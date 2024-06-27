CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

EXEC = cw
LIB_NAME = libbmp.so

SRC_DIR = src
BUILD_DIR = build

LIB_SRC_DIR = $(SRC_DIR)/bmp
LIB_BUILD_DIR = $(BUILD_DIR)/bmp
LIB_SRC_FILES = $(wildcard $(LIB_SRC_DIR)/*.cpp)
LIB_OBJ_FILES = $(patsubst $(LIB_SRC_DIR)/%.cpp, $(LIB_BUILD_DIR)/%.o, $(LIB_SRC_FILES))

CLI_SRC_DIR = cli
CLI_BUILD_DIR = $(BUILD_DIR)/cli
CLI_SRC_FILES = $(wildcard $(CLI_SRC_DIR)/*.cpp)
CLI_OBJ_FILES = $(patsubst $(CLI_SRC_DIR)/%.cpp, $(CLI_BUILD_DIR)/%.o, $(CLI_SRC_FILES))

$(shell mkdir -p $(BUILD_DIR))
$(shell mkdir -p $(LIB_BUILD_DIR))
$(shell mkdir -p $(CLI_BUILD_DIR))

all: $(EXEC) clean

$(EXEC): $(CLI_OBJ_FILES) $(LIB_NAME)
	$(CXX) $(CXXFLAGS) -o $@ $(CLI_OBJ_FILES) -L. -Wl,-rpath=. -lbmp

$(CLI_BUILD_DIR)/%.o: $(CLI_SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC_FLAGS) -c -o $@ $<

$(LIB_NAME): $(LIB_OBJ_FILES)
	$(CXX) $(CXXFLAGS) -shared -o $(LIB_NAME) $^

$(LIB_BUILD_DIR)/%.o: $(LIB_SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC_FLAGS) -fPIC -c -o $@ $<

.PHONY clean:
	rm -rf $(BUILD_DIR)
