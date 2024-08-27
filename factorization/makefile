CC = gcc
CFLAGS = -fPIC -Wall -Wextra

LDFLAGS = -shared

SRC_DIR = src
BUILD_DIR = build

SOURCES = $(shell find $(SRC_DIR) -name '*.c')
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

LIBRARY = $(BUILD_DIR)/libfactorization.so

all: $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) -lm

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) $(SHARED_FLAGS) -I$(SRC_DIR) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(LIBRARY)

.PHONY: all clean
