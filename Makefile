# written to be compatible with Code::Blocks

CC  = clang
CXX = clang++
# CC  = gcc
# CXX = g++

OUTDIR = bin/$(TYPE)
OBJDIR = obj/$(TYPE)
SRCDIR = src
ICDDIR = include

FLAGS    = -Wall -I$(ICDDIR) -I$(SRCDIR)
CFLAGS   = $(FLAGS)
CXXFLAGS = $(FLAGS) --std=c++11

PROJECT = main
TYPE = Debug


MKDIR = mkdir -p
RM = rm -r


all: directories $(patsubst %,$(OBJDIR)/%.o, CSVparser CSVwriter schulerparser) $(OUTDIR)/$(PROJECT)

directories: $(OBJDIR) $(OUTDIR)

$(OUTDIR):
	$(MKDIR) $(OUTDIR)

$(OBJDIR):
	$(MKDIR) $(OBJDIR)


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC)  $(CFLAGS)   -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


$(OBJDIR)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

$(OUTDIR)/$(PROJECT):  $(OBJDIR)/main.o $(OBJDIR)/CSVparser.o $(OBJDIR)/schulerparser.o 
	$(CXX) $(CXXFLAGS) $(OBJDIR)/main.o $(OBJDIR)/CSVparser.o $(OBJDIR)/schulerparser.o -o $(OUTDIR)/$(PROJECT)


run: all
	$(OUTDIR)/$(PROJECT) $(ARGS)


__clean:
	$(RM) $(OUTDIR)
	$(RM) $(OBJDIR)

rebuild: __clean all

clean: rebuild
