#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define OCUPADO 3
#define AGUA 0

// Função para inicializar o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("TABULEIRO BATALHA NAVAL:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para posicionar navio no tabuleiro
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char direcao) {
    // Verifica se a posição inicial e a direção permitem o posicionamento completo do navio
    if (direcao == 'H') { // Horizontal
        if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0; // Fora dos limites

        // Verifica sobreposição
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha][coluna + i] != AGUA) return 0;
        }

        // Posiciona o navio
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha][coluna + i] = OCUPADO;
        }
    } else if (direcao == 'V') { // Vertical
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;

        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna] != AGUA) return 0;
        }

        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha + i][coluna] = OCUPADO;
        }
    } else {
        return 0; // Direção inválida
    }

    return 1; // Sucesso
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // Coordenadas dos navios (definidas no código)
    int linha_horizontal = 2;
    int coluna_horizontal = 4;
    int linha_vertical = 5;
    int coluna_vertical = 7;

    // Posiciona o navio horizontal
    if (!posicionarNavio(tabuleiro, linha_horizontal, coluna_horizontal, 'H')) {
        printf("Erro ao posicionar navio horizontal.\n");
        return 1;
    }

    // Posiciona o navio vertical
    if (!posicionarNavio(tabuleiro, linha_vertical, coluna_vertical, 'V')) {
        printf("Erro ao posicionar navio vertical.\n");
        return 1;
    }

    // Exibe o tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}

