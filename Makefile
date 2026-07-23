CXX      = g++
CXXFLAGS = -Wall -Iinclude/datatypes/file -Iinclude/datatypes/function -Iinclude/datatypes/repository

VPATH = src/datatypes/file:src/datatypes/function:src/interface:src/mapper:src/datatypes/repository:src/storage:src

HEADERS = include/datatypes/file/file.h include/datatypes/function/function.h include/datatypes/mapping/mapped_type.h include/datatypes/repository/repository.h

OBJ = main.o file.o function.o interface.o mapper.o repository.o storage.o

build: $(OBJ)
	$(CXX) -o git-stalker $(OBJ)

clean:
	rm -f $(OBJ) git-stalker

# Generic pattern rule: every .o depends on ALL headers,
# even ones it doesn't actually need.
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: build clean