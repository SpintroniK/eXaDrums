# Process this file with autoconf to produce configure.

# Copyright (C) 2018-2021 Jérémy Oden <jerem.oden@gmail.com>
# Copyright (C) 2018-2021 Nicolas Boulenguez <nicolas@debian.org>

# https://www.gnu.org/software/autoconf/manual/autoconf.html
AC_INIT([eXaDrums],
        [0.6.0],
        [Jérémy Oden <jerem.oden@gmail.com>],
        [],
        [https://exadrums.com])
AC_CONFIG_SRCDIR([Source/exadrumsConfig.h])
AC_PROG_CXX
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_HEADERS([config.h])

# https://www.gnu.org/software/automake/manual/automake.html
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])

# https://autotools.io/pkgconfig/pkg_check_modules.html
PKG_CHECK_MODULES([alsa], [alsa])
PKG_CHECK_MODULES([tinyxml2], [tinyxml2])
PKG_CHECK_MODULES([minizip], [minizip])
PKG_CHECK_MODULES([gtkmm], [gtkmm-3.0])
PKG_CHECK_MODULES([exadrums], [exadrums])

AC_CONFIG_FILES([
  Makefile
])
AC_OUTPUT
