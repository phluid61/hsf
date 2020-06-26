.SUFFIXES:
CC=/usr/bin/gcc
CFLAGS=-Wall
OBJ_CFLAGS=-pie -fPIC -Wl,--relocatable
LIB_CFLAGS=-pie -fPIC --shared
CP=/bin/cp
