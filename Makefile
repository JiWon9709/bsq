CC = gcc
CLAGS = -Wall -Werror -Wextra
TARGET = bsq
OBJECTS = main.c scan.c valid.c find.c error.c

$(TARGET) : $(OBJECTS)
	$(CC) $(CLFLAGS) -o $@ $^

fclean:
	rm -rf *.o $(TARGET)
