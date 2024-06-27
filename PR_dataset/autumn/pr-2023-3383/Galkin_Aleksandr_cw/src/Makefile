all: cw
cw: main.o get_text.o text_treatment.o time_funcs.o funcs_explanation.o
	gcc main.o get_text.o text_treatment.o time_funcs.o funcs_explanation.o -o cw
main.o: main.c get_text.h structures_define.h text_treatment.h time_funcs.h funcs_explanation.h
	gcc -c -g main.c
get_text.o: get_text.c get_text.h structures_define.h
	gcc -c -g get_text.c
text_treatment.o: text_treatment.c structures_define.h text_treatment.h
	gcc -c -g text_treatment.c
time_funcs.o: time_funcs.c time_funcs.h structures_define.h
	gcc -c -g time_funcs.c
funcs_explanation.o: funcs_explanation.c funcs_explanation.h structures_define.h
	gcc -c -g funcs_explanation.c
clean:
	rm -rf *.o *.h.gch
delete:
	rm -rf cw