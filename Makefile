CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt \
          -lX11 -lXi -lXrandr -lXinerama -lXcursor

SRC = src/main.c \
      src/simulador.c \
      src/componentes.c \
      src/botones.c

TARGET = simulador

all:
	@echo "Compilando proyecto..."
	@$(CC) $(SRC) $(CFLAGS) -o $(TARGET) $(LDFLAGS)
	@echo "Compilación exitosa."

run: all
	@echo "Ejecutando..."
	@./$(TARGET)

clean:
	@rm -f $(TARGET)