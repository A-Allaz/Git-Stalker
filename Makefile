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