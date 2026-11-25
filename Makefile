CC      = gcc
CFLAGS  = -Wall -Wextra -g
LIBS    = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC_DIR   = src
OBJ_DIR   = .obj
BUILD_DIR = build

SRCS   = $(wildcard $(SRC_DIR)/*.c)
OBJS   = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
TARGET = $(BUILD_DIR)/engine

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	@echo "--- Running on Linux ---"
	./$(TARGET)

clean:
	@rm -rf $(OBJ_DIR) $(BUILD_DIR)

.PHONY: all run clean