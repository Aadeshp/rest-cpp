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
