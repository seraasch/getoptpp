


OBJECTS=getopt_pp.o

CPPFLAGS=-Wall

EXAMPLES_SRCS=$(wildcard example_*.cpp)
EXAMPLES_OBJS=$(patsubst %.cpp,%.o,$(EXAMPLES_SRCS))
EXAMPLE_BIN=$(patsubst %.cpp,%,$(EXAMPLES_SRCS))

INSTALL_DIR=/usr/lib
DEV_INSTALL_DIR=/usr/include

ifeq ($(SHARED),n)
library: clean libgetopt_pp.a
$(EXAMPLE_BIN): libgetopt_pp.a
install: libgetopt_pp.a 
else
CPPFLAGS:=$(CPPFLAGS) -fPIC
library: clean libgetopt_pp.so
$(EXAMPLE_BIN): libgetopt_pp.so
install: libgetopt_pp.so 
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
	@rm -rf $(OBJECTS) libgetopt_pp.so libgetopt_pp.a $(EXAMPLE_BIN) *.o

install: 
	cp -f $^ $(INSTALL_DIR)
	ldconfig 

install_headers: getopt_pp.h 
	cp -f $^ $(DEV_INSTALL_DIR)

install_dev: install install_headers
