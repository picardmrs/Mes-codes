# Définit le compilateur utilisé
CC = gcc
CFLAGS = -Wall -pedantic -ansi -Wextra -g
INCLUDE = ./include/
CPPFLAGS = -Iinclude
SRC = ./src/

# Définit la liste des fichiers "objets"
OBJS = file.o main.o

# Définit l'exécutable à produire
TARGET = prog.bin

.PHONY: all clean

# Règle de production de l'exécutable
all: $(TARGET)

# Règle d'édition des liens
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^


# Règles de production des fichiers "objets" avant édition des liens
main.o: $(SRC)main.c $(INCLUDE)bool.h $(INCLUDE)file.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

file.o: $(SRC)file.c $(INCLUDE)bool.h $(INCLUDE)file.h 
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Nettoyage des fichiers "objets" et de l'exécutable
clean:
	rm -f $(OBJS) $(TARGET)
