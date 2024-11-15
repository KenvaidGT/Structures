CC = gcc

CFLAGS = -Iinclude -Wall -Wextra -pedantic

# Папки
SRCDIR = src
INCDIR = include
BUILDDIR = build
DATADIR = data

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))

TARGET = $(BUILDDIR)/students_app

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILDDIR)
	$(CC) $(OBJECTS) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)

run: $(TARGET)
	$(TARGET)
