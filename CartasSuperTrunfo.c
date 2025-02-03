#include <stdio.h>    // Biblioteca padrão de entrada e saída
#include <stdlib.h>   // Biblioteca padrão de utilidades, incluindo alocação de memória, controle de processos e outras funções
#include <ctype.h>    // Biblioteca para manipulação de caracteres, como conversão de letras maiúsculas para minúsculas
#include <string.h>   // Biblioteca para manipulação de strings, como cópia, comparação e concatenação

#define MAX_CARTAS 32 // 8 estados * 4 cidades por estado

// Estrutura para representar uma carta com informações sobre uma cidade
typedef struct {
    char estado; // Letra representando o estado (A-H)
    char codigo[4]; // Código da carta (ex: A01)
    char nome[50]; // Nome da cidade
    int populacao; // População da cidade
    float area; // Área da cidade em km²
    float pib; // PIB da cidade
    int pontos_turisticos; // Número de pontos turísticos na cidade
    float densidade_populacional; // Medida de quantas pessoas vivem por quilômetro quadrado
    float pib_per_capita; // Medida da média de produção econômica por pessoa.
} Carta;

// Função para validar se o estado está entre 'A' e 'H'
int validarEstado(char estado) {
    estado = toupper(estado);
    return estado >= 'A' && estado <= 'H';
}

// Função para validar o código da carta
int validarCodigo(char *codigo) {
    return strlen(codigo) == 3 && isalpha(codigo[0]) && isdigit(codigo[1]) && isdigit(codigo[2]);
}

// Função para limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para verificar se uma cidade já está cadastrada
int cidadeJaCadastrada(Carta *cartas, int qtd_cartas, char estado, char *codigo, char *nome) {
    for (int i = 0; i < qtd_cartas; i++) {
        if (cartas[i].estado == estado && (strcmp(cartas[i].codigo, codigo) == 0 || strcmp(cartas[i].nome, nome) == 0)) {
            return 1;
        }
    }
    return 0;
}

// Função para cadastrar uma nova carta
void cadastrarCarta(Carta *cartas, int qtd_cartas) {
    Carta carta;
 
    printf("Olá, bem vindo ao jogo Super Trunfo!\n");

   // Solicitar o estado ao usuário e validar
    do {
        printf("\nDigite o estado (A-H): ");
        scanf(" %c", &carta.estado);
        carta.estado = toupper(carta.estado);
        if (!validarEstado(carta.estado)) {
            printf("Estado inválido! Insira uma letra de A a H.\n");
        }
    } while (!validarEstado(carta.estado));
    
    // Solicitar o código da carta ao usuário e validar
    do {
        printf("Digite o código da carta (ex: A01, B02): ");
        scanf(" %s", carta.codigo);
        if (!validarCodigo(carta.codigo)) {
            printf("Código inválido! Formato correto: Letra + dois dígitos (ex: A01, B02).\n");
        }
    } while (!validarCodigo(carta.codigo));
    
    // Solicitar o nome da cidade ao usuário
    printf("Digite o nome da cidade: ");
    limparBuffer(); // Limpar buffer de entrada
    fgets(carta.nome, sizeof(carta.nome), stdin);
    carta.nome[strcspn(carta.nome, "\n")] = '\0'; // Remover o caractere de nova linha

    // Verificar se a cidade já está cadastrada
    if (cidadeJaCadastrada(cartas, qtd_cartas, carta.estado, carta.codigo, carta.nome)) {
        printf("Erro: A cidade com o estado e código ou nome fornecidos já está cadastrada!\n");
        return;
    }

    // Solicitar a população da cidade ao usuário
    printf("Digite a população: ");
    while (scanf(" %d", &carta.populacao) != 1 || carta.populacao < 0) {
        printf("Valor inválido! Digite um número inteiro positivo para a população: ");
        limparBuffer(); // Limpar buffer de entrada
    }
    
    // Solicitar a área da cidade ao usuário
    printf("Digite a área em km²: ");
    while (scanf(" %f", &carta.area) != 1 || carta.area <= 0) {
        printf("Valor inválido! Digite um número positivo para a área: ");
        limparBuffer(); // Limpar buffer de entrada
    }
    
    // Solicitar o PIB da cidade ao usuário
    printf("Digite o PIB: ");
    while (scanf(" %f", &carta.pib) != 1 || carta.pib < 0) {
        printf("Valor inválido! Digite um número positivo para o PIB: ");
        limparBuffer(); // Limpar buffer de entrada
    }
    
    // Solicitar o número de pontos turísticos da cidade ao usuário
    printf("Digite o número de pontos turísticos: ");
    while (scanf(" %d", &carta.pontos_turisticos) != 1 || carta.pontos_turisticos < 0) {
        printf("Valor inválido! Digite um número inteiro positivo para pontos turísticos: ");
        limparBuffer(); // Limpar buffer de entrada
    }

    // Calcular densidade populacional e PIB per capita
    carta.densidade_populacional = (float)carta.populacao / carta.area;
    carta.pib_per_capita = (float)carta.pib / carta.populacao;

    // Adicionar a nova carta ao array de cartas
    cartas[qtd_cartas] = carta;
}

// Função para exibir uma carta cadastrada
void exibirCarta(const Carta *carta) {
    printf("\n=== Carta Cadastrada ===\n");
    printf("Estado: %c\n", carta->estado);
    printf("Código: %s\n", carta->codigo);
    printf("Cidade: %s\n", carta->nome);
    printf("População: %d habitantes\n", carta->populacao);
    printf("Área: %.2f km²\n", carta->area);
    printf("Densidade Populacional: %.2f pessoas/km²\n", carta->densidade_populacional);
    printf("PIB: %.2f bilhões de reais\n", carta->pib);
    printf("PIB per Capita: %f reais\n", carta->densidade_populacional);
    printf("Pontos turísticos: %d\n", carta->pontos_turisticos);
    printf("=======================\n");
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
        continuar = toupper(continuar);
    } while (continuar == 'S');

    printf("\nCadastro finalizado!\n");
    return 0;
}
