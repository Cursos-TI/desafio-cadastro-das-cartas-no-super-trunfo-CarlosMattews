#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_CARTAS 2

// Estrutura para representar uma carta com informações sobre uma cidade
typedef struct {
    char estado; // Letra representando o estado (A-H)
    char codigo[4]; // Código da carta (ex: A01, B02)
    char nome[50]; // Nome da cidade
    unsigned long int populacao; // População da cidade (agora do tipo unsigned long int)
    float area; // Área da cidade em km²
    float pib; // PIB da cidade
    int pontos_turisticos; // Número de pontos turísticos na cidade
    float densidade_populacional; // Medida de quantas pessoas vivem por quilômetro quadrado
    float pib_per_capita; // Medida da média de produção econômica por pessoa.
    float super_poder; // Super Poder: Soma de todas as propriedades numéricas
} Carta;

// Função para limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para cadastrar uma nova carta
void cadastrarCarta(Carta *cartas, int qtd_cartas) {
    Carta carta;

    printf("Olá, bem-vindo ao jogo Super Trunfo!\n");

    // Solicitar o estado ao usuário
    printf("\nDigite o estado (A-H): ");
    scanf(" %c", &carta.estado);
    carta.estado = toupper(carta.estado); // Converte o caractere para maiúscula
    
    // Solicitar o código da carta ao usuário
    printf("Digite o código da carta (ex: A01, B02): ");
    scanf(" %s", carta.codigo);
    
    // Solicitar o nome da cidade ao usuário
    printf("Digite o nome da cidade: ");
    limparBuffer(); // Limpar buffer de entrada
    fgets(carta.nome, sizeof(carta.nome), stdin);
    carta.nome[strcspn(carta.nome, "\n")] = '\0'; // Remover o caractere de nova linha

    // Solicitar a população da cidade ao usuário (agora como unsigned long int)
    printf("Digite a população: ");
    scanf(" %lu", &carta.populacao);

    // Solicitar a área da cidade ao usuário
    printf("Digite a área em km²: ");
    scanf(" %f", &carta.area);
    
    // Solicitar o PIB da cidade ao usuário
    printf("Digite o PIB: ");
    scanf(" %f", &carta.pib);
    
    // Solicitar o número de pontos turísticos da cidade ao usuário
    printf("Digite o número de pontos turísticos: ");
    scanf(" %d", &carta.pontos_turisticos);

    // Calcular densidade populacional e PIB per capita
    carta.densidade_populacional = carta.populacao / carta.area;
    carta.pib_per_capita = carta.pib / carta.populacao;

    // Calcular o valor de super_poder
    carta.super_poder = carta.populacao + carta.area + carta.pib + carta.pontos_turisticos + (1.0 / carta.densidade_populacional);

    // Adicionar a nova carta ao array de cartas
    cartas[qtd_cartas] = carta;
}

// Função para exibir uma carta cadastrada
void exibirCarta(const Carta *carta) {
    printf("\n=== Carta Cadastrada ===\n");
    printf("Estado: %c\n", carta->estado);
    printf("Código: %s\n", carta->codigo);
    printf("Cidade: %s\n", carta->nome);
    printf("População: %lu habitantes\n", carta->populacao); // Atualizado para unsigned long int
    printf("Área: %.2f km²\n", carta->area);
    printf("Densidade Populacional: %.2f pessoas/km²\n", carta->densidade_populacional);
    printf("PIB: %.2f bilhões de reais\n", carta->pib);
    printf("PIB per Capita: %.2f reais\n", carta->pib_per_capita);
    printf("Pontos turísticos: %d\n", carta->pontos_turisticos);
    printf("Super Poder: %.2f\n", carta->super_poder);
    printf("=======================\n");
}

