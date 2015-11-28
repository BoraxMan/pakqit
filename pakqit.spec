Summary: Graphical PAK file editor for Quake engine games
Name: pakqit
Version: 0.1.0
Release: 1
License: GPLv2
Group: System
Source: http://dennisk.customer.netspace.net.au/pakqit/pakqit-0.1.0.tar.gz
URL: http://dennisk.customer.netspace.net.au/pakqit.html
Distribution: Fedora
Vendor: Dekay Software
Packager: Dennis Katsonis <dennisk@netspace.net.au>

%description
The premiere utility for manipulating .PAK files used by Quake and Quake 2 engine games.  Allows for creation of .PAK data files from directores, extraction, individual file/directory insertion and extraction, and file/directory deletion.

%prep
%setup

%build
qmake-qt4 CONFIG+=release PREFIX=$RPM_BUILD_ROOT
make
strip pakqit

%install
make install



%files
%{_bindir}/
%{_datadir}/applications/pakqit.desktop
%{_datadir}/icons/hicolor/64x64/apps/pakqit.png
%{_docdor}/*


%defattr(-,root,root,-)

%post
/bin/touch --no-create %{_datadir}/icons/hicolor &>/dev/null || :

%postun
if [ $1 -eq 0 ] ; then
    /bin/touch --no-create %{_datadir}/icons/hicolor &>/dev/null
    /usr/bin/gtk-update-icon-cache %{_datadir}/icons/hicolor &>/dev/null || :
fi

%posttrans
/usr/bin/gtk-update-icon-cache %{_datadir}/icons/hicolor &>/dev/null || :



%clean
rm -rf $RPM_BUILD_ROOT

