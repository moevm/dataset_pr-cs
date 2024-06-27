CC = g++
CFLAGS = -std=c++14 -g -Wall -Werror -Wextra

SRCDIR = source
INCDIR = include

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=%.o)
TARGET = cw



all: $(TARGET)
	rm -f $(OBJS)


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

run1: $(TARGET)
	rm -f $(OBJS)
	./$(TARGET) --inverse --input ./channel.bmp --output ./OUTPUT.bmp


run2: $(TARGET)
	rm -f $(OBJS)
	./$(TARGET) --component_sum --component_name blue --input ./channel.bmp --output ./OUTPUT.bmp

