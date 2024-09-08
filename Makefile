SOURCE	= src
OUTPUT	= bin
INCLUDE = inc
LIBRARY = lib

CPPCODE = $(shell find $(SOURCE) -type f -name '*.cc')
OBJECTS	= $(patsubst $(SOURCE)/%.cc, $(OUTPUT)/%.cc.o, $(CPPCODE))

EXECUTE = fargo
PROGRAM	= $(OUTPUT)/$(EXECUTE)
CPPLIBS = $(shell find $(LIBRARY) -type f -name '*.lib')

CC 	= clang++
LD 	= clang++

CCFLAGS = \
-I$(SOURCE) \
-I$(INCLUDE) \
-std=c++17 \
-fpie \
-gdwarf \
-Werror \
-pedantic

LDFLAGS = \
-pie	\
-lGL \
-lX11 \


.DEFAULT-GOAL	= all
.PHONY			= clean install uninstall

all: $(PROGRAM)

$(OUTPUT)/%.cc.o: $(SOURCE)/%.cc
	@ echo "	compile $^"
	@ mkdir -p $(@D)
	@ $(CC) $(CCFLAGS) -c $^ -o $@

$(PROGRAM): $(OBJECTS)
	@ echo "	link $@ (1/1)"
	@ $(LD) $(LDFLAGS) $(OBJECTS) $(CPPLIBS) -o $(PROGRAM)

clean:
	@ rm -rf $(OUTPUT)

# define ARGS in the command line in order to add additional arguments
# ex: make run ARGS="build"
run: $(PROGRAM)
	@ echo "	executing $(PROGRAM)"
	@ echo "	-------"
	@ echo " "
	@ $(PROGRAM) $(ARGS)
	@ echo " "

INSTALL = /usr/local/bin

install: $(PROGRAM)
	@ cp $(PROGRAM) $(INSTALL)/$(EXECUTE)

uninstall:
	@ rm -f $(INSTALL)/$(EXECUTE)
