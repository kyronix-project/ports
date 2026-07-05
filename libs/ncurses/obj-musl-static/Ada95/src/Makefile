##############################################################################
# Copyright 2018-2024,2025 Thomas E. Dickey                                  #
# Copyright 1999-2016,2018 Free Software Foundation, Inc.                    #
#                                                                            #
# Permission is hereby granted, free of charge, to any person obtaining a    #
# copy of this software and associated documentation files (the "Software"), #
# to deal in the Software without restriction, including without limitation  #
# the rights to use, copy, modify, merge, publish, distribute, distribute    #
# with modifications, sublicense, and/or sell copies of the Software, and to #
# permit persons to whom the Software is furnished to do so, subject to the  #
# following conditions:                                                      #
#                                                                            #
# The above copyright notice and this permission notice shall be included in #
# all copies or substantial portions of the Software.                        #
#                                                                            #
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR #
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   #
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    #
# THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      #
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING    #
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER        #
# DEALINGS IN THE SOFTWARE.                                                  #
#                                                                            #
# Except as contained in this notice, the name(s) of the above copyright     #
# holders shall not be used in advertising or otherwise to promote the sale, #
# use or other dealings in this Software without prior written               #
# authorization.                                                             #
##############################################################################
#
#  Author:  Juergen Pfeifer, 1996
#
#  $Id: Makefile.in,v 1.102 2025/10/18 13:35:27 tom Exp $
#
.SUFFIXES:

SHELL		= /bin/sh
VPATH		= ../../../Ada95/src
THIS		= Makefile

ADA_MFLAGS 	=



MODEL		= ../../objects

top_srcdir	= ../../..
srcdir		= ../../../Ada95/src
prefix		= /usr
exec_prefix	= ${prefix}
includedir	= ${prefix}/include
libdir		= ${exec_prefix}/lib

LIBDIR		= $(DESTDIR)$(libdir)
ADA_INCLUDE	= $(DESTDIR)/usr/share/ada/adainclude
ADA_OBJECTS	= $(DESTDIR)/usr/lib/ada/adalib

INSTALL		= /usr/bin/install -c 
INSTALL_LIB	= /usr/bin/install -c -m 644 -p

AR		= ar
ARFLAGS		= -curvU
AWK		= gawk
LN_S		= ln -s -f

CC		= musl-gcc
CFLAGS		= -O2 -fno-link-libatomic --param max-inline-insns-single=1200 

CPPFLAGS	= -I${srcdir}/../../include -I. -I../include -I../../include  -I. -I${srcdir} -I../include -I${srcdir}/../include -D_BSD_SOURCE -DNDEBUG \
		  -DHAVE_CONFIG_H -I$(srcdir)

CCFLAGS		= $(CPPFLAGS) $(CFLAGS)

CFLAGS_NORMAL	= $(CCFLAGS) -DNCURSES_STATIC
CFLAGS_DEBUG	= $(CCFLAGS) -DNCURSES_STATIC -g -DTRACE
CFLAGS_PROFILE	= $(CCFLAGS) -DNCURSES_STATIC -pg
CFLAGS_SHARED	= $(CCFLAGS) -fPIC

CFLAGS_DEFAULT	= $(CFLAGS_NORMAL)

LINK		= $(CC)
LDFLAGS		= -static  

RANLIB		= ranlib

################################################################################
ADA		= gnatmake
ADAPREP		= gnatprep
ADAFLAGS	=  -gnatpn -O2 -I. -I$(srcdir)

LIB_NAME	= AdaCurses
SONAME		= lib$(LIB_NAME).so.1

GNAT_PROJECT	= AdaCurses.gpr

# build/source are the Ada95 tree
BUILD_DIR	= ..
SOURCE_DIR	= ..

BUILD_DIR_LIB	= $(BUILD_DIR)/lib
SOURCE_DIR_SRC	= $(SOURCE_DIR)/src

