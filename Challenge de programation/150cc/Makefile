TARGET = gdc/drivers/150cc

CC = gcc
CFLAGS = -ansi -pedantic -Wall -Wextra -Iinclude -Igdc/follow_line -O3 -g 

LDFLAGS = -lm

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRCS = $(wildcard $(SRC_DIR)/*.c) gdc/follow_line/follow_line.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p gdc/drivers
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)
	@mkdir -p driver
	@cp $(TARGET) driver/150cc
	@echo "Compilation réussie : $(TARGET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "Dossiers nettoyés."

.PHONY: all clean
