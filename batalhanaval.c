#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Inicializa o tabuleiro com agua (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Verifica se ha espaco para o navio sem sair do tabuleiro ou sobrepor
int espacoDisponivel(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = coluna;

        if (direcao == 'H') c += i;
        else if (direcao == 'V') l += i;
        else if (direcao == 'D') { l += i; c += i; }
        else if (direcao == 'I') { l += i; c -= i; }

        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO || tabuleiro[l][c] == NAVIO)
            return 0;
    }
    return 1;
}

// Posiciona o navio na direcao indicada ('H', 'V', 'D', 'I')
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (direcao == 'H')
            tabuleiro[linha][coluna + i] = NAVIO;
        else if (direcao == 'V')
            tabuleiro[linha + i][coluna] = NAVIO;
        else if (direcao == 'D')
            tabuleiro[linha + i][coluna + i] = NAVIO;
        else if (direcao == 'I')
            tabuleiro[linha + i][coluna - i] = NAVIO;
    }
}

// Exibe o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d", i);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Navio horizontal 
    if (espacoDisponivel(tabuleiro, 0, 0, 'H'))
        posicionarNavio(tabuleiro, 0, 0, 'H');
    else
        printf("Erro ao posicionar navio horizontal 1\n");

    // Navio horizontal 
    if (espacoDisponivel(tabuleiro, 2, 6, 'H'))
        posicionarNavio(tabuleiro, 2, 6, 'H');
    else
        printf("Erro ao posicionar navio horizontal 2\n");

    // Navio diagonal 
    if (espacoDisponivel(tabuleiro, 4, 0, 'D'))
        posicionarNavio(tabuleiro, 4, 0, 'D');
    else
        printf("Erro ao posicionar navio diagonal ↘\n");

    // Navio diagonal 
    if (espacoDisponivel(tabuleiro, 4, 9, 'I'))
        posicionarNavio(tabuleiro, 4, 9, 'I');
    else
        printf("Erro ao posicionar navio diagonal ↙\n");

    exibirTabuleiro(tabuleiro);

    return 0;
}
