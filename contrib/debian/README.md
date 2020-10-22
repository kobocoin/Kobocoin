
Debian
====================
This directory contains files used to package Kobocoind/Kobocoin-qt
for Debian-based Linux systems. If you compile Kobocoind/Kobocoin-qt yourself, there are some useful files here.

## bitcoin: URI support ##


bitcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install Kobocoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your Kobocoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoin128.png` to `/usr/share/pixmaps`

Kobocoin-qt.protocol (KDE)

