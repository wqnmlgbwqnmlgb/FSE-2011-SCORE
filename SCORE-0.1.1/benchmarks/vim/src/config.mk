#
# config.mk.in -- autoconf template for Vim on Unix		vim:ts=8:sw=8:
#
# DO NOT EDIT config.mk!! Do not edit config.mk.in!! Edit Makefile and run
# configure again. config.mk will be overwritten by configure.
#
# Configure does not edit the makefile directly. This method is not the
# standard use of GNU autoconf, but it has two advantages:
#   a) The user can override every choice made by configure.
#   b) Modifications to the makefile are not lost when configure is run.
#
# I hope this is worth being nonstandard. jw.


CC		= gcc
DEFS		= -DHAVE_CONFIG_H
CFLAGS		= -g -O2 -Wall -Wshadow
srcdir		= .
LDFLAGS		= 
LIBS		= -lelf -lncurses 
TAGPRG		= ctags

CPP		= gcc -E
CPP_MM		= M
X_CFLAGS	= 
X_LIBS_DIR	= 
X_PRE_LIBS	= 
X_EXTRA_LIBS	= 
X_LIBS		= 

PERL		= /usr/bin/perl
PERLLIB		= /usr/lib/perl5/5.8.8
SHRPENV		= 
PERL_SRC	= 
PERL_OBJ	= 
PERL_PRO	= 
PERL_CFLAGS	= 

PYTHON_SRC	= 
PYTHON_OBJ	= 
PYTHON_CFLAGS	= 
PYTHON_LIBS	= 
PYTHON_CONFDIR	= 
PYTHON_GETPATH_CFLAGS = 

AWK		= gawk

### Top directory for everything
prefix		= /usr/local

### Top directory for the binary
exec_prefix	= ${prefix}

### Prefix for location of data files
BINDIR		= ${exec_prefix}/bin

### Prefix for location of data files
DATADIR		= ${prefix}/share

### Prefix for location of man pages
MANDIR		= ${prefix}/man

### Do we have a GUI
GUI_INC_LOC	= 
GUI_LIB_LOC	= 
GUI_INCL	= $(NONE_INCL)
GUI_SRC		= $(NONE_SRC)
GUI_OBJ		= $(NONE_OBJ)
GUI_DEFS	= $(NONE_DEFS)
GUI_IPATH	= $(NONE_IPATH)
GUI_LIBS_DIR	= $(NONE_LIBS_DIR)
GUI_LIBS1	= $(NONE_LIBS1)
GUI_LIBS2	= $(NONE_LIBS2)
GUI_TARGETS	= $(NONE_TARGETS)
GUI_MAN_TARGETS	= $(NONE_MAN_TARGETS)
GUI_TESTTARGET	= $(NONE_TESTTARGET)
NARROW_PROTO	= 
GUI_X_LIBS	= 

### Any OS dependent extra source and object file
OS_EXTRA_SRC	= 
OS_EXTRA_OBJ	= 
