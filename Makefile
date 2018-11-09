PROJECT         := $(shell basename $(CURDIR))
DEBUG           ?= 0
ifeq ($(DEBUG), 1)
    TARGET      := Debug
else
    TARGET      := Release
endif

OUT_DIR          = bin
OBJ_DIR          = obj
SRC_DIR          = src
INC_DIR          = include

CXX_SRC_FILES   := $(wildcard $(SRC_DIR)/*.cpp)
CC_SRC_FILES    := $(wildcard $(SRC_DIR)/*.c)

OBJ_FILES       := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/$(TARGET)/%.o,$(CXX_SRC_FILES)) \
                   $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/$(TARGET)/%.o,$(CC_SRC_FILES))

LIBS            := -I$(INC_DIR) -I$(SRC_DIR)
COMMONFLAGS      = -Wall -Wextra -Winit-self -Wuninitialized -Wpointer-arith -Wcast-align -Wunreachable-code --ansi -Wpedantic
COMMONFLAGS     += $(FLAGS) $(LIBS)
ifeq ($(DEBUG), 1)
    COMMONFLAGS += -g -DDEBUG
else
    COMMONFLAGS += -O3
endif
CFLAGS          := $(COMMONFLAGS) --std=c11
CXXFLAGS        := $(COMMONFLAGS) --std=c++11

MKDIR           := mkdir -p
RM              := rm -r

default_target: directories all

all: $(OUT_DIR)/$(TARGET)/$(PROJECT)

directories:
	@$(MKDIR) $(OUT_DIR)/$(TARGET)
	@$(MKDIR) $(OBJ_DIR)/$(TARGET)

$(OBJ_DIR)/$(TARGET)/%.o: $(SRC_DIR)/%.c
	@echo [CC] $@
	@$(CC)  $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/$(TARGET)/%.o: $(SRC_DIR)/%.cpp
	@echo [CXX] $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUT_DIR)/$(TARGET)/$(PROJECT): $(OBJ_FILES)
	@echo [CXX] $@
	@$(CXX) $(CXXFLAGS) -o $@ $^


rmdirectories:
	@-$(RM) $(OUT_DIR) 2> /dev/null
	@-$(RM) $(OBJ_DIR) 2> /dev/null

clean: rmdirectories

loc:
	-find . -name '*.cpp' -o -name '*.c' -o -name '*.h'| xargs wc -l
