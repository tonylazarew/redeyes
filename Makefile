CC=clang
LDFLAGS=-framework Foundation -framework IOKit

redeyes: redeyes.c
	$(CC) $< -o $@ $(LDFLAGS)

clean: redeyes
	rm $<

all: redeyes
