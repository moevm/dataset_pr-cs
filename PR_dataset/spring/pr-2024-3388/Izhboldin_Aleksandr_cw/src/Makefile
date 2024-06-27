TARGET = cw
COMPILED_DIR = compiled/
CC = g++
EXT = cc
CFLAGS = -std=c++14
.PHONY = all clean

MAKEFLAGS := -j4
SRC_DIR		:= $(COMPILED_DIR) . libs/args_parsing_lib/ libs/bmp_image_lib/ libs/data_processing_lib/ libs/image_editor_lib/
SRC_FILES	:= $(addsuffix /*.$(EXT),$(SRC_DIR)) # search files

$(TARGET) : $(notdir $(patsubst %.$(EXT),%.o, $(wildcard $(SRC_FILES) ) ) ) # linking
	# linking files
	$(CC) $^ -o $@
	# moving compiled files to $(COMPILED_DIR)
	mkdir -p $(COMPILED_DIR)
	mv *.o *.d $(COMPILED_DIR)

VPATH := $(SRC_DIR)

%.o : %.$(EXT)
	@# compiling files and creating dependencies
	$(CC) -c -MD $(CFLAGS) $(addprefix -I ,$(SRC_DIR)) $<

clean_all : clean
	rm -f cw

clean :
	# Deleting compiled files
	rm -rf $(COMPILED_DIR)

include $(wildcard $(COMPILED_DIR)*.d)