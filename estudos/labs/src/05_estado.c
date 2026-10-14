/* Lab 05 — Fluxo de controle e tabelas de salto.
 * Objetivo: identificar a máquina de estados, o switch (jump table em -O2)
 * e descrever em português o que o programa reconhece.
 */
#include <stdio.h>

enum estado { INICIO, NUMERO, PONTO, DECIMAL, ERRO };

static int reconhece(const char *s) {
    enum estado e = INICIO;
    for (; *s; s++) {
        char c = *s;
        int digito = c >= '0' && c <= '9';
        switch (e) {
        case INICIO:  e = digito ? NUMERO : (c == '-' ? INICIO : ERRO); break;
        case NUMERO:  e = digito ? NUMERO : (c == '.' ? PONTO : ERRO); break;
        case PONTO:   e = digito ? DECIMAL : ERRO; break;
        case DECIMAL: e = digito ? DECIMAL : ERRO; break;
        case ERRO:    return 0;
        }
    }
    return e == NUMERO || e == DECIMAL;
}

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++)
        printf("%-12s %s\n", argv[i], reconhece(argv[i]) ? "valido" : "invalido");
    return 0;
}
