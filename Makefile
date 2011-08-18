OBJECTS=src/getopt_pp.o

CPPFLAGS=-Wall

EXAMPLES_SRCS=$(wildcard examples/example_*.cpp)
EXAMPLES_OBJS=$(patsubst %.cpp,%.o,$(EXAMPLES_SRCS))
EXAMPLE_BIN=$(patsubst %.cpp,%,$(EXAMPLES_SRCS))

_PREFIX=$(if $(PREFIX),$(PREFIX),/usr)
INSTALL_DIR=$(_PREFIX)/lib
DEV_INSTALL_DIR=$(_PREFIX)/include


ifeq ($(SHARED),n)
library: libgetopt_pp.a
$(EXAMPLE_BIN): libgetopt_pp.a
install_lib: libgetopt_pp.a 
else
CPPFLAGS:=$(CPPFLAGS) -fPIC
library: libgetopt_pp.so
$(EXAMPLE_BIN): libgetopt_pp.so
install_lib: libgetopt_pp.so 
endif

libgetopt_pp.a: $(OBJECTS)
	ar -cvq $@ $^

libgetopt_pp.so: $(OBJECTS)
	g++ -shared -o $@ $^

examples: $(EXAMPLES_OBJS) $(EXAMPLE_BIN)


$(EXAMPLE_BIN): 
	g++ -o $@ $@.o -lgetopt_pp -L.

.PHONY: clean install install_dev

clean:
	@rm -rf $(OBJECTS) libgetopt_pp.so libgetopt_pp.a $(EXAMPLE_BIN) src/*.o examples/*.o

install_lib: 
	cp -f $^ $(INSTALL_DIR)
ifneq ($(SHARED),n)
	ldconfig
endif 

install_headers: getoptpp/getopt_pp.h 
	cp -f $^ $(DEV_INSTALL_DIR)

install: install_lib install_headers
