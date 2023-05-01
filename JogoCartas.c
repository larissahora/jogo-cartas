#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>   // implementar threads
#include <semaphore.h> // implementar semáforos
#include <unistd.h>
#include <ctype.h> // para utilizar a função toupper();

// variáveis globais:
int comparadorPrioritario[2] = {-1, 0}, comparadorSecundario[2] = {-1, 0}; // comparadores acessados pelas threads t1 e t2
int intCartasJ1[4], intCartasJ2[4];                                        // valores das cartas acessados pelas threads
int rodada;                                                                // contador global
pthread_mutex_t mutex;                                                     // define o mutex (semáforo simples)

int charToInt(char c) // função que define a pontuação por carta
{
    switch (c)
    {
    case 'J':
        return 1;
    case 'Q':
        return 2;
    case 'K':
        return 3;
    case 'A':
        return 4;
    default:
        return 0; // se o jogador insere um valor inválido o sistema atribui pontuação zero à sua escolha
    }
}

void *threadBody1(void *id)
{ // função para thread1 vinculada ao Jogador 1
    int jogador = 1;
    pthread_mutex_lock(&mutex); // pede acesso ao semáforo
    if (comparadorPrioritario[0] == -1)
    { // grava no contador prioritário se o mesmo estiver com valor defaut (-1)
        comparadorPrioritario[0] = intCartasJ1[rodada];
        comparadorPrioritario[1] = jogador; // grava no índice "1" o número do jogador que gravou no índice "0"
    }
    else
    {
        comparadorSecundario[0] = intCartasJ1[rodada]; // grava no contador secundário
        comparadorSecundario[1] = jogador;             // grava no índice "1" o número do jogador que gravou no índice "0"
    }
    pthread_mutex_unlock(&mutex); // avisa ao semáforo que já efetuou a ação
    // sleep(1);                     // aguarda 1 segundo
    pthread_exit(NULL); // destrói a thread
}

