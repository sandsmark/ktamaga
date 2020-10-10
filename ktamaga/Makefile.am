# this 10 paths are KDE specific. Use them:
# kde_htmldir       Where your docs should go to. (contains lang subdirs)
# kde_appsdir       Where your application file (.kdelnk) should go to. 
# kde_icondir       Where your icon should go to.
# kde_minidir       Where your mini icon should go to.
# kde_datadir       Where you install application data. (Use a subdir)
# kde_locale        Where translation files should go to.(contains lang subdirs)
# kde_cgidir        Where cgi-bin executables should go to.
# kde_confdir       Where config files should go to.
# kde_mimedir       Where mimetypes should go to.
# kde_toolbardir    Where general toolbar icons should go to.
# kde_wallpaperdir  Where general wallpapers should go to.

# just set the variable
APPSDIR = $(kde_appsdir)/Games
# set the include path for X, qt and KDE
INCLUDES= @all_includes@
# claim, which subdirectories you want to install
SUBDIRS = doc data datapre

#DEFS = @DEFS@ -I. -I$(srcdir) -I.. -DDOTRACE
####### This part is very ktamaga specific
# you can add here more. This one gets installed 
bin_PROGRAMS = 	ktamaga
noinst_PROGRAMS = convert

# Which sources should be compiled for ktamaga.
ktamaga_SOURCES	= conf.cpp confData.cpp ktamaga.cpp ktamagasched.cpp ktamagastat.cpp main.cpp tamdata.cpp tlcd.cpp conf.moc.cpp confData.moc.cpp ktamaga.moc.cpp tlcd.moc.cpp
convert_SOURCES = convert.cpp tamdata.cpp

# the library search path
ktamaga_LDFLAGS = @all_libraries@ @KDE_RPATH@
convert_LDFLAGS = @all_libraries@ @KDE_RPATH@

# the libraries to link against. Be aware of the order. First the libraries,
# that depend on the following ones.
ktamaga_LDADD  = -lkdeui -lkdecore -lqt -lX11 -lXext @LIBSOCKET@     
convert_LDADD  = -lqt -lX11 -lXext @LIBSOCKET@

# this option you can leave out. Just, if you use "make dist", you need it
noinst_HEADERS = conf.h confData.h ktamaga.h tamagadefs.h tamdata.h tlcd.h

# just to make sure, automake makes them 
BUILTSOURCES =	conf.moc.cpp confData.moc.cpp ktamaga.moc.cpp tlcd.moc.cpp

EXTRA_DIST = ktamaga.kdelnk ktamaga.xpm

# if you "make distclean", this files get removed. If you want to remove
# them while "make clean", use CLEANFILES
CLEANFILES = $(BUILTSOURCES)

# make messages.po. Move this one to ../po/ and "make merge" in po
messages:
	$(XGETTEXT) -C -ki18n $(ktamaga_SOURCES)

# just install datas here. Use install-exec-data for scripts and etc.
# the binary itself is already installed from automake
# use mkinstalldirs, not "install -d"
# don't install a list of file. Just one file per install.
# if you have more of them, create a subdirectory with an extra Makefile 
install-data-local: 
	$(mkinstalldirs) $(APPSDIR)
	$(INSTALL_DATA) ktamaga.kdelnk $(APPSDIR)
	$(mkinstalldirs) $(kde_icondir)
	$(INSTALL_DATA) ktamaga.xpm $(kde_icondir)
	$(mkinstalldirs) $(kde_datadir)/ktamaga/
	$(INSTALL_DATA) data/* $(kde_datadir)/ktamaga/

# remove ALL you have installed in install-data-local or install-exec-local
uninstall-local:
	-rm -f $(APPSDIR)/ktamaga.kdelnk
	-rm -f $(kde_icondir)/ktamaga.xpm
	-rm -f $(kde_datadir)/ktamaga/*

# add a dependency for every moc file to be full portable
conf.moc.cpp: conf.h
	$(MOC) conf.h -o conf.moc.cpp

confData.moc.cpp: confData.h
	$(MOC) confData.h -o confData.moc.cpp

tlcd.moc.cpp: tlcd.h
	$(MOC) tlcd.h -o tlcd.moc.cpp

ktamaga.moc.cpp: ktamaga.h
	$(MOC) ktamaga.h -o ktamaga.moc.cpp

