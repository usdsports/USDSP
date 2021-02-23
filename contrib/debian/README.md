
Debian
====================
This directory contains files used to package usdsportsd/usdsports-qt
for Debian-based Linux systems. If you compile usdsportsd/usdsports-qt yourself, there are some useful files here.

## usdsports: URI support ##


usdsports-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install usdsports-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your usdsports-qt binary to `/usr/bin`
and the `../../share/pixmaps/usdsports128.png` to `/usr/share/pixmaps`

usdsports-qt.protocol (KDE)

