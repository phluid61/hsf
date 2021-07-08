include Makefile.inc

SRCDIR=./src
OBJDIR=./obj
LIBDIR=./lib

HEADERS := $(LIBDIR)/types.h $(LIBDIR)/errors.h $(LIBDIR)/error_macros.h
OBJECTS :=
LIBS    :=

# Names of individual objects/modules
NAMES = integer decimal string token bytesequence boolean innerlist bareitem item key _dict list

# Dependencies shared by all objects/modules
DEPS  = Makefile $(SRCDIR)/types.h $(SRCDIR)/errors.h $(SRCDIR)/error_macros.h

# Specific dependencies/headers/etc. can be defined by:
#
#foo_SOURCE = some-file.c
#foo_HEADER = some-file.h
#foo_DEPS   = include.inc header.h et.c
#

_dict_DEPS    = $(SRCDIR)/key.h $(SRCDIR)/item.h
bareitem_DEPS = $(SRCDIR)/integer.h $(SRCDIR)/decimal.h $(SRCDIR)/string.h $(SRCDIR)/token.h $(SRCDIR)/bytesequence.h $(SRCDIR)/boolean.h
item_DEPS     = $(SRCDIR)/_dict.h $(_dict_DEPS) $(SRCDIR)/bareitem.h $(bareitem_DEPS)
list_DEPS     = $(SRCDIR)/item.h

.PHONY: all
all: dirs lib main

$(LIBDIR)/:
	mkdir -p $@
$(OBJDIR)/:
	mkdir -p $@

### OBJECTS AND LIBRARIES

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
	$$(CC) $$(OBJ_CFLAGS) $$(CFLAGS) -o $$@ -c $$<
$(LIBDIR)/$(1).so: $(OBJDIR)/$(1).o
	$$(CC) $$(LIB_CFLAGS) -o $$@ $$<
endef
$(foreach lib,$(NAMES),$(eval $(call LIBRARY_RULES,$(lib))))

$(LIBDIR)/%.h: $(SRCDIR)/%.h
	$(CP) $< $@

### MAIN HARNESS PROGRAM

MAINOPTS =
MAINOPTS += -DNO_NULL
MAINOPTS += -DNO_INTEGER
MAINOPTS += -DNO_DECIMAL
MAINOPTS += -DNO_STRING
MAINOPTS += -DNO_TOKEN
MAINOPTS += -DNO_BYTESEQ
MAINOPTS += -DNO_BOOLEAN
MAINOPTS += -DNO_PARAMETERS
MAINOPTS += -DNO_LIST
#MAINOPTS += -DNO_INNERLIST

main.o: main.c $(HEADERS) $(DEPS)
	$(CC) $(MAINOPTS) $(CFLAGS) -c $< -o $@
main: main.o $(OBJECTS)
	$(LINK.o) -o $@ $^ -lm
.PHONY: run
run: all
	-./main

### META-RULES

.PHONY: dirs obj lib clean
dirs: $(LIBDIR)/ $(OBJDIR)/
obj: $(HEADERS) $(OBJECTS)
lib: $(HEADERS) $(LIBS)
clean:
	-rm -f $(OBJECTS) $(LIBS) $(HEADERS) main.o main

.PHONY: always
always:
	true

# vim: set ts=4 sts=4 sw=4:
