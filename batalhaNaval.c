#include <stdio.h>
#include <stdbool.h>

// Função para calcular valor absoluto de um inteiro (sem stdlib.h)
int valor_absoluto(int x) {
    return x < 0 ? -x : x;
}

int main() {
    // Tamanhos fixos
    int tamanho_tabuleiro = 10;
    int tamanho_navio = 3;
    int tamanho_habilidade = 5;

    // Tabuleiro principal
    int tabuleiro[10][10];

    // Matrizes das habilidades
    int habilidade_cone[5][5];
    int habilidade_cruz[5][5];
    int habilidade_octaedro[5][5];

    // Inicializa o tabuleiro com água (0)
    for (int i = 0; i < tamanho_tabuleiro; i++)
        for (int j = 0; j < tamanho_tabuleiro; j++)
            tabuleiro[i][j] = 0;

    // --- POSICIONAMENTO DOS NAVIOS ---
    // Horizontal
    int navio1_linha = 1, navio1_coluna = 2;
    for (int i = 0; i < tamanho_navio; i++)
        if (navio1_coluna + i < tamanho_tabuleiro)
            tabuleiro[navio1_linha][navio1_coluna + i] = 3;

    // Vertical
    int navio2_linha = 4, navio2_coluna = 1;
    for (int i = 0; i < tamanho_navio; i++)
        if (navio2_linha + i < tamanho_tabuleiro)
            tabuleiro[navio2_linha + i][navio2_coluna] = 3;

    // Diagonal crescente
    int navio3_linha = 6, navio3_coluna = 0;
    for (int i = 0; i < tamanho_navio; i++)
        if (navio3_linha + i < tamanho_tabuleiro && navio3_coluna + i < tamanho_tabuleiro)
            tabuleiro[navio3_linha + i][navio3_coluna + i] = 3;

    // Diagonal decrescente
    int navio4_linha = 2, navio4_coluna = 9;
    for (int i = 0; i < tamanho_navio; i++)
        if (navio4_linha + i < tamanho_tabuleiro && navio4_coluna - i >= 0)
            tabuleiro[navio4_linha + i][navio4_coluna - i] = 3;

    // --- MATRIZES DE HABILIDADE ---

    // Inicializa as matrizes das habilidades com 0
    for (int i = 0; i < tamanho_habilidade; i++)
        for (int j = 0; j < tamanho_habilidade; j++)
            habilidade_cone[i][j] = habilidade_cruz[i][j] = habilidade_octaedro[i][j] = 0;

    // CONE: ponto no topo, expande para baixo
    for (int i = 0; i < tamanho_habilidade; i++) {
        int centro = tamanho_habilidade / 2;
        for (int j = 0; j < tamanho_habilidade; j++) {
            int dist = valor_absoluto(j - centro);
            if (dist <= i) // Expande lateralmente conforme desce
                habilidade_cone[i][j] = 1;
        }
    }

    // CRUZ: linhas centrais
    for (int i = 0; i < tamanho_habilidade; i++)
        for (int j = 0; j < tamanho_habilidade; j++)
            if (i == tamanho_habilidade / 2 || j == tamanho_habilidade / 2)
                habilidade_cruz[i][j] = 1;

    // OCTAEDRO: formato losango (distância de Manhattan)
    for (int i = 0; i < tamanho_habilidade; i++)
        for (int j = 0; j < tamanho_habilidade; j++) {
            int centro = tamanho_habilidade / 2;
            int dist = valor_absoluto(i - centro) + valor_absoluto(j - centro);
            if (dist <= centro)
                habilidade_octaedro[i][j] = 1;
        }

    // --- SOBREPOSIÇÃO DAS HABILIDADES NO TABULEIRO ---

    // Pontos de origem das habilidades
    int cone_origem_linha = 1, cone_origem_coluna = 5;
    int cruz_origem_linha = 6, cruz_origem_coluna = 5;
    int octaedro_origem_linha = 3, octaedro_origem_coluna = 7;

    // Aplica CONE
    for (int i = 0; i < tamanho_habilidade; i++)
        for (int j = 0; j < tamanho_habilidade; j++)
            if (habilidade_cone[i][j] == 1) {
                int pos_linha = cone_origem_linha + i - (tamanho_habilidade / 2);
                int pos_coluna = cone_origem_coluna + j - (tamanho_habilidade / 2);
                if (pos_linha >= 0 && pos_linha < tamanho_tabuleiro && pos_coluna >= 0 && pos_coluna < tamanho_tabuleiro)
                    if (tabuleiro[pos_linha][pos_coluna] != 3)
                        tabuleiro[pos_linha][pos_coluna] = 5;
            }

    // Aplica CRUZ
    for (int i = 0; i < tamanho_habilidade; i++)
        for (int j = 0; j < tamanho_habilidade; j++)
            if (habilidade_cruz[i][j] == 1) {
                int pos_linha = cruz_origem_linha + i - (tamanho_habilidade / 2);
                int pos_coluna = cruz_origem_coluna + j - (tamanho_habilidade / 2);
                if (pos_linha >= 0 && pos_linha < tamanho_tabuleiro && pos_coluna >= 0 && pos_coluna < tamanho_tabuleiro)
                    if (tabuleiro[pos_linha][pos_coluna] != 3)
                        tabuleiro[pos_linha][pos_coluna] = 5;
            }

    // Aplica OCTAEDRO
    for (int i = 0; i < tamanho_habilidade; i++)
        for (int j = 0; j < tamanho_habilidade; j++)
            if (habilidade_octaedro[i][j] == 1) {
                int pos_linha = octaedro_origem_linha + i - (tamanho_habilidade / 2);
                int pos_coluna = octaedro_origem_coluna + j - (tamanho_habilidade / 2);
                if (pos_linha >= 0 && pos_linha < tamanho_tabuleiro && pos_coluna >= 0 && pos_coluna < tamanho_tabuleiro)
                    if (tabuleiro[pos_linha][pos_coluna] != 3)
                        tabuleiro[pos_linha][pos_coluna] = 5;
            }

    // --- EXIBIÇÃO ---
    printf("\n=== TABULEIRO FINAL COM HABILIDADES ===\n");
    printf("Legenda: 0=Água | 3=Navio | 5=Área de Efeito\n\n");

    for (int i = 0; i < tamanho_tabuleiro; i++) {
        for (int j = 0; j < tamanho_tabuleiro; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    // Exibe as matrizes das habilidades
    printf("\n=== MATRIZ HABILIDADE CONE ===\n");
    for (int i = 0; i < tamanho_habilidade; i++) {
        for (int j = 0; j < tamanho_habilidade; j++) {
            printf("%d ", habilidade_cone[i][j]);
        }
        printf("\n");
    }

    printf("\n=== MATRIZ HABILIDADE CRUZ ===\n");
    for (int i = 0; i < tamanho_habilidade; i++) {
        for (int j = 0; j < tamanho_habilidade; j++) {
            printf("%d ", habilidade_cruz[i][j]);
        }
        printf("\n");
    }

    printf("\n=== MATRIZ HABILIDADE OCTAEDRO ===\n");
    for (int i = 0; i < tamanho_habilidade; i++) {
        for (int j = 0; j < tamanho_habilidade; j++) {
            printf("%d ", habilidade_octaedro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
