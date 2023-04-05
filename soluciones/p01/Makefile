CC = g++
CPPFLAGS = -g -std=c++11 -Wall -pedantic
OUTPUT_PATH := bin
OUTPUT_FILENAME := app

.PHONY: all clean

$(OUTPUT_PATH)/%: %.cpp
	@mkdir -p $(OUTPUT_PATH)
	$(CC) $(CPPFLAGS) $< -o $(OUTPUT_PATH)/$*_app

clean:
	rm -f *.o
	rm -rf $(OUTPUT_PATH)