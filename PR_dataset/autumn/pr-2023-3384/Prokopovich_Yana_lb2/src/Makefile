menu: menu.o index_first_negative.o index_last_negative.o multi_between_negative.o multi_before_and_after_negative.o
        gcc menu.o index_first_negative.o index_last_negative.o multi_between_negative.o multi_before_and_after_negative.o -o menu
index_first_negative.o: index_first_negative.c index_first_negative.h
        gcc  -c index_first_negative.c -std=c99
index_last_negative.o:index_last_negative.c index_last_negative.h
        gcc -c index_last_negative.c -std=c99
multi_between_negative.o: multi_between_negative.c multi_between_negative.h index_first_negative.h index_last_negative.h
        gcc -c multi_between_negative.c -std=c99
multi_before_and_after_negative.o: multi_before_and_after_negative.c multi_before_and_after_negative.h index_first_negative.h index_last_negative.h
        gcc -c multi_before_and_after_negative.c -std=c99
menu.o: menu.c index_first_negative.h index_last_negative.h multi_between_negative.h multi_before_and_after_negative.h
        gcc -c menu.c -std=c99
clean:
        rm -rf *.o