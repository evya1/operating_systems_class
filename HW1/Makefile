SRCS = myshell.c
OBJS = $(patsubst %.c,build/%.o,$(SRCS))
CFLAGS = -Werror -std=c99
TARGET = build/myshell
OUTPUT_DIR = build/output

all: $(TARGET)

$(TARGET): $(OBJS) | build
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)
	@chmod +x $(TARGET) # Set execute permissions for the target binary

build/%.o: %.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

run: $(TARGET)
	./$(TARGET)

test: $(TARGET) | $(OUTPUT_DIR)
	@echo "Running tests..."
	@./$(TARGET) < tests/test.in > $(OUTPUT_DIR)/output.out
	@diff $(OUTPUT_DIR)/output.out tests/test.out && echo "Test passed!" || echo "Test failed!"

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

.PHONY: clean
clean:
	rm -rf build $(OBJS) $(TARGET)
