PROJNAME = rohanasan_website

CC = gcc

CDEBUGFLAGS = -Wall -I./include

CRELEASEFLAGS = -O3 -I./include

INCDIR = ./include

SRC = ./server.c

TARGET = $(PROJNAME).out

.PHONY: debug
debug:
	@echo "\033[0;32mBuilding $(PROJNAME).out for debugging!!!\033[0m"
	$(CC) $(CDEBUGFLAGS) $(SRC) -o $(TARGET)
	@echo "\033[0;32mBuilt $(PROJNAME).out for debugging!!!\033[0m"

.PHONY: release
release:
	@echo "\033[0;32mBuilding $(PROJNAME).out for release!!!\033[0m"
	$(CC) $(CRELEASEFLAGS) $(SRC) -o $(TARGET)
	@echo "\033[0;32mBuilt $(PROJNAME).out for release!!!\033[0m"

.PHONY: run
run: $(TARGET)
	./$(TARGET)


.PHONY: clean
clean:
	rm -rf $(TARGET)

    