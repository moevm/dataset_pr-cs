TARGET_EXEC := cw
BUILD_DIR := build
CC := gcc
CCFLAGS := -Wall -std=c11

INCLUDE := -Im -Ipng
LINK := -lm -lpng
LIBSRC := $(wildcard lib/*.c)
LIBOBJ := $(patsubst lib/%.c,$(BUILD_DIR)/%.o,$(LIBSRC))

all: $(TARGET_EXEC)

$(TARGET_EXEC): $(LIBOBJ) $(BUILD_DIR)/main.o
	echo Linking...
	$(CC) $(CCFLAGS) -o $(TARGET_EXEC) $(BUILD_DIR)/*.o $(LINK)

$(BUILD_DIR)/%.o: %.c
	echo Compiling $*.o...
	mkdir -p $(BUILD_DIR)
	$(CC) $(CCFLAGS) $(INCLUDE) -o $(BUILD_DIR)/$*.o -c $<

$(BUILD_DIR)/%.o: lib/%.c
	echo Compiling $*.o...
	mkdir -p $(BUILD_DIR)
	$(CC) $(CCFLAGS) $(INCLUDE) -o $(BUILD_DIR)/$*.o -c $<

clean:
	rm -rf build/
	rm -f cw

rebuild: clean all

.SILENT:
.PHONY: all clean rebuild