// Compara duas cartas com base nas suas propriedades
void compararCartas(const Carta *carta1, const Carta *carta2) {
    printf("\n=== Comparação de Cartas ===\n");

    printf("População:\n");
    printf("Carta 1: %lu habitantes\n", carta1->populacao); // Atualizado para unsigned long int
    printf("Carta 2: %lu habitantes\n", carta2->populacao);
    printf(carta1->populacao > carta2->populacao ? "Carta 1 venceu (1)\n" : "Carta 2 venceu (0)\n");

    printf("\nÁrea:\n");
    printf("Carta 1: %.2f km²\n", carta1->area);
    printf("Carta 2: %.2f km²\n", carta2->area);
    printf(carta1->area > carta2->area ? "Carta 1 venceu (1)\n" : "Carta 2 venceu (0)\n");

    printf("\nPIB:\n");
    printf("Carta 1: %.2f\n", carta1->pib);
    printf("Carta 2: %.2f\n", carta2->pib);
    printf(carta1->pib > carta2->pib ? "Carta 1 venceu (1)\n" : "Carta 2 venceu (0)\n");

    printf("\nPontos turísticos:\n");
    printf("Carta 1: %d\n", carta1->pontos_turisticos);
    printf("Carta 2: %d\n", carta2->pontos_turisticos);
    printf(carta1->pontos_turisticos > carta2->pontos_turisticos ? "Carta 1 venceu (1)\n" : "Carta 2 venceu (0)\n");

    printf("\nDensidade Populacional:\n");
    printf("Carta 1: %.2f\n", carta1->densidade_populacional);
    printf("Carta 2: %.2f\n", carta2->densidade_populacional);
    printf(carta1->densidade_populacional < carta2->densidade_populacional ? "Carta 1 venceu (1)\n" : "Carta 2 venceu (0)\n");

    printf("\nPIB per Capita:\n");
    printf("Carta 1: %.2f\n", carta1->pib_per_capita);
    printf("Carta 2: %.2f\n", carta2->pib_per_capita);
    printf(carta1->pib_per_capita > carta2->pib_per_capita ? "Carta 1 venceu (1)\n" : "Carta 2 venceu (0)\n");

    printf("\nSuper Poder:\n");
    printf("Carta 1: %.2f\n", carta1->super_poder);
    printf("Carta 2: %.2f\n", carta2->super_poder);
    printf(carta1->super_poder > carta2->super_poder ? "Carta 1 venceu (1)\n" : "Carta 2 venceu (0)\n");

    printf("===========================\n");
}

// Função principal
int main() {
    Carta cartas[MAX_CARTAS]; // Array para armazenar as cartas
    int qtd_cartas = 0; // Contador de cartas cadastradas
    char continuar; // Variável para verificar se o usuário deseja continuar cadastrando

    // Loop para cadastrar cartas
    do {
        if (qtd_cartas >= MAX_CARTAS) {
            printf("\nLimite máximo de cartas atingido!\n");
            break;
        }
        
        cadastrarCarta(cartas, qtd_cartas);
        exibirCarta(&cartas[qtd_cartas]);
        qtd_cartas++;

        // Verificar se o usuário deseja cadastrar outra carta
        printf("\nDeseja cadastrar outra carta? (S/N): ");
        scanf(" %c", &continuar);
        continuar = toupper(continuar); // Converte o caractere para maiúscula
    } while (continuar == 'S');

    printf("\nCadastro finalizado!\n");

    // Parte para permitir a comparação de cartas
    if (qtd_cartas >= 2) {
        int indice1, indice2;
        printf("\nDigite o índice da primeira carta a ser comparada (0 a %d): ", qtd_cartas - 1);
        scanf(" %d", &indice1);
        printf("Digite o índice da segunda carta a ser comparada (0 a %d): ", qtd_cartas - 1);
        scanf(" %d", &indice2);

        if (indice1 >= 0 && indice1 < qtd_cartas && indice2 >= 0 && indice2 < qtd_cartas) {
            compararCartas(&cartas[indice1], &cartas[indice2]);
        } else {
            printf("\nÍndices inválidos! Não foi possível realizar a comparação.\n");
        }
    }

    return 0;
}
