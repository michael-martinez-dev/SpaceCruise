APP_NAME = SpaceCruiser
VERSION = v0.1
CC = g++
DBR = gdb
BINARY_PATH = ./bin/$(VERSION)
OUTPUT = -o $(BINARY_PATH)/$(APP_NAME)
DEBUG_BINARY_PATH = ./bin/debug
DEBUG_OUTPUT = -o $(DEBUG_BINARY_PATH)/$(APP_NAME)-$(VERSION)
SRC_PATH = src/*
DEPS_SFML = -lsfml-graphics -lsfml-window -lsfml-system
DEPS_LOCAL = -Iinclude
ALL_DEPS = $(DEPS_SFML) $(DEPS_LOCAL)

build:
	@mkdir -p $(BINARY_PATH)
	$(CC) $(OUTPUT) $(SRC_PATH) $(ALL_DEPS)
	
run: build
	./$(BINARY_PATH)/$(APP_NAME)
	
debug:
	@mkdir -p $(DEBUG_BINARY_PATH)
	$(CC) -g $(DEBUG_OUTPUT) $(SRC_PATH) $(ALL_DEPS)
	$(DBR) $(DEBUG_BINARY_PATH)/$(APP_NAME)-$(VERSION)

clean.debug:
	rm -rf $(DEBUG_BINARY_PATH)/

clean.app:
	rm -f $(BINARY_PATH)/$(APP_NAME)

clean: clean.debug clean.app
