TARGET = cw
COMPILED_DIR = compiled/
CC = gcc
CFLAGS = -Wall -Wextra
.PHONY = all clean

SRC_DIR		:= $(COMPILED_DIR) .
SRC_FILES	:= $(addsuffix /*.c,$(SRC_DIR)) # search files

$(TARGET) : $(notdir $(patsubst %.c,%.o, $(wildcard $(SRC_FILES) ) ) ) # linking
	# linking files
	gcc $^ -o $@
	# moving compiled files to $(COMPILED_DIR)
	mkdir -p $(COMPILED_DIR)
	mv *.o *.d $(COMPILED_DIR)

VPATH := $(SRC_DIR) 

%.o : %.c
	@# compiling files and creating dependencies
	$(CC) -c -MD $(CFLAGS) $(addprefix -I ,$(SRC_DIR)) $<

clean_all : clean
	rm -f cw

clean :
	# Deleting compiled files
	rm -rf $(COMPILED_DIR)

include $(wildcard *.d) 
