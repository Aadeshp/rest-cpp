CC = g++
CFLAGS = -Wall -I.

IDIR = ./include
LFLAGS = -lcurl -I$(IDIR)

# change these to set the proper directories where each files shoould be
SRCDIR   = src
BUILDDIR = build
BINDIR   = bin

TARGET = $(BINDIR)/main

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
#INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LFLAGS)

$(OBJECTS): $(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)

$(OBJECTS): | $(BUILDDIR)
$(TARGET): | $(BINDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

#main: $(OBJECTS)
#	$(LINKER) $@ $(LFLAGS) $(OBJECTS) -I./include
#	@echo "Good to go"

#CXX = g++ 
#IDIR = ./include
#SDIR = ./src
#CXXFLAGS = -Wall -g -lcurl -I$(IDIR) -I$(SDIR)
#
#OBJS = WPNetwork.o
#DEPS = WPNetwork.h
#
#%.o: %.cpp $(DEPS)
#	$(CXX) $(CXXFLAGS) -c -o $@ $<
#
#main: $(OBJS)
#	@echo "BAM"
#	$(CXX) $(CXXFLAGS) -o $@ $^
#
#clean:
#	rm main $(OBJS)
