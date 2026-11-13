CC		 := gcc
CXX      := g++
CPPFLAGS := -Iinclude \
	-Iinclude/datatypes \
	-Iinclude/interface \
	-Iinclude/parser \
	-Iinclude/mapper \
	-Iinclude/utils \
	-Iinclude/storage 

CFLAGS   := -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=200112L -D_DEFAULT_SOURCE
CXXFLAGS := -Wall -Wextra -std=c++17 -MMD -MP

CPPFLAGS += $(shell pkg-config --cflags libgit2)
LDLIBS   += $(shell pkg-config --libs libgit2)

TARGET    := git-stalker
BUILD_DIR := .build

PREFIX    ?= $(HOME)/.local
BINDIR    ?= $(PREFIX)/bin
DATADIR   ?= $(PREFIX)/share

VPATH := \
	src \
	src/datatypes/file \
	src/datatypes/function \
	src/datatypes/repository \
	src/interface \
	src/interface/selectors \
	src/mapper \
	src/parser \
	src/parser/typescript_parser \
	src/storage \
	src/utils

OBJECT_NAMES := \
	main.o \
	file.o \
	function.o \
	repository.o \
	interface.o \
	debug.o \
	mapper.o \
	repository_parser.o \
	file_parser.o \
	function_parser.o \
	json_handler.o \
	storage_handler.o \
	repository_selector.o \
	mapping_selector.o \
	finder.o \
	logger.o

OBJ := $(addprefix $(BUILD_DIR)/,$(OBJECT_NAMES))
DEP := $(OBJ:.o=.d)

.PHONY: all build clean install install-completions

all: git-submodules install

clean-build: clean build

install: build install-completions
	install -d "$(BINDIR)"
	install -m 755 "$(TARGET)" "$(BINDIR)/$(TARGET)"
	@case ":$$PATH:" in \
		*":$(BINDIR):"*) ;; \
		*) echo "Warning: $(BINDIR) is not in PATH"; \
		   echo 'Add the binary directory to PATH in your shell configuration.';; \
	esac

install-completions:
	@shell='$(COMPLETION_SHELL)'; \
	if [ -z "$$shell" ]; then shell="$${SHELL##*/}"; fi; \
	case "$$shell" in \
		bash) install -d "$(DATADIR)/bash-completion/completions"; \
		      install -m 644 completions/bash/git_stalker "$(DATADIR)/bash-completion/completions/git-stalker" ;; \
		zsh)  install -d "$(DATADIR)/zsh/site-functions"; \
		      install -m 644 completions/zsh/_git-stalker "$(DATADIR)/zsh/site-functions/_git-stalker"; \
		      echo 'For Zsh completion, add $(DATADIR)/zsh/site-functions to fpath before compinit.' ;; \
		*)    echo "No completion installed for shell '$$shell'. Use COMPLETION_SHELL=bash or zsh to choose one." ;; \
	esac

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDLIBS)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

-include $(DEP)

git-submodules:
	git submodule update --init --recursive

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
