CC = gcc
OBJS = $(patsubst %.c,%.o,$(wildcard *.c))
CFLAGS = -Wall -Wextra `sdl2-config --cflags`
LDFLAGS =`sdl2-config --libs` -lSDL2_image -lSDL2_gfx  -lSDL2_mixer -lm 
EXEC = circles

$(EXEC): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $(EXEC)

%.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@

.PHONY: clean

clean:
	rm -f $(OBJS) $(EXEC)
