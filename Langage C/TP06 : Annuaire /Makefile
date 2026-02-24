# Définit compilateur utilisé
CC = gcc
CFLAGS = -Wall -pedantic -ansi -Wextra -g
CPPFLAGS = -Iinclude

# Définit des raccourcis dechemins
SRC = ./src/
INCLUDE = ./include/

# Définit l'executable
TARGET = annuaire.bin

# Définit la liste des fichiers objets
OBJS = main.o annuaire.o personne.o

.PHONY: all clean

#Règles de production d'éxecutable et d'édition des liens
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

#Production fichiers objets

main.o : $(SRC)main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

annuaire.o : $(SRC)annuaire.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

personne.o : $(SRC)personne.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean : 
	rm -f $(TARGET) *.o 
