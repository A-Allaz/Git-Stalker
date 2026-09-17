CC		 := gcc
CXX      := g++
CPPFLAGS := -Iinclude -Iinclude/datatypes -Iinclude/interface
CFLAGS   := -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=200112L -D_DEFAULT_SOURCE
CXXFLAGS := -Wall -Wextra -std=c++17 -MMD -MP

TARGET    := git-stalker
BUILD_DIR := .build

VPATH := \
	src \
	src/datatypes/file \
	src/datatypes/repository \
	src/datatypes/function \
	src/datatypes/function \
	src/datatypes/repository \
	src/interface \
	src/interface/selectors \
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
	storage.o \
	repository_selector.o

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

# -------------------------------------------------------------------------------------------------
# nlohmann/json dependency
# -------------------------------------------------------------------------------------------------

JSON_DIR := .dependencies/json

CPPFLAGS += -I$(JSON_DIR)/include

# -------------------------------------------------------------------------------------------------
# Tree-sitter dependencies
# -------------------------------------------------------------------------------------------------

TREE_SITTER_DIR := .dependencies/tree-sitter
TS_TYPESCRIPT_DIR := .dependencies/tree-sitter-typescript

TREE_SITTER_OBJ := $(BUILD_DIR)/tree-sitter.o
TS_TYPESCRIPT_PARSER_OBJ := $(BUILD_DIR)/tree-sitter-typescript-parser.o
TS_TYPESCRIPT_SCANNER_OBJ := $(BUILD_DIR)/tree-sitter-typescript-scanner.o

TREE_SITTER_OBJS := \
	$(TREE_SITTER_OBJ) \
	$(TS_TYPESCRIPT_PARSER_OBJ) \
	$(TS_TYPESCRIPT_SCANNER_OBJ)

CPPFLAGS += -I$(TREE_SITTER_DIR)/lib/include

OBJ += $(TREE_SITTER_OBJS)

$(TARGET): $(TREE_SITTER_OBJS)

$(TREE_SITTER_OBJ): $(TREE_SITTER_DIR)/lib/src/lib.c | $(BUILD_DIR)
	$(CC) \
		-I$(TREE_SITTER_DIR)/lib/src \
		-I$(TREE_SITTER_DIR)/lib/include \
		$(CFLAGS) \
		-c $< \
		-o $@

$(TS_TYPESCRIPT_PARSER_OBJ): $(TS_TYPESCRIPT_DIR)/typescript/src/parser.c | $(BUILD_DIR)
	$(CC) \
		-I$(TS_TYPESCRIPT_DIR)/typescript/src \
		$(CFLAGS) \
		-c $< \
		-o $@

$(TS_TYPESCRIPT_SCANNER_OBJ): $(TS_TYPESCRIPT_DIR)/typescript/src/scanner.c | $(BUILD_DIR)
	$(CC) \
		-I$(TS_TYPESCRIPT_DIR)/typescript/src \
		$(CFLAGS) \
		-c $< \
		-o $@

# -------------------------------------------------------------------------------------------------
# FTXUI dependency
# -------------------------------------------------------------------------------------------------

FTXUI_DIR       := .dependencies/FTXUI
FTXUI_BUILD_DIR := $(FTXUI_DIR)/build
FTXUI_STAMP     := $(FTXUI_BUILD_DIR)/.built

FTXUI_LIBS := \
	$(FTXUI_BUILD_DIR)/libftxui-component.a \
	$(FTXUI_BUILD_DIR)/libftxui-dom.a \
	$(FTXUI_BUILD_DIR)/libftxui-screen.a

CPPFLAGS += -I$(FTXUI_DIR)/include

OBJ += $(FTXUI_LIBS)

$(TARGET): $(FTXUI_LIBS)

$(FTXUI_LIBS): $(FTXUI_STAMP)

$(FTXUI_STAMP):
	cmake \
		-S $(FTXUI_DIR) \
		-B $(FTXUI_BUILD_DIR) \
		-DCMAKE_BUILD_TYPE=Release \
		-DFTXUI_BUILD_DOCS=OFF \
		-DFTXUI_BUILD_EXAMPLES=OFF \
		-DFTXUI_BUILD_TESTS=OFF \
		-DFTXUI_ENABLE_INSTALL=OFF
	cmake --build $(FTXUI_BUILD_DIR) --parallel
	touch $@

.PHONY: ftxui clean-ftxui

ftxui: $(FTXUI_LIBS)

clean: clean-ftxui

clean-ftxui:
	rm -rf $(FTXUI_BUILD_DIR)