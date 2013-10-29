PROGNAME = derping_with

CC = gcc
CFLAGS = -Wall -std=c99 -pedantic
COMPILE = $(CC) $(CFLAGS) -c
OUTPUT = -o $@

%.o: %.c
	$(COMPILE) $< $(OUTPUT) -lm

$(PROGNAME): $(PROGNAME).c
	$(CC) $(CFLAGS) $(OUTPUT) $^ -lm

run: $(PROGNAME)
	./$(PROGNAME)
