CXX 			= g++
CXXFLAGS		= -Wall -O2 -std=gnu++11 -D _GRADUAL_CHANGE
LDFLAGS			=

SOURCES			= $(wildcard *.cc)
OBJECTS			= ${SOURCES:.cc=.o}
TARGET			= _bright
RUNSCRIPT		= bright

INSTALL_PREFIX	= /usr/local

.PHONY: all clean distclean install

all: $(SOURCES) $(TARGET)
$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@
clean:
	@- $(RM) $(TARGET)
	@- $(RM) $(OBJECTS)

distclean: clean

install: $(TARGET) $(RUNSCRIPT)
	install $(RUNSCRIPT) $(INSTALL_PREFIX)/bin
	install $(TARGET) $(INSTALL_PREFIX)/bin

# NOTE: if you don't like the gradual brightness change, remove `-D _GRADUAL_CHANGE`
# from the CXXFLAGS; this will make the change instantaneous.
