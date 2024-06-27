.PHONY: clean
FLAG=-std=c99
menu: menu.o input.o abs_max.o abs_min.o diff.o sum.o oper.o
	gcc $(FLAG) temp/menu.o temp/input.o temp/abs_max.o temp/abs_min.o temp/sum.o temp/oper.o -o menu
menu.o: temp menu.c
	gcc $(FLAG) -c menu.c -o temp/menu.o
input.o: input.c
	gcc $(FLAG) -c input.c -o temp/input.o
abs_max.o: abs_max.c
	gcc $(FLAG) -c abs_max.c -o temp/abs_max.o
abs_min.o: abs_min.c
	gcc $(FLAG) -c abs_min.c -o temp/abs_min.o
diff.o: diff.c
	gcc $(FLAG) -c diff.c -o temp/diff.o
sum.o: sum.c
	gcc $(FLAG) -c sum.c -o temp/sum.o
oper.o: oper.c
	gcc $(FLAG) -c oper.c -o temp/oper.o
temp:
	mkdir temp
clean:
	rm -rf temp temp/*
