# generic build

CXX = g++

# Compiler flags
# -Wall		- turn all compiler warnings on

CXXFLAGS	= -std=c++14 -O2 -Wall -lwt -lwthttp -g -I./lib/build/usr/local/include/ -L./lib/build/usr/local/lib/

SRCDIR = .
OBJDIR = ./obj
BUILDDIR = ./build
SRCFILES = $(wildcard $(SRCDIR)/*.cpp)
OBJFILES = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCFILES))

DIRS=$(OBJDIR) $(BUILDDIR)
LIBDIR = ./lib
TMPDIR = ./tmp

$(shell mkdir -p $(DIRS))

# The build target
TARGET = client

libs:
	$(shell mkdir -p $(TMPDIR) && mkdir -p $(LIBDIR) && cd $(TMPDIR) && cmake ../../lib/wt/ && DESTDIR=./build make install -j20) && cp ./build/usr/* ../$(LIBDIR)

$(TARGET): $(OBJFILES)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILDDIR)/$@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm $(OBJDIR) $(BUILDDIR) $(LIBDIR) -rf

