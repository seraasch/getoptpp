


OBJECTS=getopt_pp.o

CPPFLAGS=-Wall

EXAMPLES_SRCS=$(wildcard example_*.cpp)
EXAMPLES_OBJS=$(patsubst %.cpp,%.o,$(EXAMPLES_SRCS))
EXAMPLE_BIN=$(patsubst %.cpp,%,$(EXAMPLES_SRCS))

INSTALL_DIR=/usr/lib

ifeq ($(SHARED),n)
library: libgetopt_pp.a clean
$(EXAMPLE_BIN): libgetopt_pp.a
install: libgetopt_pp.a 
else
CPPFLAGS:=$(CPPFLAGS) -fPIC
library: libgetopt_pp.so clean
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

.PHONY: clean install

clean:
	@rm -rf $(OBJECTS) libgetopt_pp.so libgetopt_pp.a $(EXAMPLE_BIN) *.o

install: 
	cp -f $^ $(INSTALL_DIR)
	ldconfig 


