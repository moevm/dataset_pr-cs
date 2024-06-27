CC =g++
CFLAGS = -std=c++11 -Wno-deprecated

all: cw

cw: main.o rgb.o throw_exception.o utils.o input.o draw_line.o biggest_rect.o make_collage.o draw_triangle.o
	${CC} $^ -o $@ ${CFLAGS}

rgb.o: src/rgb.cpp include/rgb.h
	${CC} -c $< ${CFLAGS}

throw_exception.o: src/throw_exception.cpp include/throw_exception.h
	${CC} -c $< ${CFLAGS}

utils.o: src/utils.cpp include/utils.h include/throw_exception.h
	${CC} -c $< ${CFLAGS}

input.o: src/input.cpp include/input.h include/rgb.h include/utils.h include/throw_exception.h
	${CC} -c $< ${CFLAGS}

draw_line.o: src/draw_line.cpp include/draw_line.h include/rgb.h
	${CC} -c $< ${CFLAGS}

biggest_rect.o: src/biggest_rect.cpp include/biggest_rect.h include/rgb.h include/draw_line.h
	${CC} -c $< ${CFLAGS}

make_collage.o: src/make_collage.cpp include/make_collage.h include/rgb.h
	${CC} -c $< ${CFLAGS}

draw_triangle.o: src/draw_triangle.cpp include/draw_triangle.h include/draw_line.h
	${CC} -c $< ${CFLAGS}

main.o: main.cpp include/rgb.h include/throw_exception.h include/utils.h include/input.h include/draw_line.h include/biggest_rect.h include/make_collage.h include/draw_triangle.h
	${CC} -c $< ${CFLAGS}

clean:
	rm *.o cw
