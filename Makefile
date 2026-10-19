CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC_DIR = src
OBJ_DIR = .obj
BUILD_DIR = build

# wszystkie .c oprócz Settings.c
SRC_FILES = $(filter-out $(SRC_DIR)/Settings.c, $(wildcard $(SRC_DIR)/*.c))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
TARGET = $(BUILD_DIR)/engine
SETTINGS = $(BUILD_DIR)/settings

all: $(TARGET) $(SETTINGS)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(OBJS) -o $@ $(LIBS)

$(SETTINGS): $(SRC_DIR)/Settings.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	@clear
	@echo "--- Running on Linux ---"
	@cd $(BUILD_DIR) && ./engine

clean:
	@rm -rf $(OBJ_DIR) $(BUILD_DIR)

.PHONY: all run clean