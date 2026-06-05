CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -march=native -std=c++17 -I src

SRC_DIR = src
BUILD_DIR = build
TARGET = knapsack

CPP_FILES = $(shell find $(SRC_DIR) -name "*.cpp" ! -path "*/containers/*")
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CPP_FILES))

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -rf $(BUILD_DIR)/*

run: $(TARGET)
	./$(TARGET) data/test1.txt

run-test2: $(TARGET)
	./$(TARGET) data/test2.txt

run-test3: $(TARGET)
	./$(TARGET) data/test3.txt

run-invalid: $(TARGET)
	./$(TARGET) data/invalid.txt

.PHONY: all clean run run-test2 run-test3 run-invalid