all: cw
cw: main.o DELL.o ERROR.o find.o Input_Sentence.o Input_Text.o Memory_Cleaning.o Replace.o Sort_low_cnt_wrd.o find_no_reg.o
	gcc main.o DELL.o ERROR.o find.o Input_Sentence.o Input_Text.o Memory_Cleaning.o Replace.o Sort_low_cnt_wrd.o find_no_reg.o -o cw
main.o: main.c DELL.h ERROR.h find.h Input_Sentence.h Input_Text.h Memory_Cleaning.h my_lib.h Replace.h Sort_low_cnt_wrd.h find_no_reg.h
	gcc -c -g main.c
DELL.o: DELL.c DELL.h my_lib.h
	gcc -c -g DELL.c
ERROR.o: ERROR.c ERROR.h my_lib.h
	gcc -c -g ERROR.c
find.o: find.c find.h my_lib.h
	gcc -c -g find.c
Input_Sentence.o: Input_Sentence.c Input_Sentence.h my_lib.h
	gcc -c -g Input_Sentence.c
Input_Text.o: Input_Text.c Input_Text.h my_lib.h
	gcc -c -g Input_Text.c
Memory_Cleaning.o: Memory_Cleaning.c Memory_Cleaning.h my_lib.h
	gcc -c -g Memory_Cleaning.c
Replace.o: Replace.c Replace.h
	gcc -c -g Replace.c
Sort_low_cnt_wrd.o: Sort_low_cnt_wrd.c Sort_low_cnt_wrd.h my_lib.h
	gcc -c -g Sort_low_cnt_wrd.c
find_no_reg.o: find_no_reg.c find_no_reg.h my_lib.h
	gcc -c -g find_no_reg.c
clean:
	rm -rf *.o
delete:
	rm -rf cw