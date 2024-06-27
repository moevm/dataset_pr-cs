IFN = index_first_negative
ILN = index_last_negative
MBN = multi_between_negative
MBAAN = multi_before_and_after_negative


all: menu.o $(IFN).o $(ILN).o $(MBN).o $(MBAAN).o
	gcc menu.o $(IFN).o $(ILN).o $(MBN).o $(MBAAN).o -o menu

menu.o: menu.c $(IFN).h $(ILN).h $(MBN).h $(MBAAN).h
	gcc -c menu.c -std=c99

$(IFN).o: $(IFN).c $(IFN).h
	gcc -c $(IFN).c -std=c99

$(ILN).o: $(ILN).c $(ILN).h
	gcc -c $(ILN).c -std=c99

$(MBN).o: $(MBN).c $(MBN).h $(IFN).h $(ILN).h
	gcc -c $(MBN).c -std=c99

$(MBAAN).o: $(MBAAN).c $(MBAAN).h $(IFN).h $(ILN).h
	gcc -c $(MBAAN).c -std=c99

clean: 
	rm *.o