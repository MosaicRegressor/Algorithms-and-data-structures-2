
# -Iinclude dice al compilatore di cercare gli header in include/.
# Gli oggetti compilati finiscono nella cartella obj/.
# Gli eseguibili finiscono nella cartella bin/.
# Le cartelle obj e bin vengono create automaticamente se non esistono (grazie alle regole con | $(OBJ_DIR) e | $(BIN_DIR)).
# Usa i percorsi completi per ogni file .c, .o ed eseguibile.
# per compilare make
# per pulire make clean

CC = gcc
CFLAGS = -Werror -Wall -Wextra -pedantic -std=c11 -g -Iinclude    # -Iinclude per cercare gli header nella cartella include

# Cartelle sorgente
LCS_DIR = ./LCS
FIB_DIR = ./Fibonacci
LIS_DIR = ./LIS
LICS_DIR = ./LICS
HELPER_DIR = ./custom_helper_libs
INCLUDE_DIR = ./include

# Object files e file eseguibili
OBJ_DIR = obj
BIN_DIR = bin

# File .o (con percorso completo)
HELPER_OBJ = $(OBJ_DIR)/helper_lib.o
LCS_OBJ = $(OBJ_DIR)/lcs.o
FIB_OBJ = $(OBJ_DIR)/fibonacci.o
LIS_OBJ = $(OBJ_DIR)/lis.o
LICS_OBJ = $(OBJ_DIR)/lics.o

# Eseguibili
LCS_BIN = $(BIN_DIR)/lcs.out
FIB_BIN = $(BIN_DIR)/fibonacci.out
LIS_BIN = $(BIN_DIR)/lis.out
LICS_BIN = $(BIN_DIR)/lics.out

# Target principale
all: $(LCS_BIN) $(FIB_BIN) $(LIS_BIN) $(LICS_BIN)

# ----------------------------------------------------------------------------------

# Regola per creare la cartella obj se non esiste
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Regola per creare la cartella bin se non esiste
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# ---------------------------------------------------------------------------------
# Compila gli eseguibili

$(LCS_BIN): $(LCS_OBJ) $(HELPER_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(FIB_BIN): $(FIB_OBJ) $(HELPER_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(LIS_BIN): $(LIS_OBJ) $(HELPER_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(LICS_BIN): $(LICS_OBJ) $(HELPER_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# ---------------------------------------------------------------------------------
# Compila gli object files

$(HELPER_OBJ): $(HELPER_DIR)/helper_lib.c $(INCLUDE_DIR)/helper_lib.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LCS_OBJ): $(LCS_DIR)/lcs.c $(INCLUDE_DIR)/helper_lib.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(FIB_OBJ): $(FIB_DIR)/fibonacci.c $(INCLUDE_DIR)/helper_lib.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIS_OBJ): $(LIS_DIR)/lis.c $(INCLUDE_DIR)/helper_lib.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LICS_OBJ): $(LICS_DIR)/lics.c $(INCLUDE_DIR)/helper_lib.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ---------------------------------------------------------------------------------
# Pulizia
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
