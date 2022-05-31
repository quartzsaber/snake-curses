CXX = g++
CXXFLAGS = -Wfatal-errors -Wall $(shell pkg-config --cflags ncurses)
LDFLAGS = $(shell pkg-config --libs ncurses)

BIN = snake-curses

CPP = $(wildcard *.cpp)

OBJ = $(CPP:%.cpp=%.o)
DEP = $(OBJ:%.o=%.d)

run: $(BIN)
	-./$(BIN)

$(BIN): $(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

-include $(DEP)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

.PHONY: clean

clean:
	-rm $(BIN) $(OBJ) $(DEP)

