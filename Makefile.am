bin_PROGRAMS = brightness_agan2k

brightness_agan2k_SOURCES = \
	src/main.c
dist_doc_DATA = LICENSE
dist_man_MANS = $(srcdir)/brightness_agan2k.1
EXTRA_DIST = $(srcdir)/scripts/*

install-data-local:
	install -g wheel -m 644 $(srcdir)/agan.conf /usr/local/etc/devd/
