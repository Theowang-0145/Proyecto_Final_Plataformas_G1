CC = gcc

CFLAGS = -Wall -Wextra -g -Iinclude

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

TEST_MEM = test_memoria

test_memoria:
	@$(CC) src/test_memoria.c src/componentes.c $(CFLAGS) -o $(TEST_MEM) $(LDFLAGS)

memcheck-test: test_memoria
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_MEM)