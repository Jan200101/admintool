# written to be compatible with Code::Blocks

# use clang for debug builds
CC  = clang
CXX = clang++
# CC  = gcc
# CXX = g++

CFLAGS   = -Wall
CXXFLAGS = -Wall --std=c++11

PROJECT = main
TYPE = Debug

OUTDIR = bin/$(TYPE)
OBJDIR = obj/$(TYPE)

MKDIR = mkdir -p
RM = rm -rf


all: directories prog exit


directories: $(OBJDIR) $(OUTDIR)

$(OUTDIR):
	$(MKDIR) $(OUTDIR)

$(OBJDIR):
	$(MKDIR) $(OBJDIR)


prog: $(OUTDIR)/$(PROJECT)

$(OUTDIR)/$(PROJECT):  $(OBJDIR)/main.o $(OBJDIR)/CSVparser.o $(OBJDIR)/schulerparser.o 
	$(CXX) $(CXXFLAGS) $(OBJDIR)/main.o $(OBJDIR)/CSVparser.o $(OBJDIR)/schulerparser.o -o $(OUTDIR)/$(PROJECT)

$(OBJDIR)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

$(OBJDIR)/CSVparser.o: include/CSVparser.c
	$(CC) $(CCFLAGS) -c $^ -o $@

$(OBJDIR)/CSVwriter.o: include/CSVwriter.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

$(OBJDIR)/schulerparser.o: include/schulerparser.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@
run:
	$(OUTDIR)/$(PROJECT)


__clean:
	$(RM) $(OUTDIR)
	$(RM) $(OBJDIR)

rebuild: __clean all

clean: rebuild


exit:
	@echo
