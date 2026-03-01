CC = gcc
CFLAGS = -Wall -Wextra -ansi -pedantic -g
CPPFLAGS = -Iinclude -I./ressources/MODULE\ IMAGE/MODULE_IMAGE/include/
LDFLAGS = -L./ressources/MODULE\ IMAGE/MODULE_IMAGE -limage -lm
SRC = ./src/
SRC_IMG = ./ressources/MODULE\ IMAGE/MODULE_IMAGE/src/
INCLUDE = ./include/
INCLUDE_IMG = ./ressources/MODULE\ IMAGE/MODULE_IMAGE/include/
BIN = ./bin/

# Définir les fichiers objets
OBJ = $(SRC)main.o $(SRC)histogramme.o $(SRC)quantification.o

# Définir l'executable 
TARGET = $(BIN)histogramme.bin

.PHONY: all clean test

# Règles de production de l'executable
all: $(TARGET)

# Règles d'édition des liens
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Règles de production des fichiers objets avant édition des liens 
$(SRC)main.o: $(SRC)main.c $(INCLUDE)histogramme.h $(INCLUDE_IMG)image.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(SRC)histogramme.o: $(SRC)histogramme.c $(INCLUDE)histogramme.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(SRC)quantification.o: $(SRC)quantification.c $(INCLUDE)quantification.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

test:
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(BIN)test.bin $(SRC)TEST/test.c $(SRC)histogramme.c $(SRC)quantification.c $(LDFLAGS)

clean :
	rm -f $(OBJ) $(TARGET) 