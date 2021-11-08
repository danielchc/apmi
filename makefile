SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

LEX_FILE := ./src/lex.yy.c
TAB_FILE := ./src/y.tab.c
TAB_HEADER:= ./src/y.tab.h


EXE := $(BIN_DIR)/apmi
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude
CFLAGS   := -Wall
LDLIBS   := -lm -ldl

.PHONY: all clean lex



all: lex bison $(EXE) 

lex:
	flex -o $(LEX_FILE) ./src/grammar.l
bison:
	bison -dy -o $(TAB_FILE) ./src/calc.y && mv $(TAB_HEADER) include

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)