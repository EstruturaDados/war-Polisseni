// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define TAM_NOME 30
#define TAM_COR 10
#define TAM_MISSAO 60
// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
typedef struct{
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
}Territorio;

const char* missoes[] = {
    "Destruir o exército Verde",
    "Conquistar 3 territórios",
    "Conquistar 5 territórios no total",
    "Manter 10 tropas em um único território",
    "Eliminar o exército Azul"
};
// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:
void cadastrarTerritorio(Territorio *mapa,int num_territorios){
    for(int i = 0; i < num_territorios; i++){
        printf("\n    Territorio %d\n", i + 1);

        printf("\nNome do território: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do Exercito: ");
        scanf("%s", mapa[i].cor);

        printf("Número de Tropas: ");
        scanf("%d", &mapa[i].tropas);
    };    
}

void exibirMapa(const Territorio *mapa, int num_territorios){
    printf("\n==================================================\n");
    printf("            MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("==================================================\n\n");
    for(int i = 0; i< num_territorios; i++){
        printf("%d. %s (Exercito %s, Tropas: %d)\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    };    
}

void exibirMenuPrincipal(int *opcao){
    printf("\n          --- MENU ---\n\n");
    printf(" - Opção 1: Iniciar a fase de ataque.\n");
    printf(" - Opção 2: Verificar condição de vitória.\n");
    printf(" - Opção 0: Sair do jogo.\n\n");
    printf("SELECIONE UMA OPÇÃO: ");
    scanf("%d", opcao);
}

void faseDeAtaque(Territorio *mapa, int num_territorios, int *indicieAtacante, int *indicieDefensor){
    printf("\n --- FASE DE ATAQUE ---\n");

    printf("\nEscolha o territorio atacante (1 a %d, ou 0 para sair):  ",num_territorios);
    scanf("%d", indicieAtacante);

    if (*indicieAtacante == 0){
        return;
    }

    *indicieAtacante = *indicieAtacante - 1;

    printf("\nEscolha o territorio defensor (1 a %d): ", num_territorios);
    scanf("%d", indicieDefensor);

    *indicieDefensor = *indicieDefensor - 1;

    if (((*indicieAtacante >= num_territorios) || (*indicieAtacante < 0)) || ((*indicieDefensor >= num_territorios) || (*indicieDefensor < 0))){
        printf("\nINDICIE INVÁLIDO! TENTE NOVAMENTE.\n");
        return;
    } else if(mapa[*indicieAtacante].tropas <= 1){
        printf("\nNÃO É POSSIVEL REALIZAR O ATAQUE COM MENOS DE 2 TROPAS!\n");
        return;

    } else {
        int dadoAtaque = (rand() % 6) + 1;
        int dadoDefesa = (rand() % 6) + 1;

        printf(" \n--- RESULTADO DA BATALHA ---\n");
        printf("\nO atacante %s rolou um dado e tiro: %d\n", mapa[*indicieAtacante].nome, dadoAtaque);
        printf("O defensor %s rolou um dado e tiro: %d\n", mapa[*indicieDefensor].nome, dadoDefesa);

        if (dadoAtaque >= dadoDefesa){
            mapa[*indicieDefensor].tropas --;
            printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");

            if(mapa[*indicieDefensor].tropas == 0){
                strcpy(mapa[*indicieDefensor].cor, mapa[*indicieAtacante].cor);
                mapa[*indicieDefensor].tropas = mapa[*indicieAtacante].tropas / 2;
                mapa[*indicieAtacante].tropas = mapa[*indicieAtacante].tropas / 2;
                printf("CONQUISTA! O territorio %s foi conquistado pelo Exercito %s.",mapa[*indicieDefensor].nome, mapa[*indicieAtacante].cor);
            }
        } else{
            mapa[*indicieAtacante].tropas --;
            printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");
        }
    } 
}

void atribuirMissao(char* destino, const char* missoes[], int totalMissoes){
    int indicieSorteado = rand() % totalMissoes;

    strcpy(destino, missoes[indicieSorteado]);
}

void exibirMissao(const char* missaoJogador){
    printf("\n\n==================================================\n");
    printf("SUA MISSÃO SECRETA:\n");
    printf("-> %s\n", missaoJogador);
    printf("==================================================\n\n");
}

void verificarMissao(const char* missaoJogador, const Territorio* mapa, int num_territorios, const char* corJogador) {
    if (strcmp(missaoJogador, "Destruir o exército Verde") == 0) {
        for (int i = 0; i < num_territorios; i++) {
            if (strcmp(mapa[i].cor, "Verde") == 0) {
                printf("\n--- VERIFICAR MISSÃO ---\n");
                printf("Objetivo: Destruir o exército Verde.\n");
                printf("Status: A missão ainda não foi cumprida.\n");
                return;
            }
        }
        printf("\n--- VERIFICAR MISSÃO ---\n");
        printf("Objetivo: Destruir o exército Verde.\n");
        printf("Status: MISSÃO CUMPRIDA! Parabéns!\n");
        return;
    } else if (strcmp(missaoJogador, "Eliminar o exército Azul") == 0) {
        for (int i = 0; i < num_territorios; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0) {
                printf("\n--- VERIFICAR MISSÃO ---\n");
                printf("Objetivo: Eliminar o exército Azul.\n");
                printf("Status: A missão ainda não foi cumprida.\n");
                return;
            }
        }
        printf("\n--- VERIFICAR MISSÃO ---\n");
        printf("Objetivo: Eliminar o exército Azul.\n");
        printf("Status: MISSÃO CUMPRIDA! Parabéns!\n");
        return;
    } else if (strcmp(missaoJogador, "Conquistar 3 territórios") == 0) {
        int contador = 0;
        for (int i = 0; i < num_territorios; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                contador++;
            }
        }
        printf("\n--- VERIFICAR MISSÃO ---\n");
        printf("Objetivo: Conquistar 3 territórios.\n");
        printf("Status: Você possui %d de 3 territórios.\n", contador);
        if (contador >= 3) {
            printf("MISSÃO CUMPRIDA! Parabéns!\n");
        } else {
            printf("A missão ainda não foi cumprida.\n");
        }
        return;
    } else if (strcmp(missaoJogador, "Conquistar 5 territórios no total") == 0) {
        int contador = 0;
        for (int i = 0; i < num_territorios; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                contador++;
            }
        }
        printf("\n--- VERIFICAR MISSÃO ---\n");
        printf("Objetivo: Conquistar 5 territórios no total.\n");
        printf("Status: Você possui %d de 5 territórios.\n", contador);
        if (contador >= 5) {
            printf("MISSÃO CUMPRIDA! Parabéns!\n");
        } else {
            printf("A missão ainda não foi cumprida.\n");
        }
        return;
    } else if (strcmp(missaoJogador, "Manter 10 tropas em um único território") == 0) {
        for (int i = 0; i < num_territorios; i++) {
            if (mapa[i].tropas >= 10 && strcmp(mapa[i].cor, corJogador) == 0) {
                printf("\n--- VERIFICAR MISSÃO ---\n");
                printf("Objetivo: Manter 10 tropas em um único território.\n");
                printf("Status: MISSÃO CUMPRIDA! O território %s (seu) possui %d tropas.\n", mapa[i].nome, mapa[i].tropas);
                return;
            }
        }        
        printf("\n--- VERIFICAR MISSÃO ---\n");
        printf("Objetivo: Manter 10 tropas em um único território.\n");
        printf("Status: A missão ainda não foi cumprida.\n");
        return;
    }
    printf("\n--- VERIFICAR MISSÃO ---\n");
    printf("Erro: Missão desconhecida.\n");
}