ADAMAKE		= gnatmake
ADAMAKEFLAGS	= \
	-P$(GNAT_PROJECT) \
	-XBUILD_DIR=`cd $(BUILD_DIR);pwd` \
	-XSOURCE_DIR=`cd $(SOURCE_DIR);pwd` \
	-XSOURCE_DIR2=`cd $(srcdir);pwd` \
	-XLIB_NAME=$(LIB_NAME) \
	-XSONAME=$(SONAME)

CARGS           = -cargs $(ADAFLAGS)
LARGS           =

STATIC_LIBNAME	= lib$(LIB_NAME).a
SHARED_LIBNAME	= $(SONAME)
SHARED_SYMLINK	= lib$(LIB_NAME).so

ALIB            = terminal_interface
ABASE           = $(ALIB)-curses
################################################################################
GENERATED_SOURCES=$(ABASE).ads         			\
		  $(ABASE).adb         			\
	          $(ABASE)-aux.ads   			\
	          $(ABASE)-trace.ads   			\
	          $(ABASE)-menus.ads   			\
	          $(ABASE)-forms.ads   			\
	          $(ABASE)-mouse.ads 			\
	          $(ABASE)-panels.ads			\
	          $(ABASE)-menus-menu_user_data.ads	\
	          $(ABASE)-menus-item_user_data.ads	\
	          $(ABASE)-forms-form_user_data.ads	\
	          $(ABASE)-forms-field_types.ads	\
	          $(ABASE)-forms-field_user_data.ads	\
	          $(ABASE)-panels-user_data.ads
################################################################################
LIBOBJS=$(ALIB).o                			\
	$(ABASE)-aux.o           			\
	$(ABASE).o               			\
	$(ABASE)-terminfo.o				\
	$(ABASE)-termcap.o				\
	$(ABASE)-putwin.o				\
	$(ABASE)-trace.o				\
	$(ABASE)-mouse.o         			\
	$(ABASE)-panels.o        			\
	$(ABASE)-menus.o         			\
	$(ABASE)-forms.o         			\
	$(ABASE)-forms-field_types.o      		\
	$(ABASE)-forms-field_types-alpha.o      	\
	$(ABASE)-forms-field_types-alphanumeric.o	\
	$(ABASE)-forms-field_types-intfield.o     	\
	$(ABASE)-forms-field_types-numeric.o     	\
	$(ABASE)-forms-field_types-regexp.o       	\
	$(ABASE)-forms-field_types-enumeration.o	\
	$(ABASE)-forms-field_types-ipv4_address.o	\
	$(ABASE)-forms-field_types-user.o 		\
	$(ABASE)-forms-field_types-user-choice.o 	\
	$(ABASE)-text_io.o       			\
	$(ABASE)-text_io-aux.o

# Ada object files for generic packages. Since gnat 3.10 they are
# also compiled
GENOBJS=$(ABASE)-menus-menu_user_data.o			\
	$(ABASE)-menus-item_user_data.o			\
	$(ABASE)-forms-form_user_data.o			\
	$(ABASE)-forms-field_user_data.o		\
	$(ABASE)-forms-field_types-enumeration-ada.o	\
	$(ABASE)-panels-user_data.o			\
	$(ABASE)-text_io-integer_io.o			\
	$(ABASE)-text_io-float_io.o			\
	$(ABASE)-text_io-fixed_io.o			\
	$(ABASE)-text_io-decimal_io.o			\
	$(ABASE)-text_io-enumeration_io.o		\
	$(ABASE)-text_io-modular_io.o			\
	$(ABASE)-text_io-complex_io.o

################################################################################

.PHONY :	all
.PHONY :	clean
.PHONY :	distclean
.PHONY :	install
.PHONY :	install.libs
.PHONY :	libs
.PHONY :	mostlyclean
.PHONY :	realclean
.PHONY :	sources
.PHONY :	uninstall
.PHONY :	uninstall.libs

