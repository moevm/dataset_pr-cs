CC=gcc
CFLAGS=-std=c99

.PHONY: clean

menu: obj/menu.o obj/index_first_negative.o obj/index_last_negative.o obj/sum_between_negative.o obj/sum_before_and_after_negative.o obj/range_abs_sum.o
	$(CC) $(CFLAGS) obj/menu.o obj/index_first_negative.o obj/index_last_negative.o obj/sum_between_negative.o obj/sum_before_and_after_negative.o obj/range_abs_sum.o -o menu

obj/index_first_negative.o: obj index_first_negative.c index_first_negative.h
	$(CC) $(CFLAGS) -c index_first_negative.c -o obj/index_first_negative.o

obj/index_last_negative.o: obj index_last_negative.c index_last_negative.h
	$(CC) $(CFLAGS) -c index_last_negative.c -o obj/index_last_negative.o

obj/sum_between_negative.o: obj sum_between_negative.c sum_between_negative.h index_first_negative.h index_last_negative.h
	$(CC) $(CFLAGS) -c sum_between_negative.c -o obj/sum_between_negative.o

obj/sum_before_and_after_negative.o: obj sum_before_and_after_negative.c sum_before_and_after_negative.h index_first_negative.h index_last_negative.h
	$(CC) $(CFLAGS) -c sum_before_and_after_negative.c -o obj/sum_before_and_after_negative.o

obj/range_abs_sum.o: obj range_abs_sum.c range_abs_sum.h
	$(CC) $(CFLAGS) -c range_abs_sum.c -o obj/range_abs_sum.o

obj/menu.o: obj menu.c index_first_negative.h index_last_negative.h sum_between_negative.h sum_before_and_after_negative.h range_abs_sum.h
	$(CC) $(CFLAGS) -c menu.c -o obj/menu.o

obj:
	mkdir obj

clean:
	rm -rf obj menu