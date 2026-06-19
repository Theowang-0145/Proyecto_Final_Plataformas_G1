CC = gcc

CFLAGS = -Wall 

LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt \
          -lX11 -lXi -lXrandr -lXinerama -lXcursor

SRC = prueba_completa.c\


TARGET = ejecutable_pruebas

all:
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET) $(LDFLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)