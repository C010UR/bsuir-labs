# tool macros
CXX := g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror -m64 -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable

# path macros
BIN_PATH := bin
SRC_PATH := src

# compile macros
TARGET := $(basename $(notdir $(wildcard $(SRC_PATH)/*.cpp)))
INCLUDE := $(wildcard $(SRC_PATH)/*/*.cpp) $(wildcard $(SRC_PATH)/*/*.hpp)

# default rule
default: makedir all

# non-phony targets
$(TARGET):
	$(CXX) $(CXXFLAGS) -o $(BIN_PATH)/$@ $(SRC_PATH)/$@.cpp $(INCLUDE)

# phony rules
.PHONY: makedir
makedir:
	-@mkdir $(BIN_PATH)

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	- @rm -rf $(BIN_PATH)/
	- @rm -rf $(OBJ_PATH)/