/* Lab 02 — Crackme simples.
 * Objetivo: descobrir a senha correta SEM ler este arquivo.
 * Dica: a senha não aparece como texto puro; procure a transformação.
 */
#include <stdio.h>
#include <string.h>

static const unsigned char segredo[] = {0x27, 0x31, 0x36, 0x37, 0x26, 0x23, 0x30, 0x00};

static int confere(const char *tentativa) {
    size_t n = strlen(tentativa);
    if (n != sizeof(segredo) - 1) return 0;
    for (size_t i = 0; i < n; i++) {
        if ((unsigned char)(tentativa[i] ^ 0x42) != segredo[i]) return 0;
    }
    return 1;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "uso: %s <senha>\n", argv[0]);
        return 2;
    }
    puts(confere(argv[1]) ? "Acesso liberado." : "Senha incorreta.");
    return 0;
}