all ::  $(BUILD_DIR_LIB)/$(STATIC_LIBNAME)
	@echo done

$(ADA_INCLUDE) \
$(ADA_OBJECTS) \
$(LIBDIR) \
$(BUILD_DIR_LIB) :
	mkdir -p $@

$(GENERATED_SOURCES) :
	( cd ../gen; $(MAKE) $(ADA_MFLAGS) )

sources : $(GENERATED_SOURCES)
	@echo made $@

libs \
install \
install.libs :: \
		$(BUILD_DIR_LIB)/$(STATIC_LIBNAME)
	@echo made $(STATIC_LIBNAME)

#OLD:BEGIN
install \
install.libs :: \
		$(BUILD_DIR_LIB)/$(STATIC_LIBNAME) \
		$(ADA_OBJECTS)
	@$(INSTALL_LIB) \
		$(BUILD_DIR_LIB)/$(STATIC_LIBNAME) \
		$(ADA_OBJECTS)

uninstall \
uninstall.libs ::
	@rm -f $(ADA_OBJECTS)/$(STATIC_LIBNAME)
#OLD:END

mostlyclean ::
	rm -f *.o *.ali b_t*.* *.s $(PROGS) a.out core b_*_test.c *.xr[bs] *.a

clean :: mostlyclean
	rm -f $(ABASE)-trace.adb

distclean :: clean
	rm -f Makefile library.gpr

realclean :: distclean

BASEDEPS=$(ABASE).ads $(ABASE)-aux.ads $(ABASE).adb

$(ABASE)-trace.adb : $(srcdir)/$(ABASE)-trace.adb_p
	rm -f $@
	$(ADAPREP) -DADA_TRACE=FALSE -T  $(srcdir)/$(ABASE)-trace.adb_p $@

###############################################################################
# Use these definitions when building a shared library.
SHARED_C_OBJS	= c_varargs_to_ada.o c_threaded_variables.o ncurses_compat.o
SHARED_OBJS 	= $(SHARED_C_OBJS) $(LIBOBJS) ${GENOBJS}

c_varargs_to_ada.o :	$(srcdir)/c_varargs_to_ada.c
	$(CC) $(CFLAGS_DEFAULT) -c -o $@ $(srcdir)/c_varargs_to_ada.c

c_threaded_variables.o : $(srcdir)/c_threaded_variables.c
	$(CC) $(CFLAGS_DEFAULT) -c -o $@ $(srcdir)/c_threaded_variables.c

ncurses_compat.o :	$(srcdir)/ncurses_compat.c
	$(CC) $(CFLAGS_DEFAULT) -c -o $@ $(srcdir)/ncurses_compat.c

###############################################################################
# Use these definitions when building a static library.
STATIC_C_OBJS	= static_c_varargs_to_ada.o static_c_threaded_variables.o static_ncurses_compat.o
STATIC_OBJS 	= $(STATIC_C_OBJS) $(LIBOBJS) ${GENOBJS}

static_c_varargs_to_ada.o :	$(srcdir)/c_varargs_to_ada.c
	$(CC) $(CFLAGS_NORMAL) -c -o $@ $(srcdir)/c_varargs_to_ada.c

static_c_threaded_variables.o : $(srcdir)/c_threaded_variables.c
	$(CC) $(CFLAGS_NORMAL) -c -o $@ $(srcdir)/c_threaded_variables.c

static_ncurses_compat.o :	$(srcdir)/ncurses_compat.c
	$(CC) $(CFLAGS_NORMAL) -c -o $@ $(srcdir)/ncurses_compat.c

###############################################################################

$(BUILD_DIR_LIB)/$(STATIC_LIBNAME) :: \
		$(BUILD_DIR_LIB) \
		$(STATIC_OBJS)
	$(AR) $(ARFLAGS) $@ $(STATIC_OBJS)

$(BUILD_DIR)/static-ali : ; mkdir -p $@
$(BUILD_DIR)/static-obj : ; mkdir -p $@

