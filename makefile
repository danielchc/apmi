SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

LEX_FILE := ./src/lex.yy.c
LEX_HEADER := ./include/lex.yy.h
TAB_FILE := ./src/y.tab.c
TAB_HEADER:= ./include/y.tab.h


EXE := $(BIN_DIR)/apmi
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude
CFLAGS   := -Wall
LDLIBS   := -lm -ldl

.PHONY: all clean lex



all: lex bison $(EXE) 

lex:
	flex -o $(LEX_FILE) --header-file=$(LEX_HEADER) ./src/lexsrc/grammar.l 
bison:
	bison -y -o $(TAB_FILE) --defines=$(TAB_HEADER) ./src/lexsrc/calc.y

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)