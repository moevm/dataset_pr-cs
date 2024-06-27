all : libimageBMP.so cw

cw : main.o parser.o handler.o
	g++ main.o parser.o handler.o -fPIC -Wl,-rpath=. -L. -limageBMP -o cw

main.o : main.cpp handler.h
	g++ main.cpp -c -Wall

parser.o : parser.cpp parser.h imageBMP.h
	g++ parser.cpp -c -Wall

handler.o : handler.cpp handler.h parser.h
	g++ handler.cpp -c -Wall

libimageBMP.so : imageBMP.cpp imageBMP.h
	g++ imageBMP.cpp -fPIC -shared -o libimageBMP.so

clean :
	-rm cw libimageBMP.so *.o