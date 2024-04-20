AC_PREREQ([2.69])
AC_INIT([brightness_agan2k],[0.1],[evg.andrienko@gmail.com])
AM_INIT_AUTOMAKE([foreign subdir-objects -Wall -Werror -Wportability])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
CFLAGS="-I/usr/local/include ${CFLAGS}"
LDFLAGS="-L/usr/local/lib ${LDFLAGS}"

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL

# Checks for libraries.
AC_CHECK_LIB([popt], [poptGetContext], [], AC_MSG_ERROR([cannot find libpopt]))
AC_CHECK_LIB([hidapi], [hid_init], [], AC_MSG_ERROR([cannot find libhidapi]))

# Checks for header files.
AC_CHECK_INCLUDES_DEFAULT
AC_CHECK_HEADER([popt.h], [], AC_MSG_ERROR([cannot find popt.h]))
AC_CHECK_HEADER([hidapi/hidapi.h], [], AC_MSG_ERROR([cannot find hidapi/hidapi.h]))

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE

AC_OUTPUT
