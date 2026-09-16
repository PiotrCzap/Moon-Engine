CXX = g++
CXXFLAGS = -Wall -Wextra
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC_DIR = src
OBJ_DIR = .obj
BUILD_DIR = build

# Szukamy plików .cpp w głównym folderze src ORAZ w podfolderze src/imgui
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/imgui/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
TARGET = $(BUILD_DIR)/Moon-Engine

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(OBJS) -o $@ $(LIBS)

# Reguła budowania dla plików .cpp (działa też z podfolderami)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	@clear
	@echo "--- Running on Linux ---"
	@./$(TARGET)

clean:
	@rm -rf $(OBJ_DIR) $(BUILD_DIR)

push:
	@git add .
	@git commit -m "$(m)"
	@git push -u origin main

.PHONY: all run clean push