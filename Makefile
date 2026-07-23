CXX      := g++
CPPFLAGS := -Iinclude
CXXFLAGS := -Wall -Wextra -std=c++17 -MMD -MP

TARGET    := git-stalker
BUILD_DIR := .build

VPATH := \
	src \
	src/datatypes/file \
	src/datatypes/function \
	src/datatypes/repository \
	src/interface \
	src/mapper \
	src/parser \
	src/storage

OBJECT_NAMES := \
	main.o \
	file.o \
	function.o \
	repository.o \
	interface.o \
	debug.o \
	mapper.o \
	repository_parser.o \
	storage.o

OBJ := $(addprefix $(BUILD_DIR)/,$(OBJECT_NAMES))
DEP := $(OBJ:.o=.d)

.PHONY: all build clean

all: build

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

-include $(DEP)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)