STATIC_DIRS = \
	$(BUILD_DIR_LIB) \
	$(BUILD_DIR)/static-ali \
	$(BUILD_DIR)/static-obj

#$(BUILD_DIR_LIB)/$(STATIC_LIBNAME) :: \
#		$(STATIC_DIRS)
#$(BUILD_DIR_LIB)/$(STATIC_LIBNAME) :: \
#		$(ABASE)-trace.adb \
#		$(STATIC_C_OBJS)
#	@echo "Making $@"
#	##gprconfig --batch --config=Ada --config=C,,,,
#	-rm -f $(GNAT_PROJECT)
#	$(SHELL) $(srcdir)/library-cfg.sh static library.gpr $(CFLAGS_NORMAL) >$(GNAT_PROJECT)
#	@echo "Using GNAT Project:"
#	@-$(SHELL) -c "diff -c $(srcdir)/library.gpr $(GNAT_PROJECT); exit 0"
#	$(ADAMAKE) $(ADAMAKEFLAGS) -XLIB_KIND=static
#	$(AR) $(ARFLAGS) $@ $(STATIC_C_OBJS)
#	-rm -f $(GNAT_PROJECT)
#	@-$(SHELL) -c "diff -c library.gpr $(GNAT_PROJECT); exit 0"
#	gprbuild -p $(ADAMAKEFLAGS) -XLIB_KIND=static
#	-rm -f $(GNAT_PROJECT)

#OLD:BEGIN
#install \
#install.libs :: \
#		$(ADA_OBJECTS)
#	$(INSTALL_LIB) \
#		$(BUILD_DIR)/static-ali/*.ali \
#		$(ADA_OBJECTS)
#OLD:END
# While gprinstall is the "recommended" tool, it is rather brittle, with
# hardcoded assumptions about the use of the install-name which prevent using
# that tool to make the directory layout of older versions of the AdaCurses
# package.
#
# In principle, one might just do
#	--install-name=""
# and in dry-run mode, gprinstall pretends to handle it properly (trimming the
# empty directory level), but without the dry-run option, it fails (tested
# with gnat 10.1.1).
#NEW:BEGIN
##install \
##install.libs ::
##	@echo "Making $@"
##	##gprconfig --batch --config=Ada --config=C,,,,
##	-rm -f $(GNAT_PROJECT)
##	$(SHELL) $(srcdir)/library-cfg.sh static library.gpr $(CFLAGS_NORMAL) >$(GNAT_PROJECT)
##	@echo "Using GNAT Project:"
##	@-$(SHELL) -c "diff -c library.gpr $(GNAT_PROJECT); exit 0"
##
##	gprinstall -m -v -f -p \
##		--prefix="$(DESTDIR)$(prefix)" \
##		$(ADAMAKEFLAGS) -XLIB_KIND=static \
##		--lib-subdir="$(DESTDIR)$(prefix)"/lib \
##		--ali-subdir="$(DESTDIR)$(prefix)"/lib/ada/adalib \
##		--sources-subdir="$(DESTDIR)$(prefix)"/share/ada/adainclude
##
##	-rm -f $(GNAT_PROJECT)
#NEW:END

#OLD:BEGIN
uninstall \
uninstall.libs ::
	@rm -f $(ADA_OBJECTS)/$(STATIC_LIBNAME)
#OLD:END
#NEW:BEGIN
##uninstall \
##uninstall.libs ::
##	@echo "Making $@"
##	##gprconfig --batch --config=Ada --config=C,,,,
##	-rm -f $(GNAT_PROJECT)
##	$(SHELL) $(srcdir)/library-cfg.sh static library.gpr $(CFLAGS_NORMAL) >$(GNAT_PROJECT)
##	@echo "Using GNAT Project:"
##	@-$(SHELL) -c "diff -c library.gpr $(GNAT_PROJECT); exit 0"
##
##	gprinstall -v -f --prefix="$(DESTDIR)$(prefix)" --uninstall $(ADAMAKEFLAGS) -XLIB_KIND=static
##
##	-rm -f $(GNAT_PROJECT)
#NEW:END

