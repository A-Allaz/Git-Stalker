CXX      := g++
CPPFLAGS := -Iinclude
CXXFLAGS := -Wall -Wextra -std=c++17 -MMD -MP

TARGET := git-stalker

VPATH := \
	src \
	src/datatypes/file \
	src/datatypes/function \
	src/datatypes/repository \
	src/interface \
	src/mapper \
	src/parser \
	src/storage

OBJ := \
	main.o \
	file.o \
	function.o \
	repository.o \
	interface.o \
	debug.o \
	mapper.o \
	repository_parser.o \
	storage.o

DEP := $(OBJ:.o=.d)

.PHONY: all build clean

all: build

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP) $(TARGET)
