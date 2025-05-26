#include <stdio.h>
#include <stdbool.h>

int main() {
    // Constantes para o jogo
    const int tamanho_tabuleiro = 10;
    const int tamanho_navio = 3;
    
    // Declaração do tabuleiro sem inicialização automática
    int tabuleiro[10][10];
    
    // Inicializa manualmente todas as posições com 0 (água)
    for (int i = 0; i < tamanho_tabuleiro; i++) {
        for (int j = 0; j < tamanho_tabuleiro; j++) {
            tabuleiro[i][j] = 0;
        }
    }
    
    // Coordenadas iniciais dos quatro navios
    int navio1_linha = 1, navio1_coluna = 2;  // Navio horizontal
    int navio2_linha = 4, navio2_coluna = 1;  // Navio vertical
    int navio3_linha = 6, navio3_coluna = 0;  // Navio diagonal crescente
    int navio4_linha = 2, navio4_coluna = 9;  // Navio diagonal decrescente
    
    bool posicionamento_valido = true;
    
    // Array para armazenar todas as posições ocupadas (para verificar sobreposição)
    int posicoes_ocupadas[50][2]; // Máximo de posições possíveis
    int total_posicoes = 0;
    
    // Função para verificar se uma posição está dentro dos limites
    bool dentro_limites(int linha, int coluna) {
        return (linha >= 0 && linha < tamanho_tabuleiro && 
                coluna >= 0 && coluna < tamanho_tabuleiro);
    }
    
    // Função para verificar se uma posição já está ocupada
    bool posicao_ocupada(int linha, int coluna) {
        for (int i = 0; i < total_posicoes; i++) {
            if (posicoes_ocupadas[i][0] == linha && posicoes_ocupadas[i][1] == coluna) {
                return true;
            }
        }
        return false;
    }
    
    // Função para adicionar posição à lista de ocupadas
    void adicionar_posicao(int linha, int coluna) {
        posicoes_ocupadas[total_posicoes][0] = linha;
        posicoes_ocupadas[total_posicoes][1] = coluna;
        total_posicoes++;
    }
    
    // Valida e posiciona navio horizontal
    printf("Posicionando navio horizontal...\n");
    for (int i = 0; i < tamanho_navio; i++) {
        int linha = navio1_linha;
        int coluna = navio1_coluna + i;
        
        if (!dentro_limites(linha, coluna)) {
            printf("Erro: Navio horizontal sai dos limites do tabuleiro\n");
            posicionamento_valido = false;
            break;
        }
        
        if (posicao_ocupada(linha, coluna)) {
            printf("Erro: Navio horizontal sobrepõe com outro navio\n");
            posicionamento_valido = false;
            break;
        }
        
        adicionar_posicao(linha, coluna);
        tabuleiro[linha][coluna] = 3;
    }
    
    // Valida e posiciona navio vertical
    if (posicionamento_valido) {
        printf("Posicionando navio vertical...\n");
        for (int i = 0; i < tamanho_navio; i++) {
            int linha = navio2_linha + i;
            int coluna = navio2_coluna;
            
            if (!dentro_limites(linha, coluna)) {
                printf("Erro: Navio vertical sai dos limites do tabuleiro\n");
                posicionamento_valido = false;
                break;
            }
            
            if (posicao_ocupada(linha, coluna)) {
                printf("Erro: Navio vertical sobrepõe com outro navio\n");
                posicionamento_valido = false;
                break;
            }
            
            adicionar_posicao(linha, coluna);
            tabuleiro[linha][coluna] = 3;
        }
    }
    
    // Valida e posiciona navio diagonal crescente
    if (posicionamento_valido) {
        printf("Posicionando navio diagonal crescente...\n");
        for (int i = 0; i < tamanho_navio; i++) {
            int linha = navio3_linha + i;
            int coluna = navio3_coluna + i;
            
            if (!dentro_limites(linha, coluna)) {
                printf("Erro: Navio diagonal crescente sai dos limites do tabuleiro\n");
                posicionamento_valido = false;
                break;
            }
            
            if (posicao_ocupada(linha, coluna)) {
                printf("Erro: Navio diagonal crescente sobrepõe com outro navio\n");
                posicionamento_valido = false;
                break;
            }
            
            adicionar_posicao(linha, coluna);
            tabuleiro[linha][coluna] = 3;
        }
    }
    
    // Valida e posiciona navio diagonal decrescente
    if (posicionamento_valido) {
        printf("Posicionando navio diagonal decrescente...\n");
        for (int i = 0; i < tamanho_navio; i++) {
            int linha = navio4_linha + i;
            int coluna = navio4_coluna - i;
            
            if (!dentro_limites(linha, coluna)) {
                printf("Erro: Navio diagonal decrescente sai dos limites do tabuleiro\n");
                posicionamento_valido = false;
                break;
            }
            
            if (posicao_ocupada(linha, coluna)) {
                printf("Erro: Navio diagonal decrescente sobrepõe com outro navio\n");
                posicionamento_valido = false;
                break;
            }
            
            adicionar_posicao(linha, coluna);
            tabuleiro[linha][coluna] = 3;
        }
    }
    
    // Verifica se todos os navios foram posicionados com sucesso
    if (!posicionamento_valido) {
        printf("Falha no posicionamento dos navios. Ajuste as coordenadas.\n");
        return 1;
    }
    
    // Exibe o tabuleiro completo
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n");
    printf("Legenda: 0 = Água, 3 = Navio\n\n");
    
    for (int i = 0; i < tamanho_tabuleiro; i++) {
        for (int j = 0; j < tamanho_tabuleiro; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    
    printf("\nTotal de posições ocupadas: %d\n", total_posicoes);
    printf("Navios posicionados com sucesso!\n");
    
    return 0;
}
