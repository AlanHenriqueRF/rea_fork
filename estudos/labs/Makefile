# Compila cada lab em quatro variantes para comparar no REA/Ghidra:
#   <nome>-O0          sem otimização, com símbolos (mais fácil de ler)
#   <nome>-O2          otimizado, com símbolos (veja o compilador reescrever seu código)
#   <nome>-O0-stripped sem símbolos (como um binário "de verdade")
#   <nome>-O2-stripped otimizado e sem símbolos (o desafio final)
CC ?= cc
CFLAGS ?= -Wall -Wextra -fno-stack-protector
SRC := $(wildcard src/*.c)
NOMES := $(basename $(notdir $(SRC)))
ALVOS := $(foreach n,$(NOMES),bin/$(n)-O0 bin/$(n)-O2 bin/$(n)-O0-stripped bin/$(n)-O2-stripped)

all: $(ALVOS)

bin/%-O0: src/%.c | bin
	$(CC) $(CFLAGS) -O0 -g -o $@ $<

bin/%-O2: src/%.c | bin
	$(CC) $(CFLAGS) -O2 -g -o $@ $<

bin/%-stripped: bin/%
	strip -o $@ $<

bin:
	mkdir -p bin

clean:
	rm -rf bin

.PHONY: all clean
