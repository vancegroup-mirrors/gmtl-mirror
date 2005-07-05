# Spec file for gmtl.
%define name    gmtl
%define version	0.4.9
%define release	1

Name: %{name}
Summary: The GMTL Headers
Version: %{version}
Release: %{release}
Source: %{name}-%{version}.tar.gz
URL: http://ggt.sourceforge.net/
Group: System Environment/Libraries
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-buildroot
License: LGPL
BuildPrereq: scons >= 0.96.1
Obsoletes: gmtl <= %{version}
Provides: gmtl = %{version}-%{release}

%description
The Generic Math Template Library (GMTL) is a high-performance, extensible,
and generic math library. The design is based upon discussion with many
experts in the field of computer graphics and virtual reality, culminating the
efforts of many previous math library efforts. GMTL gives the graphics
programmer several core math types and a rich library of graphics/math
operations on those types.

%prep
rm -rf $RPM_BUILD_ROOT
%setup -q

%build
# This needs to be fixed once we have a boost install.
scons #optimize=yes enable_python=yes BoostPythonDir=/home/aronb/linux-fc3 BoostVersion=1.32

%install
scons install prefix=$RPM_BUILD_ROOT/usr
# Remove all stupid scons temp files
find $RPM_BUILD_ROOT/usr -name .sconsign -exec rm {} \;

%clean
rm -rf $RPM_BUILD_ROOT

%pre

%post

%preun

%postun

%files
%defattr(-, root, root)
/usr/bin/gmtl-config
/usr/include/gmtl
#/usr/lib/*.a

%doc AUTHORS ChangeLog COPYING
#LICENSE README

%changelog
