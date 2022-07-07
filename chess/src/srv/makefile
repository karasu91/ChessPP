# generic build

CXX = clang++

# Compiler flags
# -Wall		- turn all compiler warnings on

CXXFLAGS	= -std=c++20 -O2 -Wall -g -DCMAKE_CXX_FLAGS='-D_GLIBCXX_USE_CXX11_ABI=0 -DBOOST_ASIO_HAS_STD_CHRONO=0' -lcrypto -lssl
MAKEFLAGS := --jobs=$(shell nproc)

SRCDIR = .
OBJDIR = ./obj
BUILDDIR = ./build
SRCFILES = $(wildcard $(SRCDIR)/*.cpp)
OBJFILES = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCFILES))

DIRS=$(OBJDIR) $(BUILDDIR)

$(shell mkdir -p $(DIRS))

# The build target
TARGET = server

server: $(OBJFILES)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILDDIR)/$@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm $(OBJDIR) $(BUILDDIR) -rf

