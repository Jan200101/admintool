PROJECT      = $(shell basename $(CURDIR))
TYPE         = Debug

CC            ?= gcc
CXX           ?= g++

OUT_DIR        = bin/$(TYPE)
OBJ_DIR        = obj/$(TYPE)
SRC_DIR        = src
INC_DIR        = include

CXX_SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
CC_SRC_FILES  := $(wildcard $(SRC_DIR)/*.c)

OBJ_FILES     := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CXX_SRC_FILES)) \
                 $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(CC_SRC_FILES))

COMMONFLAGS    = -I$(INC_DIR) -I$(SRC_DIR)
COMMONFLAGS   += -g -Wall -Wextra -Winit-self -Wuninitialized -Wpointer-arith -Wcast-align -Wunreachable-code --ansi -Wpedantic
COMMONFLAGS   += $(FLAGS)
CFLAGS        := $(COMMONFLAGS) --std=c11
CXXFLAGS      := $(COMMONFLAGS) --std=c++11

MKDIR         := mkdir -p
RM            := rm -r

default_target: directories all

all: $(OUT_DIR)/$(PROJECT)

directories: $(OBJ_DIR) $(OUT_DIR)

$(OUT_DIR):
	@$(MKDIR) $(OUT_DIR)

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC)  $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUT_DIR)/$(PROJECT): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/$(PROJECT) $^

run: all
	$(OUT_DIR)/$(PROJECT) $(ARGS)


rmdirectories:
	-$(RM) $(OUT_DIR)
	-$(RM) $(OBJ_DIR)

rebuild: rmdirectories directories all

clean: rebuild

loc:
	-find . -name '*.cpp' -o -name '*.c' -o -name '*.h'| xargs wc -l
