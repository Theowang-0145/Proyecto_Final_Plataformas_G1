CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt \
          -lX11 -lXi -lXrandr -lXinerama -lXcursor

SRC = src/main.c \
      src/simulator.c \
      src/components.c \
      src/buttons.c

TARGET = simulator

all:
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET) $(LDFLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)