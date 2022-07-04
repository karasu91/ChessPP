# generic build

CXX = g++

# Compiler flags
# -Wall		- turn all compiler warnings on

CXXFLAGS	= -std=c++20 -O2 -Wall -g -I./lib/include/ -L./usr/local/

SRCDIR = .
OBJDIR = ./obj
BUILDDIR = ./build
SRCFILES = $(wildcard $(SRCDIR)/*.cpp)
OBJFILES = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCFILES))

DIRS=$(OBJDIR) $(BUILDDIR)
LIBDIR = ./lib

$(shell mkdir -p $(DIRS))
$(shell mkdir -p $(LIBDIR) && cd $(LIBDIR) && cmake ../lib/wt/ && DESTDIR=$(LIBDIR) make install -j20)

# The build target
TARGET = client

main: $(OBJFILES)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILDDIR)/$@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm $(OBJDIR) $(BUILDDIR) -rf

