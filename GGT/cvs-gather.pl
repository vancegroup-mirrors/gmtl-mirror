#!/usr/bin/perl -w

# Id: cvs-gather.pl,v 1.12 2002/02/07 18:53:21 patrick Exp

require 5.004;

use Cwd qw(chdir getcwd);
use File::Basename;
use File::Path;
use Getopt::Long;

use strict 'vars';
use vars qw($indent $log_file $full_path $debug_level);
use vars qw($CRITICAL_LVL $WARNING_LVL $CONFIG_LVL $STATE_LVL $VERB_LVL
            $HVERB_LVL $HEX_LVL);

# Subroutine prototypes.
sub printHelp();
sub printVersion();
sub parse($$);
sub parseModule($$$;$);
sub handleInclude($$$);
sub expandWildcardLine($$);
sub expandWildcards($$$$$);
sub doOverride($$);
sub overrideValue($$$);
sub checkoutModules($);
sub checkoutModule($$$$$$$);
sub expandEnvVars($);
sub printDebug($@);

# *********************************************************************
# Here is the version for this script!

my $VERSION = '0.0.4';
# *********************************************************************

my $cfg_file      = '';
my $help          = 0;
my $print_version = 0;
my $verbose       = 0;
my $force_install = 0;

my (@overrides)     = ();
my (%cmd_overrides) = ();

$CRITICAL_LVL = 0;
$WARNING_LVL  = 1;
$CONFIG_LVL   = 2;
$STATE_LVL    = 3;
$VERB_LVL     = 4;
$HVERB_LVL    = 5;
$HEX_LVL      = 6;

$debug_level = $CRITICAL_LVL;
GetOptions('cfg=s' => \$cfg_file, 'help' => \$help, 'override=s' => \@overrides,
           'debug=i' => \$debug_level, 'set=s' => \%cmd_overrides,
           'version' => \$print_version, 'verbose' => \$verbose,
           'force-install' => \$force_install);

# Print the help output and exit if --help was on the command line.
printHelp() && exit(0) if $help;

# Print the version number and exit if --version was on the command line.
printVersion() && exit(0) if $print_version;

# If we are doing verbose output and the user did not change the debug level,
# then we push the debug level up to the max.
$debug_level = $HVERB_LVL if $verbose && $debug_level <= $CRITICAL_LVL;

if ( ! $cfg_file )
{
   if ( -r ".gatherrc" )
   {
      $cfg_file = '.gatherrc';
   }
   else
   {
      $cfg_file = "$ENV{'HOME'}/.gatherrc";
   }
}

$log_file = "gather.log";
open(LOG_FILE, "> $log_file")
   or warn "WARNING: Could not create log file $log_file: $!\n";

my (%orig_modules) = ();
parse("$cfg_file", \%orig_modules) or die "ERROR: Failed to parse $cfg_file\n";
my %override_modules = %orig_modules;

