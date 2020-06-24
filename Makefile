include Makefile.inc

SRCDIR=./src
OBJDIR=./obj
LIBDIR=./lib

OBJECTS :=
HEADERS :=
LIBS    :=

# Names of individual objects/modules
NAMES = integer decimal string token bytesequence boolean

# Dependencies shared by all objects/modules
DEPS  = $(SRCDIR)/_types.h

# Specific dependencies/headers/etc. can be defined by:
#
#foo_SOURCE = some-file.c
#foo_HEADER = some-file.h
#foo_DEPS   = include.inc header.h et.c
#

.PHONY: all
all: lib

define LIBRARY_RULES
ifeq (,$$(findstring /$(1).o,$$(OBJECTS)))
	OBJECTS += $(OBJDIR)/$(1).o
	HEADERS += $(LIBDIR)/$(1).h
	LIBS    += $(LIBDIR)/$(1).so
endif
$(1)_SOURCE ?= $$(SRCDIR)/$(1).c
$(1)_HEADER ?= $$(SRCDIR)/$(1).h
$(1)_DEPS   ?= 
$(OBJDIR)/$(1).o: $$($(1)_SOURCE) $$($(1)_HEADER) $$($(1)_DEPS) $$(DEPS)
	$$(CC) $$(OBJ_CFLAGS) $$(CFLAGS) -c $$< -o $$@
$(LIBDIR)/$(1).so: $(OBJDIR)/$(1).o
	$$(CC) -shared $$< -o $$@
endef
$(foreach lib,$(NAMES),$(eval $(call LIBRARY_RULES,$(lib))))

$(LIBDIR)/%.h: $(SRCDIR)/%.h
	$(CP) $< $@

.PHONY: lib clean
lib: $(HEADERS) $(LIBS)
clean:
	-rm $(OBJECTS) $(LIBS) $(HEADERS) $(TESTS) $(TEST_OBJECTS) $(BENCHES) $(BENCH_OBJECTS)

.PHONY: always
always:
	true
