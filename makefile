TAR = mesh
SRC = lib
BUILD = build
CC = g++
OBJ += $(shell ls $(SRC) | egrep *.cpp | sed 's/.cpp/.o/g' | sed 's/^/$(BUILD)\//g')
# compile options
COPTIONS = -Wreturn-type -g
# link options
LOPTIONS = -g

$(shell mkdir build)

$(TAR): $(OBJ)
	$(CC) $^ -o $(TAR) $(LOPTIONS)

# commands
.PHONY:
run: clean_all $(TAR)
	./$(TAR)
.PHONY:
clean:
	rm -f $(BUILD)/* *.o
.PHONY:
clean_all:
	rm -f $(BUILD)/* *.o $(TAR)

# modular build
$(BUILD)/%.o: $(SRC)/%.cpp
	$(CC) -c $^ -o $@ $(COPTIONS)
