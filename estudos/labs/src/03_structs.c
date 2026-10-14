/* Lab 03 — Recuperando structs.
 * Objetivo: reconstruir o layout de `struct item` (campos, tipos, offsets e tamanho)
 * só olhando os acessos de memória no binário stripped.
 */
#include <stdio.h>
#include <stdint.h>

struct item {
    uint32_t id;
    char nome[12];
    uint16_t quantidade;
    double preco;
};

static double valor_total(const struct item *itens, int n) {
    double total = 0;
    for (int i = 0; i < n; i++) total += itens[i].quantidade * itens[i].preco;
    return total;
}

int main(void) {
    struct item estoque[] = {
        {1, "caderno", 10, 12.5},
        {2, "caneta", 50, 2.0},
        {3, "mochila", 2, 149.9},
    };
    int n = (int)(sizeof(estoque) / sizeof(estoque[0]));
    for (int i = 0; i < n; i++)
        printf("#%u %-10s x%u\n", estoque[i].id, estoque[i].nome, estoque[i].quantidade);
    printf("Total: %.2f\n", valor_total(estoque, n));
    return 0;
}