#uninstall \
#uninstall.libs ::
#	@$(SHELL) -c 'for name in $(BUILD_DIR)/static-ali/*.ali ; do rm -f $(ADA_OBJECTS)/`basename $$name`; done'

$(BUILD_DIR)/dynamic-ali : ; mkdir -p $@
$(BUILD_DIR)/dynamic-obj : ; mkdir -p $@

SHARED_DIRS = \
	$(BUILD_DIR_LIB) \
	$(BUILD_DIR)/dynamic-ali \
	$(BUILD_DIR)/dynamic-obj

#all :: $(BUILD_DIR_LIB)/$(SHARED_LIBNAME)
#$(BUILD_DIR_LIB)/$(SHARED_LIBNAME) :: \
#		$(SHARED_DIRS)
#$(BUILD_DIR_LIB)/$(SHARED_LIBNAME) :: \
#		$(ABASE)-trace.adb \
#		$(SHARED_OBJS)
#	@echo "Making $@"
#	cp $(SHARED_OBJS) $(BUILD_DIR)/dynamic-obj/
#	##gprconfig --batch --config=Ada --config=C,,,,
#	-rm -f $(GNAT_PROJECT)
#	$(SHELL) $(srcdir)/library-cfg.sh dynamic library.gpr $(CFLAGS_SHARED) >$(GNAT_PROJECT)
#	@echo "Making Ada shared-lib:"
#	@-$(SHELL) -c "diff -c library.gpr $(GNAT_PROJECT); exit 0"
#	$(ADAMAKE) $(ADAMAKEFLAGS) -XLIB_KIND=dynamic
#	-rm -f $(GNAT_PROJECT)

