CC = gcc

CFLAGS = -Iinclude -Wall -Wextra -pedantic

SRCDIR = src
INCDIR = include
BUILDDIR = build
DATADIR = data

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))

TARGET = $(BUILDDIR)/px

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILDDIR)
	$(CC) $(OBJECTS) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	@./$(TARGET) $(filter-out $@,$(MAKECMDGOALS))

clean:
	rm -rf $(BUILDDIR)

%:
	@:
