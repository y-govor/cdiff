DEBUG = 0
CXX = g++

ifeq ($(DEBUG),1)
	CXXFLAGS = -g -Wall -Wextra -std=c++11 -pedantic -Og
else
	CXXFLAGS = -Wall -Wextra -std=c++11 -pedantic -O2
endif

SRC = src
BIN = bin
INCLUDE = include
LIB = lib

OUTFILE = cdiff
LIBRARIES =

ifeq ($(OS),Windows_NT)
	EXECUTABLE = $(OUTFILE).exe
	RM = cmd /c del
else
	EXECUTABLE = $(OUTFILE)
	RM = rm -f
endif

INCLUDES = $(addprefix -I,$(INCLUDE))
LIBS = $(addprefix -L,$(LIB))
SOURCES = $(wildcard $(SRC)/*.cpp)

.PHONY: run clean

all: $(BIN)/$(EXECUTABLE)

run:
	./$(BIN)/$(EXECUTABLE)

clean:
ifeq ($(OS),Windows_NT)
	$(RM) $(BIN)\$(EXECUTABLE)
else
	$(RM) $(BIN)/$(EXECUTABLE)
endif

$(BIN)/$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(INCLUDES) $(LIBS) $(LIBRARIES)
