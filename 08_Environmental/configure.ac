#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([08_Environmental], [0.01], [knyazev1514@gmail.com])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash],[rhash_library_init],[],[AC_MSG_ERROR([Curses is needed])])

# Optional checks
AC_CHECK_LIB([readline], [readline])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT