executable_name=cw
source_files=main.c ./*/*.c

all:
	gcc -g -o $(executable_name) $(source_files)

run: build
	./$(executable_name)
	@echo
	@make -s clean

build: 
	gcc -g -o $(executable_name) $(source_files)

clean: 
	@rm -rf ./$(executable_name)

debug: build
	gdb ./cw 