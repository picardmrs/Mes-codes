# Définit le compilateur utilisé
CC = gcc
CFLAGS = -Wall -pedantic -ansi -Wextra -g
INCLUDE = ./include/
CPPFLAGS = -Iinclude
SRC = ./src/

# Définit la liste des fichiers "objets" communs
OBJS_COMMON = image.o convert.o

# Définit les exécutables à produire
TARGET1 = prog.bin
TARGET2 = prog2.bin

.PHONY: all clean

# Règle de production des deux exécutables
all: $(TARGET1) $(TARGET2)

# Règle d'édition des liens pour le premier exécutable
$(TARGET1): $(OBJS_COMMON) main.o
	$(CC) $(CFLAGS) -o $@ $^

# Règle d'édition des liens pour le deuxième exécutable
$(TARGET2): $(OBJS_COMMON) main2.o transformations.o
	$(CC) $(CFLAGS) -o $@ $^ -lm


# Règles de production des fichiers "objets" avant édition des liens
main.o: $(SRC)main.c $(INCLUDE)image.h $(INCLUDE)convert.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

main2.o: $(SRC)main2.c $(INCLUDE)transformations.h 
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

image.o: $(SRC)image.c $(INCLUDE)image.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

convert.o: $(SRC)convert.c $(INCLUDE)convert.h $(INCLUDE)image.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

transformations.o: $(SRC)transformations.c $(INCLUDE)transformations.h $(INCLUDE)image.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Nettoyage des fichiers "objets" et des exécutables
clean:
	rm -f $(OBJS_COMMON) main.o main2.o transformations.o $(TARGET1) $(TARGET2)