install \
install.libs :: $(ADA_INCLUDE)
	$(INSTALL_LIB) \
		$(SOURCE_DIR_SRC)/*.ad[sb] \
		$(ADA_INCLUDE)

install \
install.libs :: $(ADA_INCLUDE)
	$(INSTALL_LIB) \
		$(GENERATED_SOURCES) \
		$(ADA_INCLUDE)

uninstall \
uninstall.libs ::
	$(SHELL) -c 'for name in $(SOURCE_DIR_SRC)/*.ad[sb] $(GENERATED_SOURCES); do rm -f $(ADA_INCLUDE)/`basename $$name`; done'

#install \
#install.libs :: $(ADA_OBJECTS) $(LIBDIR)
#	$(INSTALL_LIB) \
#		$(BUILD_DIR)/dynamic-ali/* \
#		$(ADA_OBJECTS)
#	$(INSTALL_LIB) \
#		$(BUILD_DIR_LIB)/$(SHARED_LIBNAME) \
#		$(LIBDIR)
#	( cd $(LIBDIR) && $(LN_S) $(SHARED_LIBNAME) $(SHARED_SYMLINK) )
#
#uninstall \
#uninstall.libs ::
#	$(SHELL) -c 'for name in $(BUILD_DIR)/dynamic-ali/* ; do rm -f $(ADA_OBJECTS)/`basename $$name`; done'
#
#uninstall \
#uninstall.libs ::
#	rm -f $(LIBDIR)/$(SHARED_SYMLINK)
#	rm -f $(LIBDIR)/$(SHARED_LIBNAME)

#rm-docs :
#	gnatdoc --enable-build $(ADAMAKEFLAGS) -XLIB_KIND=static

clean ::
	-rm -f default.cgpr
	-rm -rf $(BUILD_DIR)/*-ali
	-rm -rf $(BUILD_DIR)/*-obj
	-rm -rf $(BUILD_DIR_LIB)
##	gprclean $(ADAMAKEFLAGS) -XLIB_KIND=static
##	gprclean $(ADAMAKEFLAGS) -XLIB_KIND=dynamic

# generated by Ada95/mk-1st.awk

$(ALIB).o : \
		$(srcdir)/$(ALIB).ads
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ALIB).ads

$(ABASE)-aux.o : \
		$(srcdir)/$(ABASE)-aux.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-aux.adb

$(ABASE).o : \
		$(ABASE).adb
	$(ADA) $(ADAFLAGS) -c -o $@ $(ABASE).adb

$(ABASE)-terminfo.o : \
		$(srcdir)/$(ABASE)-terminfo.ads \
		$(srcdir)/$(ABASE)-terminfo.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-terminfo.adb

$(ABASE)-termcap.o : \
		$(srcdir)/$(ABASE)-termcap.ads \
		$(srcdir)/$(ABASE)-termcap.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-termcap.adb

$(ABASE)-putwin.o : \
		$(srcdir)/$(ABASE)-putwin.ads \
		$(srcdir)/$(ABASE)-putwin.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-putwin.adb

$(ABASE)-trace.o : \
		$(ABASE)-trace.ads \
		$(ABASE)-trace.adb
	$(ADA) $(ADAFLAGS) -c -o $@ $(ABASE)-trace.adb

$(ABASE)-mouse.o : \
		$(ABASE)-mouse.ads \
		$(srcdir)/$(ABASE)-mouse.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-mouse.adb

$(ABASE)-panels.o : \
		$(ABASE)-panels.ads \
		$(srcdir)/$(ABASE)-panels.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-panels.adb

$(ABASE)-menus.o : \
		$(ABASE)-menus.ads \
		$(srcdir)/$(ABASE)-menus.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-menus.adb

$(ABASE)-forms.o : \
		$(ABASE)-forms.ads \
		$(srcdir)/$(ABASE)-forms.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-forms.adb

$(ABASE)-forms-field_types.o : \
		$(ABASE)-forms-field_types.ads \
		$(srcdir)/$(ABASE)-forms-field_types.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-forms-field_types.adb

$(ABASE)-forms-field_types-alpha.o : \
		$(srcdir)/$(ABASE)-forms-field_types-alpha.ads \
		$(srcdir)/$(ABASE)-forms-field_types-alpha.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-forms-field_types-alpha.adb

$(ABASE)-forms-field_types-alphanumeric.o : \
		$(srcdir)/$(ABASE)-forms-field_types-alphanumeric.ads \
		$(srcdir)/$(ABASE)-forms-field_types-alphanumeric.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-forms-field_types-alphanumeric.adb

$(ABASE)-forms-field_types-intfield.o : \
		$(srcdir)/$(ABASE)-forms-field_types-intfield.ads \
		$(srcdir)/$(ABASE)-forms-field_types-intfield.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-forms-field_types-intfield.adb

$(ABASE)-forms-field_types-numeric.o : \
		$(srcdir)/$(ABASE)-forms-field_types-numeric.ads \
		$(srcdir)/$(ABASE)-forms-field_types-numeric.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-forms-field_types-numeric.adb

$(ABASE)-forms-field_types-regexp.o : \
		$(srcdir)/$(ABASE)-forms-field_types-regexp.ads \
		$(srcdir)/$(ABASE)-forms-field_types-regexp.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-forms-field_types-regexp.adb

$(ABASE)-forms-field_types-enumeration.o : \
		$(srcdir)/$(ABASE)-forms-field_types-enumeration.ads \
		$(srcdir)/$(ABASE)-forms-field_types-enumeration.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-forms-field_types-enumeration.adb

$(ABASE)-forms-field_types-ipv4_address.o : \
		$(srcdir)/$(ABASE)-forms-field_types-ipv4_address.ads \
		$(srcdir)/$(ABASE)-forms-field_types-ipv4_address.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-forms-field_types-ipv4_address.adb

$(ABASE)-forms-field_types-user.o : \
		$(srcdir)/$(ABASE)-forms-field_types-user.ads \
		$(srcdir)/$(ABASE)-forms-field_types-user.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-forms-field_types-user.adb

$(ABASE)-forms-field_types-user-choice.o : \
		$(srcdir)/$(ABASE)-forms-field_types-user-choice.ads \
		$(srcdir)/$(ABASE)-forms-field_types-user-choice.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-forms-field_types-user-choice.adb

$(ABASE)-text_io.o : \
		$(srcdir)/$(ABASE)-text_io.ads \
		$(srcdir)/$(ABASE)-text_io.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-text_io.adb

$(ABASE)-text_io-aux.o : \
		$(srcdir)/$(ABASE)-text_io-aux.ads \
		$(srcdir)/$(ABASE)-text_io-aux.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-text_io-aux.adb

$(ABASE)-menus-menu_user_data.o : \
		$(ABASE)-menus-menu_user_data.ads \
		$(srcdir)/$(ABASE)-menus-menu_user_data.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-menus-menu_user_data.adb

$(ABASE)-menus-item_user_data.o : \
		$(ABASE)-menus-item_user_data.ads \
		$(srcdir)/$(ABASE)-menus-item_user_data.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-menus-item_user_data.adb

$(ABASE)-forms-form_user_data.o : \
		$(ABASE)-forms-form_user_data.ads \
		$(srcdir)/$(ABASE)-forms-form_user_data.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-forms-form_user_data.adb

$(ABASE)-forms-field_user_data.o : \
		$(ABASE)-forms-field_user_data.ads \
		$(srcdir)/$(ABASE)-forms-field_user_data.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-forms-field_user_data.adb

$(ABASE)-forms-field_types-enumeration-ada.o : \
		$(srcdir)/$(ABASE)-forms-field_types-enumeration-ada.ads \
		$(srcdir)/$(ABASE)-forms-field_types-enumeration-ada.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-forms-field_types-enumeration-ada.adb

$(ABASE)-panels-user_data.o : \
		$(ABASE)-panels-user_data.ads \
		$(srcdir)/$(ABASE)-panels-user_data.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-panels-user_data.adb

$(ABASE)-text_io-integer_io.o : \
		$(srcdir)/$(ABASE)-text_io-integer_io.ads \
		$(srcdir)/$(ABASE)-text_io-integer_io.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-text_io-integer_io.adb

$(ABASE)-text_io-float_io.o : \
		$(srcdir)/$(ABASE)-text_io-float_io.ads \
		$(srcdir)/$(ABASE)-text_io-float_io.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-text_io-float_io.adb

$(ABASE)-text_io-fixed_io.o : \
		$(srcdir)/$(ABASE)-text_io-fixed_io.ads \
		$(srcdir)/$(ABASE)-text_io-fixed_io.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-text_io-fixed_io.adb

$(ABASE)-text_io-decimal_io.o : \
		$(srcdir)/$(ABASE)-text_io-decimal_io.ads \
		$(srcdir)/$(ABASE)-text_io-decimal_io.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-text_io-decimal_io.adb

$(ABASE)-text_io-enumeration_io.o : \
		$(srcdir)/$(ABASE)-text_io-enumeration_io.ads \
		$(srcdir)/$(ABASE)-text_io-enumeration_io.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-text_io-enumeration_io.adb

$(ABASE)-text_io-modular_io.o : \
		$(srcdir)/$(ABASE)-text_io-modular_io.ads \
		$(srcdir)/$(ABASE)-text_io-modular_io.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-text_io-modular_io.adb

$(ABASE)-text_io-complex_io.o : \
		$(srcdir)/$(ABASE)-text_io-complex_io.ads \
		$(srcdir)/$(ABASE)-text_io-complex_io.adb \
		$(BASEDEPS)
	$(ADA) $(ADAFLAGS) -c -o $@ $(srcdir)/$(ABASE)-text_io-complex_io.adb

