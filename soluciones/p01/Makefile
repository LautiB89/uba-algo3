CC = g++
CPPFLAGS = -g -std=c++11 -Wall -pedantic
OUTPUT_PATH := bin
OUTPUT_FILENAME := app

SRC=$(wildcard ej*.cpp)

.PHONY: all clean

all: $(SRC)
	$(CC) $(CPPFLAGS) $< -o $(OUTPUT_PATH)/ej$*_$(OUTPUT_FILENAME)

ej%: ej%.cpp
	@mkdir -p $(OUTPUT_PATH)
	$(CC) $(CPPFLAGS) $< -o $(OUTPUT_PATH)/ej$*_$(OUTPUT_FILENAME)

run%: ej%
	./$(OUTPUT_PATH)/ej$*_$(OUTPUT_FILENAME)

clean:
	rm -f *.o
	rm -rf $(OUTPUT_PATH)