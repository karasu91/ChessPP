# generic build

CXX = g++

# Compiler flags
# -Wall		- turn all compiler warnings on

CXXFLAGS	= -std=c++20 -O2 -Wall -g

SRCDIR = .
OBJDIR = ./obj
BUILDDIR = ./build
SRCFILES = $(wildcard $(SRCDIR)/*.cpp)
OBJFILES = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCFILES))

DIRS=$(OBJDIR) $(BUILDDIR)

$(shell mkdir -p $(DIRS))

# The build target
TARGET = main

main: $(OBJFILES)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILDDIR)/$@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm $(OBJDIR) $(BUILDDIR) -rf

