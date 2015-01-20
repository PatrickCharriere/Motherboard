
CC=g++
CFLAGS=-O3 -Wall
LDFLAGS=
TARGET=robot

SRC=$(shell find ./ -type f -name '*.cpp')
OBJ=$(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	@echo "Linking $(TARGET) ..."
	@$(CC) $(LDFLAGS) $(OBJ) -o $(TARGET)
	@chmod u+x $(TARGET)

.c.o:
	@echo "Building $< ..."
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(TARGET)