TAR = mesh
SRC = lib
BUILD = build
CC = g++
DBG = gdb
OBJ += $(shell ls $(SRC) | egrep *.c | sed 's/.c/.o/g' | sed 's/^/$(BUILD)\//g')

$(TAR): $(OBJ)
	$(CC) $^ -o $(TAR)

debug: $(OBJ)
	$(CC) -g $^ -o $(TAR)
	$(DBG) $(TAR)

# commands
.PHONY:
run: $(TAR)
	make clean
	./$(TAR)
.PHONY:
clean:
	rm -f $(BUILD)/* *.o
.PHONY:
clean_all:
	rm -f $(BUILD)/* *.o $(TAR)

# modular build
$(BUILD)/%.o: $(SRC)/%.c
	$(CC) -c $^ -o $@
