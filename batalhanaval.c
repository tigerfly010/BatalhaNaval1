#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define AREA_HABILIDADE 5

void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

int espacoDisponivel(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char orientacao) {
    if (orientacao == 'H') {
        if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
        for (int c = coluna; c < coluna + TAMANHO_NAVIO; c++) {
            if (tabuleiro[linha][c] != AGUA) return 0;
        }
    } else if (orientacao == 'V') {
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
        for (int l = linha; l < linha + TAMANHO_NAVIO; l++) {
            if (tabuleiro[l][coluna] != AGUA) return 0;
        }
    }
    return 1;
}

void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char orientacao) {
    if (orientacao == 'H') {
        for (int c = coluna; c < coluna + TAMANHO_NAVIO; c++) {
            tabuleiro[linha][c] = NAVIO;
        }
    } else if (orientacao == 'V') {
        for (int l = linha; l < linha + TAMANHO_NAVIO; l++) {
            tabuleiro[l][coluna] = NAVIO;
        }
    }
}

int espacoDisponivelDiagonal1(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna + i] != AGUA) return 0;
    }
    return 1;
}

void posicionarNavioDiagonal1(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna + i] = NAVIO;
    }
}

int espacoDisponivelDiagonal2(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna - TAMANHO_NAVIO + 1 < 0) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna - i] != AGUA) return 0;
    }
    return 1;
}

void posicionarNavioDiagonal2(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna - i] = NAVIO;
    }
}

void criarHabilidadeCone(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            habilidade[i][j] = 0;

    habilidade[0][2] = 1;
    habilidade[1][1] = 1; habilidade[1][2] = 1; habilidade[1][3] = 1;
    habilidade[2][0] = 1; habilidade[2][1] = 1; habilidade[2][2] = 1; habilidade[2][3] = 1; habilidade[2][4] = 1;
}

void criarHabilidadeCruz(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            habilidade[i][j] = 0;

    int centro = 2;
    for (int j = 0; j < 5; j++) habilidade[centro][j] = 1;
    for (int i = 0; i < 5; i++) habilidade[i][centro] = 1;
}

void criarHabilidadeOctaedro(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            habilidade[i][j] = 0;

    habilidade[0][2] = 1;
    habilidade[1][1] = 1; habilidade[1][2] = 1; habilidade[1][3] = 1;
    habilidade[2][0] = 1; habilidade[2][1] = 1; habilidade[2][2] = 1; habilidade[2][3] = 1; habilidade[2][4] = 1;
    habilidade[3][1] = 1; habilidade[3][2] = 1; habilidade[3][3] = 1;
    habilidade[4][2] = 1;
}

void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[5][5], int origemLinha, int origemColuna) {
    int centro = 2;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (habilidade[i][j] == 1) {
                int linha = origemLinha - centro + i;
                int coluna = origemColuna - centro + j;

                if (linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO) {
                    if (tabuleiro[linha][coluna] == AGUA) {
                        tabuleiro[linha][coluna] = AREA_HABILIDADE;
                    }
                }
            }
        }
    }
}

void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   ");
    for (int c = 0; c < TAMANHO_TABULEIRO; c++)
        printf("%2d ", c);
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == AGUA) printf(" . ");
            else if (tabuleiro[i][j] == NAVIO) printf(" N ");
            else if (tabuleiro[i][j] == AREA_HABILIDADE) printf(" * ");
            else printf(" ? ");
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Posiciona navios
    posicionarNavio(tabuleiro, 0, 6, 'H');            
    posicionarNavio(tabuleiro, 6, 0, 'V');            
    posicionarNavioDiagonal1(tabuleiro, 2, 6);        
    posicionarNavioDiagonal2(tabuleiro, 7, 3);        

    int habilidadeCone[5][5], habilidadeCruz[5][5], habilidadeOctaedro[5][5];
    criarHabilidadeCone(habilidadeCone);
    criarHabilidadeCruz(habilidadeCruz);
    criarHabilidadeOctaedro(habilidadeOctaedro);

    aplicarHabilidade(tabuleiro, habilidadeCone, 2, 2);
    aplicarHabilidade(tabuleiro, habilidadeCruz, 5, 4);
    aplicarHabilidade(tabuleiro, habilidadeOctaedro, 7, 7);

    exibirTabuleiro(tabuleiro);

    return 0;
}





