#!/usr/bin/perl -w

require 5.004;

use Cwd qw(chdir getcwd);
use File::Basename;
use File::Path;
use Getopt::Long;

use strict 'vars';
use vars qw($indent $log_file $full_path $debug_level);
use vars qw($CRITICAL_LVL $WARNING_LVL $CONFIG_LVL $STATE_LVL $VERB_LVL
            $HVERB_LVL);

# Subroutine prototypes.
sub printHelp();
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

my ($cfg_file, $help) = ('', '');
my (@overrides)       = ();
my (%cmd_overrides)   = ();

$CRITICAL_LVL = 0;
$WARNING_LVL  = 1;
$CONFIG_LVL   = 2;
$STATE_LVL    = 3;
$VERB_LVL     = 4;
$HVERB_LVL    = 5;

$debug_level = $CRITICAL_LVL;
GetOptions('cfg=s' => \$cfg_file, 'help' => \$help, 'override=s' => \@overrides,
           'debug=i' => \$debug_level, 'set=s' => \%cmd_overrides);

printHelp() && exit(0) if $help;

if ( ! $cfg_file )
{
   if ( -r ".esrc" )
   {
      $cfg_file = '.esrc';
   }
   else
   {
      $cfg_file = "$ENV{'HOME'}/.esrc";
   }
}

$log_file = "es.log";
open(LOG_FILE, "> $log_file")
   or warn "WARNING: Could not create log file $log_file: $!\n";

my (%orig_modules) = ();
parse("$cfg_file", \%orig_modules) or die "ERROR: Failed to parse $cfg_file\n";
my %override_modules = %orig_modules;

if ( $#overrides == -1 )
{
   if ( -r ".esrc-override" )
   {
      push(@overrides, '.esrc-override');
   }
   elsif ( -r "$ENV{'HOME'}/.esrc-override" )
   {
      push(@overrides, "$ENV{'HOME'}/.esrc-override");
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

   if ( $cfg_data =~ /\s*(\w.*?\w?)\s*{\s*(.*)\s*}\s*$/s )
   {
      my $module_name = "$1";
      my $module_body = "$2";

      local $indent = 0;
      print "Loading $module_name from $file ...\n";
      parseModule("$module_body", "$module_name", $module_ref) or return 0;
   }

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
         if ( $module_body =~ /^(\w.*?\w?)\s*{\s*(.*)/s )
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

         warn "Parse error";
         $status = 0;
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
         printDebug $VERB_LVL, "$_ --> $$mod_ref{$_}{'CVSROOT'} ",
                    "$$mod_ref{$_}{'Tag'} $$mod_ref{$_}{'Date'} ",
                    "$cvs_module_name ($$mod_ref{$_}{'Path'}";
         printDebug $VERB_LVL, " --> $install_name" if $install_name;
         printDebug $VERB_LVL, ")\n";
         checkoutModule($_, $$mod_ref{"$_"}{'CVSROOT'}, $$mod_ref{"$_"}{'Tag'},
                        $$mod_ref{"$_"}{'Date'}, "$cvs_module_name",
                        $$mod_ref{"$_"}{'Path'}, "$install_name");
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
      mkdir("$path", 0755) unless -d "$path";
      chdir("$path") if $path;
      print LOG_FILE `$cmd_line 2>&1`;

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
            chdir("$module_dir");
         }
         # Otherwise, we can just use the module name as it was originally
         # given.
         else
         {
            $orig_module_name = "$cvs_module";
         }

         printDebug $VERB_LVL, "$orig_module_name --> $co_dir/$install_name\n";
         rename("$orig_module_name", "$co_dir/$install_name")
            or warn "    WARNING: Module renaming failed: $!\n";
      }

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
   print STDERR @_ if $debug_level > $level;
}
