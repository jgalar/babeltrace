SUBDIRS = trace-ir prio-heap plugin graph

lib_LTLIBRARIES = libbabeltrace2.la

libbabeltrace2_la_SOURCES = \
	assert-pre.h \
	babeltrace2.c \
	lib-logging.c \
	lib-logging.h \
	logging.c \
	object.h \
	object-pool.c \
	object-pool.h \
	property.h \
	util.c \
	value.c \
	value.h

libbabeltrace2_la_LDFLAGS = $(LT_NO_UNDEFINED) \
			-version-info $(BABELTRACE_LIBRARY_VERSION)

libbabeltrace2_la_LIBADD = \
	prio-heap/libprio-heap.la \
	graph/libgraph.la \
	plugin/libplugin.la \
	trace-ir/libtrace-ir.la \
	$(top_builddir)/src/logging/libbabeltrace2-logging.la \
	$(top_builddir)/src/common/libbabeltrace2-common.la \
	$(top_builddir)/src/compat/libcompat.la

if ENABLE_BUILT_IN_PYTHON_PLUGIN_SUPPORT
libbabeltrace2_la_LIBADD += $(top_builddir)/src/python-plugin-provider/libbabeltrace2-python-plugin-provider.la
endif