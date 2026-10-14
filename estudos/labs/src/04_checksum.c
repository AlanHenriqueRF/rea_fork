/* Lab 04 — Reconstrução de algoritmo (estilo showcase DX-Ball).
 * Objetivo: a partir do binário -O2-stripped, reescreva `checksum` em C e prove que
 * sua versão dá o mesmo resultado para várias entradas (ver estudos/README.md, Etapa 4).
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint32_t checksum(const unsigned char *dados, size_t n) {
    uint32_t a = 1, b = 0;
    for (size_t i = 0; i < n; i++) {
        a = (a + dados[i]) % 65521;
        b = (b + a) % 65521;
    }
    return (b << 16) | a;
}

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++)
        printf("%s -> %08x\n", argv[i], checksum((const unsigned char *)argv[i], strlen(argv[i])));
    return 0;
}
