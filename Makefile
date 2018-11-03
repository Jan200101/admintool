
CC          ?= gcc
CXX         ?= g++

OUTDIR       = bin/$(TYPE)
OBJDIR       = obj/$(TYPE)
SOURCEDIR    = src
INCLUDEDIR   = include

COMMONFLAGS  = -I$(INCLUDEDIR) -I$(SOURCEDIR) -Wall --ansi -Wpedantic
COMMONFLAGS += $(FLAGS)
CFLAGS       = $(COMMONFLAGS) --std=c11
CXXFLAGS     = $(COMMONFLAGS) --std=c++11

PROJECT      = admintool
TYPE         = Debug

MKDIR        = mkdir -p
RM           = rm -r

all: directories $(OUTDIR)/$(PROJECT)

directories: $(OBJDIR) $(OUTDIR)

$(OUTDIR):
	$(MKDIR) $(OUTDIR)

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

$(OBJDIR)/%.o: $(SOURCEDIR)/%.c
	$(CC)  $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(SOURCEDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTDIR)/$(PROJECT): $(OBJDIR)/main.o $(OBJDIR)/menu.o $(OBJDIR)/schulerparser.o $(OBJDIR)/CSVparser.o $(OBJDIR)/CSVwriter.o
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/$(PROJECT) $^

run: all
	$(OUTDIR)/$(PROJECT) $(ARGS)


__clean:
	-$(RM) $(OUTDIR)
	-$(RM) $(OBJDIR)

rebuild: __clean all

clean: rebuild