if ( $#overrides == -1 )
{
   if ( -r ".gatherrc-override" )
   {
      push(@overrides, '.gatherrc-override');
   }
   elsif ( -r "$ENV{'HOME'}/.gatherrc-override" )
   {
      push(@overrides, "$ENV{'HOME'}/.gatherrc-override");
   }
}

my $override = '';
foreach $override ( @overrides )
{
   if ( open(OVERRIDE, "$override") )
   {
      my $line;
      while ( $line = <OVERRIDE> )
      {
         chomp($line);

         # Strip comments.
         $line =~ s/#.*$//;

         # Skip blank lines.
         next if $line =~ /^\s*$/;

         # The current line has at least one wildcard.
         if ( $line =~ /\*/ )
         {
            if ( $line !~ /\*\./ )
            {
               warn "ERROR: Invalid wildcard use at $override:$.\n";
            }
            else
            {
               my(@override_lines) = expandWildcardLine("$line",
                                                        \%orig_modules);

               foreach ( @override_lines )
               {
                  doOverride("$_", \%override_modules);
               }
            }
         }
         # The current line has no wildcards.
         else
         {
            doOverride("$line", \%override_modules);
         }
      }

      close(OVERRIDE);
   }
   else
   {
      warn "WARNING: Could not open override file $override: $!\n";
   }
}

my $key;
foreach $key ( keys(%cmd_overrides) )
{
   # This is needed because expandWildcardLine() and doOverride() expect to
   # see something of the form "<key> = <value>".
   my $line = "$key = $cmd_overrides{$key}";

   # The current line has at least one wildcard.
   if ( $key =~ /\*/ )
   {
      if ( $key !~ /\*\./ )
      {
         warn "ERROR: Invalid wildcard use at $override:$.\n";
      }
      else
      {
         my(@override_lines) = expandWildcardLine("$line", \%orig_modules);

         foreach ( @override_lines )
         {
            doOverride("$_", \%override_modules);
         }
      }
   }
   # The current line has no wildcards.
   else
   {
      doOverride("$line", \%override_modules);
   }
}

checkoutModules(\%override_modules);
exit 0;

# -----------------------------------------------------------------------------
# Subroutines follow.
# -----------------------------------------------------------------------------

sub printHelp ()
{
   print <<EOF;
Usage:
    $0
        [ --cfg=<filename> ] [ --override=<filename> ... ] [ --debug=<level> ]
        [ --set <key>=<value> ... ] [ --verbose ]

For application makefiles:

    --help
        Print usage information.

    --cfg=<filename>
        Specify the name of the module configuration to load. If not given,
        the current directory is searched for a .gatherrc file. If one is not
        found, the user's home directory is searched for the same file.

    --debug=<level>
        Set the debug output level (0-5).

    --override=<filename>
        Specify the name of an an override file used to override values set
        by the loaded module configuration file. There may be zero or more of
        these. If not specified, the current directory is searched for the
        file .gatherrc-override. If not found, the user's home directory is
        searched for the same file.

    --set <key1>=<value1> --set <key2>=<value2> ... --set <keyN>=<valueN>
        Override the setting for "key" with "value". This supercedes any
        settings in the module configuration file and any loaded override
        file. There may be zero or more of these.

    --force-install
        When re-downloading a module, force removal of the existing
        directory.  Without this option, a warning is printed, and the
        existing directory is not removed.

    --verbose
        Turn on verbose output.  This basically makes the log file useless.

    --version
        Print the version number and exit.
EOF

   return 1;
}

sub printVersion ()
{
   print "$VERSION\n";

   return 1;
}

sub parse ($$)
{
   my $file       = shift;
   my $module_ref = shift;

   my $status = 1;

   open(INPUT, "$file") or die "ERROR: Could not open $file: $!\n";

   my $cfg_data = '';
   while ( <INPUT> )
   {
      $cfg_data .= $_;
   }
   close(INPUT);

   $cfg_data =~ s|/\*.*?\*/||gs; # Strip out C-style comments
   $cfg_data =~ s/#.*$//gm;      # Strip out shell-style comments
   $cfg_data =~ s|//.*$||gm;     # Strip out C++-style comments 

   my $mod_count = 0;
   while ( $cfg_data =~ /\s*(\w.*?\w?)\s*{\s*(.*?)\s*}\s*;\s*/s )
   {
      my $module_name = "$1";
      my $module_body = "$2";
      $cfg_data       = $';

      $indent = 0;
      print "Loading $module_name from $file ...\n";
      my $parse_stat = parseModule("$module_body", "$module_name", $module_ref);
      return 0 if $parse_stat == -1;
      $mod_count++
   }

   warn "WARNING: Nothing happened which probably means a parse error\n"
      unless $mod_count > 0;

   return $status;
}

sub parseModule ($$$;$)
{
   my $module_body = shift;
   my $module_name = shift;
   my $module_ref  = shift;
   my $in_module   = shift || 0;

   print " " x $indent, "Parsing $module_name\n";

   my $status = 1;

   # Ensure that all of these are initialized just for safety's sake.
   $$module_ref{"$module_name"}{'CVSROOT'} = '';
   $$module_ref{"$module_name"}{'Module'}  = [];
   $$module_ref{"$module_name"}{'Date'}    = '';
   $$module_ref{"$module_name"}{'Tag'}     = '';
   $$module_ref{"$module_name"}{'Path'}    = '.';

   # Initialize this module's dependency hash with an anonymous hash
   # reference.
   $$module_ref{"$module_name"}{'deps'} = {};

   while ( "$module_body" ne "" && $status == 1 )
   {
      printDebug $HEX_LVL, ">" x 78, "\nNew module body:\n$module_body\n",
                           "<" x 78, "\n";

      SWITCH:
      {
         # Matched an include.
         if ( $module_body =~ /^(s?include\s+(.+?);)/s )
         {
            my $inc_string = "$1";
            my $inc_file   = "$2";

            $indent += 4;
            $status = handleInclude("$inc_string", "$inc_file", \$module_body);
            $indent -= 4;

            last SWITCH;
         }

         if ( $module_body =~ /^CVSROOT:\s+(\S+?)\s*;/s )
         {
            $$module_ref{"$module_name"}{'CVSROOT'} = "$1";
            $module_body = $';
            last SWITCH;
         }

         if ( $module_body =~ /^Module:\s+(.+?)\s*;/s )
         {
            my $temp = "$1";
            $module_body = $';

            my($cvs_module_name, $install_name) = ('', '');

            if ( $temp =~ /^(.+?)\s*\[(.*)\]\s*$/ )
            {
               $cvs_module_name = "$1";
               $install_name    = "$2";
            }
            else
            {
               $cvs_module_name = "$temp";
            }

            push(@{$$module_ref{"$module_name"}{'Module'}},
                 {$cvs_module_name => $install_name});
            last SWITCH;
         }

         # Matched a tag/branch setting for this module.
         if ( $module_body =~ /^Tag:\s+(\S+?)\s*;/s )
         {
            $$module_ref{"$module_name"}{'Tag'}  = "$1";
            $module_body = $';
            last SWITCH;
         }

         # Matched a date setting for this module.
         if ( $module_body =~ /^Date:\s+(.+?)\s*;/s )
         {
            $$module_ref{"$module_name"}{'Date'}  = "$1";
            $module_body = $';
            last SWITCH;
         }

         # Matched a path setting for this module.
         if ( $module_body =~ /^Path:\s+(.+?)\s*;/s )
         {
            my $path = "$1";
            expandEnvVars(\$path);
            $$module_ref{"$module_name"}{'Path'}  = "$path";
            $module_body   = $';
            last SWITCH;
         }

         # Matched the beginning of a sub-module.
         if ( $module_body =~ /^(\w+)\s*{\s*(.*)/s )
         {
            $indent += 4;
            ($module_body = parseModule("$2", "$1",
                                        $$module_ref{"$module_name"}{'deps'},
                                        1))
               or return 0;
            $indent -= 4;
            print " " x $indent, "Returning to $module_name\n";
            last SWITCH;
         }

         # We have reached the end of the module.
         if ( $module_body =~ /^}/ && $in_module )
         {
            print " " x $indent, "Finished parsing $module_name\n";
            return $';
         }

         warn "Parse error in the following:\n$module_body\n";
         $status = -1;
      }

      $module_body =~ s/^\s+(\S*)/$1/s;
   }

   return $status;
}

sub handleInclude ($$$)
{
   my $inc_string = shift;
   my $inc_file   = shift;
   my $text_ref   = shift;

   my $sinclude = 1 if $inc_string =~ /^sinclude/;

   my $status = 1;

   expandEnvVars(\$inc_file);

   if ( open(INC_FILE, "$inc_file") )
   {
      my $loaded_body = '';
      while ( <INC_FILE> )
      {
         $loaded_body .= $_;
      }
      close(INC_FILE);

      $$text_ref =~ s/\Q$inc_string\E/$loaded_body/s;
   }
   else
   {
      warn "WARNING: Failed to load $inc_file: $!\n" unless $sinclude;
      $$text_ref =~ s/\Q$inc_string\E//s;
      $status = 0;
   }

   return $status;
}

sub expandWildcardLine ($$)
{
   my $line       = shift;
   my $module_ref = shift;

   my (@expanded_lines) = ();

   my ($path, $value) = split(/\s*=\s*/, "$line");
   my (@path_arr)     = split(/\./, "$path");

   local $full_path = "$path";

   if ( $#path_arr < 1 )
   {
      warn "ERROR: Invalid hierarchy in $line ($override:$.)\n";
   }
   else
   {
      my (@modules) = ();

      if ( "$path_arr[0]" eq "*" )
      {
         @modules = keys(%$module_ref);
      }
      else
      {
         $modules[0] = $$module_ref{$path_arr[0]};
      }

      my $module;
      foreach $module ( @modules )
      {
         my (@work_arr) = @path_arr;
         $work_arr[0] = "$module";
         my $work_path = "$full_path";
         $work_path =~ s/^\*/$module/;

         expandWildcards(\@work_arr, $module_ref, $value, \@expanded_lines,
                         $work_path);
      }
   }

   return @expanded_lines;
}

sub expandWildcards ($$$$$)
{
   my $path_ref       = shift;
   my $module_ref     = shift;
   my $override_value = shift;
   my $lines_ref      = shift;
   my $work_path      = shift;

   my $current_value = shift(@$path_ref);
   printDebug $VERB_LVL, "current_value: $current_value\n";

   if ( "$current_value" eq "*" )
   {
      die "This should never happen!\n";
   }
   else
   {
      # A wildcard in this position (<Module>.*) must always indicate a
      # project dependency.
      if ( $$path_ref[0] && $$path_ref[0] eq "*" )
      {
         my (@temp_arr) = ();
         my ($dep_name, $new_path);

         shift(@$path_ref);
         my $save_path = $work_path;
         printDebug $VERB_LVL, "Unexpanded Path: $work_path\n";

         foreach $dep_name ( keys(%{$$module_ref{"$current_value"}{'deps'}}) )
         {
            printDebug $VERB_LVL, "Dep: $dep_name\n";
            @temp_arr = @$path_ref;
            unshift(@temp_arr, "$dep_name");
            printDebug $HVERB_LVL, "path_arr: @$path_ref\n";
            printDebug $HVERB_LVL, "temp_arr: @temp_arr\n";

            $work_path =~ s/\*/$dep_name/;
            printDebug $VERB_LVL, "New Path: $work_path\n";

            expandWildcards(\@temp_arr, $$module_ref{"$current_value"}{'deps'},
                            $override_value, $lines_ref, $work_path);
            $work_path = $save_path;
         }

         # If the above expansion gave us <Module>.<Setting>, we now have
         # only <Setting> which is meaningless.
         # XXX: It seems like this should not be necessary, but it may be the
         # result of using a different array reference in the recursive calls.
         shift(@$path_ref) if $#$path_ref == 0;
      }
      elsif ( defined($$module_ref{"$current_value"}) )
      {
         printDebug $STATE_LVL, "Matched $current_value\n";
         printDebug $VERB_LVL, "Checking for $$path_ref[0] in $current_value\n";

         # We have reached the end of the recursion.
         if ( defined($$module_ref{"$current_value"}{$$path_ref[0]}) )
         {
            printDebug $STATE_LVL,
                       "Adding line '$work_path = $override_value'\n";
            push(@$lines_ref, "$work_path = $override_value");
         }
         elsif ( defined($$module_ref{"$current_value"}{'deps'}{$$path_ref[0]}) )
         {
            printDebug $STATE_LVL, "Matched dependency $$path_ref[0]\n";
            expandWildcards($path_ref, $$module_ref{"$current_value"}{'deps'},
                            $override_value, $lines_ref, $work_path);
         }
         else
         {
            warn "WARNING: $work_path not found!\n";
         }
      }
      else
      {
         warn "WARNING: $work_path not found!\n";
      }
   }
}

sub doOverride ($$)
{
   my $line       = shift;
   my $module_ref = shift;

   my ($path, $value) = split(/\s*=\s*/, "$line");
   my (@path_arr)     = split(/\./, "$path");

   if ( $#path_arr < 1 )
   {
      warn "ERROR: Invalid hierarchy in $line ($override:$.)\n";
   }
   else
   {
      local $full_path = "$path";
      overrideValue(\@path_arr, $module_ref, "$value");
   }
}

sub overrideValue ($$$)
{
   my $path_ref       = shift;
   my $module_ref     = shift;
   my $override_value = shift;

   my $current_value = shift(@$path_ref);

   if ( defined($$module_ref{"$current_value"}) )
   {
#      print "Matched $current_value\n";
#      print "Checking for ", $$path_ref[0], " in $current_value\n";

      # We have reached the end of the recursion.
      if ( defined($$module_ref{"$current_value"}{$$path_ref[0]}) )
      {
         if ( $$path_ref[0] eq "Module" )
         {
            my $module_list = "$override_value";
            $module_list =~ s/;/ /g;

            my(@modules)       = split(/;/, "$module_list");
            my(@mod_overrides) = ();

            my $mod;
            foreach $mod ( @modules )
            {
               my($module_name, $install_name) = ('', '');

               if ( $mod =~ /^\s*(.+?)\s*\[(.*)\]\s*$/ )
               {
                  $module_name  = "$1";
                  $install_name = "$2";
               }
               else
               {
                  $module_name = "$mod";
               }

               push(@mod_overrides, {$module_name => $install_name});
            }

            print "Overriding $full_path with $module_list\n";
            $$module_ref{"$current_value"}{'Module'} = \@mod_overrides;
         }
         elsif ( $$path_ref[0] eq "Path" )
         {
            my $new_path = "$override_value";
            expandEnvVars(\$new_path);

            print "Overriding $full_path with $new_path\n";
            $$module_ref{"$current_value"}{'Path'} = "$new_path";
         }
         else
         {
            print "Overriding $full_path with $override_value\n";
            $$module_ref{"$current_value"}{$$path_ref[0]} = "$override_value";
         }
      }
      elsif ( defined($$module_ref{"$current_value"}{'deps'}{$$path_ref[0]}) )
      {
#         print "Matched dependency $$path_ref[0]\n";
         overrideValue($path_ref, $$module_ref{"$current_value"}{'deps'},
                       $override_value);
      }
      else
      {
         warn "WARNING: $full_path not found!\n";
      }
   }
   else
   {
      warn "WARNING: $full_path not found!\n";
   }
}

sub checkoutModules ($)
{
   my $mod_ref = shift;

   foreach ( keys(%$mod_ref) )
   {
      my $module = '';
      foreach $module ( @{$$mod_ref{"$_"}{'Module'}} )
      {
         my($cvs_module_name, $install_name) = each(%$module);

         if ( defined($$mod_ref{"$_"}{'CVSROOT'}) && $cvs_module_name )
         {
            printDebug $VERB_LVL, "$_ --> $$mod_ref{$_}{'CVSROOT'} ",
                       "$$mod_ref{$_}{'Tag'} $$mod_ref{$_}{'Date'} ",
                       "$cvs_module_name (to $$mod_ref{$_}{'Path'}";
            printDebug $VERB_LVL, "/$install_name" if $install_name;
            printDebug $VERB_LVL, ")\n";
            checkoutModule($_, $$mod_ref{"$_"}{'CVSROOT'},
                           $$mod_ref{"$_"}{'Tag'}, $$mod_ref{"$_"}{'Date'},
                           "$cvs_module_name", $$mod_ref{"$_"}{'Path'},
                           "$install_name");
         }
      }

      checkoutModules($$mod_ref{"$_"}{'deps'});
   }
}

sub checkoutModule ($$$$$$$)
{
   my $name         = shift;
   my $cvsroot      = shift;
   my $tag          = shift;
   my $date         = shift;
   my $cvs_module   = shift;
   my $path         = shift;
   my $install_name = shift;

   if ( "$cvsroot" ne "" && "$cvs_module" ne "" )
   {
      print LOG_FILE "Checking out $cvs_module from $cvsroot ...\n";
      my $cmd_line = "cvs -d $cvsroot checkout ";

      $cmd_line .= "-r $tag " if $tag && "$tag" ne "HEAD";
      $cmd_line .= "-D $date " if $date;

      $cmd_line .= "$cvs_module";
      print "Checking out source for $name: $cvs_module -- please wait ...\n";
      print LOG_FILE "$cmd_line\n";
      my $cwd = getcwd();

      # The name for the temporary checkout directory.
      my $temp_checkout_dir = "$cwd/temp.$$";

      # Create the temporary directory for the initial module checkout.
      if ( mkdir("$temp_checkout_dir", 0700) )
      {
         chdir("$temp_checkout_dir")
            or warn "WARNING: Could not chdir to $temp_checkout_dir: $!\n";
      }
      # If the temporary directory creation failed, we'll just fall back on
      # the current working directory.
      else
      {
         $temp_checkout_dir = "$cwd";
      }

      if ( $verbose )
      {
         print `$cmd_line 2>&1`;
      }
      else
      {
         print LOG_FILE `$cmd_line 2>&1`;
      }

      chdir("$cwd");
      mkdir("$path", 0755) unless -d "$path";
      chdir("$path") if $path;

      # This is the full path to the directory where the checked-out module
      # will be placed after being downloaded.
      my $inst_dir = getcwd();

      # We have an alternate installation name that the actual path to the
      # checked-out module.
      if ( $install_name )
      {
         print "    Moving $cvs_module to $install_name ...\n";
         
         my $install_dir = '';

         if ( $install_name =~ /\// )
         {
            $install_dir = (fileparse("$install_name"))[1];
         }
         else
         {
            $install_dir = "$install_name";
         }

         # Create the path for the module's target location unless it already
         # exists.
         mkpath($install_dir, 0, 0755) unless -d "$install_dir";

         my $orig_module_name = '';

         # Save the current working directory.  It is the directory where
         # the module was checked out.
         my $co_dir = getcwd();

         # If the checked out module contained a path, we have to deal with
         # that.
         if ( $cvs_module =~ /\// )
         {
            my ($module_dir, $ext);
            ($orig_module_name, $module_dir, $ext) = fileparse("$cvs_module");
            chdir("$temp_checkout_dir/$module_dir")
               or die "ERROR: Could not chdir to $temp_checkout_dir/$module_dir: $!\n";
         }
         # Otherwise, we can just use the module name as it was originally
         # given.
         else
         {
            $orig_module_name = "$cvs_module";
         }

         printDebug $VERB_LVL, "$orig_module_name --> $co_dir/$install_name\n";

         if ( -d "$co_dir/$install_name" && ! $force_install )
         {
            warn "    WARNING: Module renaming failed--target directory already exists!\n";
         }
         else
         {
            rmtree("$co_dir/$install_name") if $force_install;
            printDebug $STATE_LVL, "Moving $orig_module_name to " .
                                   "$co_dir/$install_name\n";
            rename("$orig_module_name", "$co_dir/$install_name")
               or warn "    WARNING: Module renaming failed: $!\n";
         }
      }
      # We are going to use the default module name, but we have to get it
      # from the temporary directory to the place the user wants it.
      else
      {
         my @module_path = split(/\//, "$cvs_module");

         my $skipped_path = '';
         my $dest_dir = "$inst_dir";

         # We have to iterate over each directory in @module_path and find
         # the first path element that does not exist in $dest_dir.  The
         # reason is that a previous module may have set up part of this
         # module's path already, and we cannot overwrite what already exists.
         my $dir;
         foreach $dir ( @module_path )
         {
            # We found a directory that does not already exist, so we can go
            # ahead with the move.
            if ( ! -d "$dest_dir/$dir" )
            {
               printDebug $STATE_LVL,
                          "Renaming $temp_checkout_dir/$skipped_path/$dir " .
                          "to $dest_dir/$dir\n";
               rename("$temp_checkout_dir/$skipped_path/$dir",
                      "$dest_dir/$dir");
            }
            # $dir already exists in $dest_dir, so append it to $dest_dir and
            # move on.
            else
            {
               $skipped_path .= "$dir/";
               $dest_dir     .= "/$dir";
               printDebug $STATE_LVL, "Descending to $skipped_path ...\n";
            }
         }
      }

      printDebug $STATE_LVL, "Removing tree $temp_checkout_dir\n";
      rmtree("$temp_checkout_dir")
         or warn "WARNING: Could not clean up temporary checkout directory: $!\n";

      print "Done\n";
      chdir("$cwd");
   }
   else
   {
      warn " " x $indent, "Nothing to check out for $name!\n";
   }
}

sub expandEnvVars ($)
{
   my $text_ref = shift;

   while ( $$text_ref =~ /\${(.+?)}/ )
   {
      my $var_name = "$1";
      $$text_ref =~ s/\${$var_name}/$ENV{$var_name}/g;
   }
}

sub printDebug ($@)
{
   my $level = shift;
   print STDERR @_ if $debug_level >= $level;
}
