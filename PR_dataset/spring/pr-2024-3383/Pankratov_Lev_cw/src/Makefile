all: cw clean

cw: main.o command_line_options.o core.o inverse.o gray_picture.o change_size.o draw_romb.o
	g++ main.o command_line_options.o core.o inverse.o gray_picture.o change_size.o draw_romb.o -o cw

main.o: main.cpp command_line_options.hpp
	g++ -c main.cpp

command_line_options.o: command_line_options.cpp command_line_options.hpp modules/core.hpp modules/inverse.hpp modules/gray_picture.hpp modules/core.hpp modules/draw_romb.hpp
	g++ -c command_line_options.cpp

core.o: modules/core.cpp modules/core.hpp
	g++ -c modules/core.cpp

inverse.o: modules/inverse.cpp modules/inverse.hpp modules/core.hpp
	g++ -c modules/inverse.cpp

gray_picture.o: modules/gray_picture.cpp modules/gray_picture.hpp modules/core.hpp
	g++ -c modules/gray_picture.cpp

change_size.o: modules/change_size.cpp modules/change_size.hpp modules/core.hpp
	g++ -c modules/change_size.cpp

draw_romb.o: modules/draw_romb.cpp modules/draw_romb.hpp modules/core.hpp
	g++ -c modules/draw_romb.cpp

clean:
	# find . -name "*.o" ! -name "cw.o" -type f -exec rm -f {} +