void liberarMemoria(Territorio* mapa, char* missaoJogador){
    free(mapa);
    free(missaoJogador);
}
// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    
    Territorio *mapa;
    int num_territorios;
    int opcao;
    int indicieAtacante;
    int indicieDefensor;
    char* missaoJogador;

    srand(time(NULL));

    printf("\n==================================================\n");
    printf("                     JOGO WAR\n");
    printf("==================================================\n");

    printf("\n--- CADASTRO DE TERRITORIOS ---\n");
    printf("\nNúmero de territorios: ");
    scanf("%d", &num_territorios);

    mapa = (Territorio *) calloc(num_territorios, sizeof(Territorio));
    missaoJogador = (char*) malloc(TAM_MISSAO);

    cadastrarTerritorio(mapa, num_territorios);
    atribuirMissao(missaoJogador, missoes, sizeof(missoes) / sizeof(missoes[0]));
    exibirMissao(missaoJogador);

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

     do {
        exibirMapa(mapa, num_territorios);
        exibirMenuPrincipal(&opcao);
        switch (opcao){
        case 1:
            faseDeAtaque(mapa, num_territorios, &indicieAtacante, &indicieDefensor);
            break;
        case 2:
            verificarMissao(missaoJogador, mapa, num_territorios, mapa[0].cor);
            break;
        case 0:
            printf("\nSaindo do jogo... Obrigado por jogar!\n");
            break;    
        default:
            break;
        }
    } while (opcao != 0);

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.
    liberarMemoria(mapa, missaoJogador);
    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
