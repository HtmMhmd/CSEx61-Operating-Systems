CC = gcc
CFLAGS = -Wall -Wextra -pthread
SRCDIR = readtxtfiles writetxtfiles
SRCS = application.c $(wildcard readtxtfiles/*.c) $(wildcard writetxtfiles/*.c)
OBJS = $(SRCS:.c=.o)
OUT = myprogram

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) myprogram
