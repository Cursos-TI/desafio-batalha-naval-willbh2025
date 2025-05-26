#include <stdio.h>
#include <stdbool.h>

int main() {
    // Tamanho do tabuleiro e dos navios definidos por variáveis constantes
    const int tamanho_tabuleiro = 10;
    const int tamanho_navio = 3;

    int tabuleiro[10][10] = {0}; // Inicializa todas as posições com 0 (água)

    // Coordenadas iniciais dos navios (definidas diretamente no código)
    int linha_horizontal = 2, coluna_horizontal = 3; // Navio horizontal
    int linha_vertical = 5, coluna_vertical = 6;     // Navio vertical

    bool posicoes_validas = true;

    // Validação dos limites do navio horizontal
    if (linha_horizontal < 0 || linha_horizontal >= tamanho_tabuleiro ||
        coluna_horizontal < 0 || (coluna_horizontal + tamanho_navio - 1) >= tamanho_tabuleiro) {
        printf("Erro: Navio horizontal fora dos limites do tabuleiro\n");
        posicoes_validas = false;
    }

    // Validação dos limites do navio vertical
    if (coluna_vertical < 0 || coluna_vertical >= tamanho_tabuleiro ||
        linha_vertical < 0 || (linha_vertical + tamanho_navio - 1) >= tamanho_tabuleiro) {
        printf("Erro: Navio vertical fora dos limites do tabuleiro\n");
        posicoes_validas = false;
    }

    // Vetores para guardar as posições ocupadas pelos navios
    int navio_horizontal[3];
    int navio_vertical[3];

    if (posicoes_validas) {
        // Calcula as posições do navio horizontal
        for (int i = 0; i < tamanho_navio; i++) {
            navio_horizontal[i] = linha_horizontal * tamanho_tabuleiro + (coluna_horizontal + i);
        }

        // Calcula as posições do navio vertical
        for (int i = 0; i < tamanho_navio; i++) {
            navio_vertical[i] = (linha_vertical + i) * tamanho_tabuleiro + coluna_vertical;
        }

        // Verifica sobreposição entre os navios
        for (int i = 0; i < tamanho_navio; i++) {
            for (int j = 0; j < tamanho_navio; j++) {
                if (navio_horizontal[i] == navio_vertical[j]) {
                    printf("Erro: Navios se sobrepõem na posição linha %d, coluna %d\n",
                           navio_horizontal[i] / tamanho_tabuleiro, navio_horizontal[i] % tamanho_tabuleiro);
                    posicoes_validas = false;
                    break;
                }
            }
            if (!posicoes_validas) break;
        }
    }

    if (!posicoes_validas) {
        printf("Ajuste as coordenadas e execute novamente.\n");
        return 1;
    }

    // Posiciona o navio horizontal no tabuleiro
    for (int i = 0; i < tamanho_navio; i++) {
        int linha = navio_horizontal[i] / tamanho_tabuleiro;
        int coluna = navio_horizontal[i] % tamanho_tabuleiro;
        tabuleiro[linha][coluna] = 3;
    }

    // Posiciona o navio vertical no tabuleiro
    for (int i = 0; i < tamanho_navio; i++) {
        int linha = navio_vertical[i] / tamanho_tabuleiro;
        int coluna = navio_vertical[i] % tamanho_tabuleiro;
        tabuleiro[linha][coluna] = 3;
    }

    // Exibe o tabuleiro
    printf("\nTabuleiro Final:\n");
    for (int i = 0; i < tamanho_tabuleiro; i++) {
        for (int j = 0; j < tamanho_tabuleiro; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