void *threadBody2(void *id)
{ // função para thread 2, similar a anterior
    int jogador = 2;
    pthread_mutex_lock(&mutex);
    if (comparadorPrioritario[0] == -1)
    {
        comparadorPrioritario[0] = intCartasJ2[rodada];
        comparadorPrioritario[1] = jogador;
    }
    else
    {
        comparadorSecundario[0] = intCartasJ2[rodada];
        comparadorSecundario[1] = jogador;
    }
    pthread_mutex_unlock(&mutex);
    // sleep(1);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    char linha[100];                          // variável para captura da linha de entrada
    char *letra;                              // para salvar o caractere oriundo da quebra da linha
    char cartasJ1[4], cartasJ2[4], caractere; // para armazenar os caracteres nos respectivos vetores
    int i, j;                                 // contadores
    int placarJ1, placarJ2;                   // acumuladores de placar

    pthread_mutex_init(&mutex, NULL); // inicializa o mutex
    pthread_attr_t attr;              // declara variável attr para usar os valores padrão

    // define attribute
    pthread_attr_init(&attr);
    // pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    pthread_t threadJ1, threadJ2; // define as treads para cada jogador

    system("clear || cls"); // Limpa a tela do console

    // tela de abertura
    printf("Bem-vindo ao jogo de cartas\n\n");
    printf("##### ##### ##### #####\n");
    printf("#   # #   # #   # #   #\n");
    printf("# J # # Q # # K # # A #\n");
    printf("#   # #   # #   # #   #\n");
    printf("##### ##### ##### #####\n\n");

    printf("Pressione 'ENTER' para continuar.\n");
    while (getchar() != '\n')
        ; // lê e descarta os caracteres do buffer até encontrar '\n'

    printf("JOGADOR 1:\n\n");
    printf("Escolha a ordem em que você jogará suas cartas:\n");
    fgets(linha, 100, stdin); // salva a linha digitada

    letra = strtok(linha, " \n"); // separa a string utilizando "espaço" ou "nova linha" como delimitador.
    i = 0;                        // contador para a função while
    while (letra != NULL && i < 4)
    {                                            // loop para cada quebra de string enquanto i < 4
        sscanf(letra, "%c", &caractere);         // associa a quebra a um caractere
        cartasJ1[i] = toupper(caractere);        // função para converter os caracteres em maiúsculas
        intCartasJ1[i] = charToInt(cartasJ1[i]); // atribui um valor inteiro para cada carta
        i++;                                     // incrementa contador
        letra = strtok(NULL, " \n");             // continua o processo de quebra de linha
    }

    // apresenta na tela a escolha do jogador
    printf("\nA ordem das cartas escolhidas foram: \n");
    printf("##### ##### ##### #####\n");
    printf("#   # #   # #   # #   #\n");
    for (j = 0; j < i; j++)
    {
        printf("# %c # ", cartasJ1[j]);
    }
    printf("\n#   # #   # #   # #   #\n");
    printf("##### ##### ##### #####\n\n");

    printf("Pressione 'ENTER' para continuar.\n");
    while (getchar() != '\n')
        ; // lê e descarta os caracteres do buffer até encontrar '\n'

    system("clear || cls"); // Limpa a tela do console

    // repete o processo para o jogador 2
    printf("JOGADOR 2:\n\n");
    printf("Escolha a ordem em que você jogará suas cartas:\n");
    fgets(linha, 100, stdin);
    letra = strtok(linha, " \n");
    i = 0;
    while (letra != NULL && i < 4)
    {
        sscanf(letra, "%c", &caractere);
        cartasJ2[i] = toupper(caractere);
        intCartasJ2[i] = charToInt(cartasJ2[i]);
        i++;
        letra = strtok(NULL, " \n");
    }

    printf("\nA ordem das cartas escolhidas foram: \n");
    printf("##### ##### ##### #####\n");
    printf("#   # #   # #   # #   #\n");
    for (j = 0; j < i; j++)
    {
        printf("# %c # ", cartasJ2[j]);
    }
    printf("\n#   # #   # #   # #   #\n");
    printf("##### ##### ##### #####\n\n");

    printf("Pressione 'ENTER' para inciar o jogo!\n"); // inicia a apuração dos resultados

    // define placar inicial
    placarJ1 = 0;
    placarJ2 = 0;
    while (getchar() != '\n')
        ;                   // lê e descarta os caracteres do buffer até encontrar '\n'
    system("clear || cls"); // Limpa a tela do console

    rodada = 0;        // contador de rodadas
    int arg = rodada;  // definição do argumento das funções threads
    while (rodada < 4) // incia as rodadas de apuração
    {
        // inicializa as threads
        pthread_create(&threadJ1, &attr, threadBody1, &arg);
        pthread_create(&threadJ2, &attr, threadBody2, &arg);
        sleep(1); // faz a thread principal aguardar a atualização das variáveis comparativas

        // imprime na tela a escolha dos jogadores
        printf("Rodada %d:\n\n", rodada + 1);
        printf("JOGADOR 1 | JOGADOR 2\n");
        printf("  #####       #####\n");
        printf("  #   #       #   #\n");
        printf("  # %c #   X   # %c #\n", cartasJ1[rodada], cartasJ2[rodada]);
        printf("  #   #       #   #\n");
        printf("  #####       #####\n\n");

        if (comparadorPrioritario[0] >= comparadorSecundario[0])
        {                                                                        // lógica de prioridade
            if (comparadorPrioritario[1] == 1)                                   // verifica se o vencedor é o jogador 1
                placarJ1 = placarJ1 + intCartasJ1[rodada] + intCartasJ2[rodada]; // acumula placar para jogador 1
            else
                placarJ2 = placarJ2 + intCartasJ1[rodada] + intCartasJ2[rodada]; // ou acumula placar para jogador 2
        }
        else
        {                                                                        // se comparadorSecundario maior
            if (comparadorSecundario[1] == 2)                                    // verifica se o vencedor é o jogador 2
                placarJ2 = placarJ2 + intCartasJ1[rodada] + intCartasJ2[rodada]; // acumula placar para o jogador 2
            else
                placarJ1 = placarJ1 + intCartasJ1[rodada] + intCartasJ2[rodada]; // ou acumula placar para o jogador 1
        }

        /* teste
        printf("intCartasJ1[rodada]: %d\n", intCartasJ1[rodada]);
        printf("intCartasJ2[rodada]: %d\n", intCartasJ2[rodada]);
        printf("comparadorPrioritário %d %d: \n", comparadorPrioritario[0], comparadorPrioritario[1]);
        printf("comparadorSecundário %d %d: \n", comparadorSecundario[0], comparadorSecundario[1]); */

        // imprime o placar parcial do jogo
        printf("Placar ao final da rodada %d:\n", rodada + 1);
        printf("Jogador 1: %d pontos\n", placarJ1);
        printf("Jogador 2: %d pontos\n\n", placarJ2);
        comparadorPrioritario[0] = -1; // redefine o valor do contadorPrioritário para o defaut
        rodada++;
        if (rodada == 4)
        {
            // imprime resultado final
            printf("\nO vencedor foi o Jogador ");
            if (placarJ1 > placarJ2)
                printf("1");
            if (placarJ2 > placarJ1)
                printf("2");
            if (placarJ1 == placarJ2)
                printf("%d", comparadorPrioritario[1]);
            printf("! Parabéns!!!!\n");
        }
        printf("\nPressione 'ENTER' para continuar...\n");

        while (getchar() != '\n')
            ;                   // lê e descarta os caracteres do buffer até encontrar '\n'
        system("clear || cls"); // Limpa a tela do console
    }
    pthread_exit(NULL); // destrói a thread principal
}