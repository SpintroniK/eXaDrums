## Process this file with automake to produce Makefile.in

# Copyright (C) 2018-2019 Jérémy Oden <jerem.oden@gmail.com>
# Copyright (C) 2018-2019 Nicolas Boulenguez <nicolas@debian.org>

# Cache shared with autoconf.
ACLOCAL_AMFLAGS = -I m4

PACKAGE = exadrums

# Distribute (in the tarball created by 'make dist-gzip').
EXTRA_DIST = LICENSE

# Distribute and install into docdir.
dist_doc_DATA = README.md

dist_man_MANS = exadrums.1

dist_pkgdata_DATA = \
  Data/alsaConfig.xml \
  Data/Kits/Default.xml \
  Data/metronomeConfig.xml \
  Data/sensorsConfig.xml \
  Data/SoundBank/BassDrum/BD_Acou_01.wav \
  Data/SoundBank/Crash/Crash_High.wav \
  Data/SoundBank/HiHat/HiHat.wav \
  Data/SoundBank/Ride/RideBell.wav \
  Data/SoundBank/Ride/RideEdge.wav \
  Data/SoundBank/SnareDrum/Snr_Acou_01.wav \
  Data/SoundBank/Tom/Tom01.wav \
  Data/SoundBank/Tom/Tom03.wav \
  Data/triggersConfig.xml

# Install an empty directory.
emptyrecdir = $(pkgdatadir)/Data/Rec
emptyrec_DATA =

outrawdir = $(pkgdatadir)/Data/data
dist_outraw_DATA = out.raw

uidir = $(pkgdatadir)/Ui
dist_ui_DATA = \
  Source/eXaDrums_logo_small.png \
  Source/Ui.glade

desktopdir = $(datadir)/applications
dist_desktop_DATA = \
  eXaDrums.desktop

pngdir = $(datadir)/icons/hicolor/128x128/apps
dist_png_DATA = eXaDrums.png

pixmapsdir = $(datadir)/pixmaps
dist_pixmaps_DATA = eXaDrums.xpm

# Good habits.
AM_CXXFLAGS = -Wall
AM_LDFLAGS = -Wl,--as-needed

bin_PROGRAMS = exadrums

exadrums_CXXFLAGS = $(AM_CXXFLAGS) \
  $(alsa_CFLAGS) $(tinyxml2_CFLAGS) $(gtkmm_CFLAGS) $(exadrums_CFLAGS) \
  -std=c++17
exadrums_LDADD = $(AM_LDADD) \
  -lstdc++fs \
  $(alsa_LIBS) $(tinyxml2_LIBS) $(gtkmm_LIBS) $(exadrums_LIBS)

exadrums_SOURCES = \
  Source/Controllers/CoachController.cpp \
  Source/Controllers/CoachController.h \
  Source/Controllers/ConfigController.cpp \
  Source/Controllers/ConfigController.h \
  Source/Controllers/KitController.cpp \
  Source/Controllers/KitController.h \
  Source/Controllers/MainController.cpp \
  Source/Controllers/MainController.h \
  Source/Controllers/MetronomeController.cpp \
  Source/Controllers/MetronomeController.h \
  Source/MainWindow/MainWindow.cpp \
  Source/MainWindow/MainWindow.h \
  Source/Util/Util.h \
  Source/Widgets/Fader.cpp \
  Source/Widgets/Fader.h \
  Source/Widgets/InstrumentSelector.cpp \
  Source/Widgets/InstrumentSelector.h \
  Source/Widgets/SoundTypeAndPath.cpp \
  Source/Widgets/SoundTypeAndPath.h \
  Source/Widgets/TriggerIdAndLocation.cpp \
  Source/Widgets/TriggerIdAndLocation.h \
  Source/Widgets/TriggerSelector.cpp \
  Source/Widgets/TriggerSelector.h \
  VirtualPad.h \
  Source/exadrumsConfig.h \
  Source/main.cpp
