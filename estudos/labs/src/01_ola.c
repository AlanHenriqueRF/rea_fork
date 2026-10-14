/* Lab 01 — Primeiro contato.
 * Objetivo: localizar main, a string de saudação e a chamada a printf.
 * Perguntas: onde a string fica guardada (qual seção)? Como o argumento chega ao printf?
 */
#include <stdio.h>

static int soma(int a, int b) { return a + b; }

int main(int argc, char **argv) {
    const char *nome = argc > 1 ? argv[1] : "mundo";
    printf("Ola, %s! argc+41 = %d\n", nome, soma(argc, 41));
    return 0;
}
