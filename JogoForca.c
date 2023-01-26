//Curso Alura: C: avan‡ando na linguagem
//Janeiro de 2023

//incluindo bibliotecas
#include <stdio.h>
#include <string.h>
#include "arquivoForca.h"
#include <time.h>
#include <stdlib.h>

//variaveis globais
char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;

int letraexiste(char letra) {
    for(int j = 0; j < strlen(palavrasecreta); j++) {
        if(letra == palavrasecreta[j]) {
            return 1;
        }
    }
    return 0;
}

int chuteserrados() {
    int erros = 0;

    for(int i = 0; i < chutesdados; i++) {

        if(!letraexiste(chutes[i])) {
            erros++;
        }
    }

    return erros;
}

int enforcou() {
    return chuteserrados() >= 5;
}

int ganhou(){
  for (int i = 0; i < strlen(palavrasecreta); i++) {
    if (!jaChutou(palavrasecreta[i])) {
      return 0;
    }
  }
  return 1;
}

void abertura(){
    printf("******************************\n");
    printf("*        Jogo de forca       *\n");
    printf("******************************\n\n");
}

void chuta(){
  //captura um novo chute
  char chute;
  printf("\n-> Qual letra? (Em maiusculo): ");
  scanf(" %c", &chute);  //espa‡o ‚ ignorar o enter pq ele pode ser o char digitado
  printf("\n");

  if(letraexiste(chute)) {
        printf("Vocˆ acertou: a palavra tem a letra %c\n\n",chute);
    } else {
        printf("\nVocˆ errou: a palavra NÇO tem a letra %c\n\n", chute);
    }

  chutes[chutesdados] = chute;
  chutesdados++;
}

int jaChutou(char letra){
  int achou = 0;
  //printf("Estou vendo a letra secreta %c\n", palavrasecreta[i] );
  //letra foi chutada?
  for (int j = 0; j < chutesdados; j++) { //se o chute na posicao tal ‚ igual a palavra.
    //printf("-> chute %c\n", chutes[j]  );
    if(chutes[j] == letra){
      //printf("------> chut correct\n");
      achou = 1; //encontrar a letra dentro do array
      break;
    }
  }
  return achou;
}

void desenhaforca(){

  int erros = chuteserrados();

    printf("  _______       \n");
    printf(" |/      |      \n"); //ifs ternario
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

  //imprime a palavra secreta
  for (int i = 0; i < strlen(palavrasecreta); i++) { //palavrasecreta na posicao i... tamanho da palavra

    if(jaChutou(palavrasecreta[i])) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }

    }
    printf("\n");
}

void escolhepalavra(){
  FILE* f;
  f = fopen("palavrasJogo.txt", "r");//devolve um ponteiro de arquivo
  if(f == 0){
    printf("Desculpe, banco de dados nao disponivel\n");
    exit(1); //falha
  }

  int qtdpalavras;
  fscanf(f, "%d", &qtdpalavras);

  srand(time(0));
  int randomico = rand() %qtdpalavras;

  for (int i = 0; i <= randomico; i++) {
    fscanf(f, "%s", palavrasecreta);
  }

  fclose(f);
}

void adicionapalavra(){
  char resposta;

  printf("Vocˆ deseja adicionar uma nova palavra no jogo? (S/N)");
  scanf(" %c", &resposta );

  if (resposta == 'S') {
    char novapalavra[TAMANHO_PALAVRA];
    printf("Qual a nova palavra? (Digite em letras maiusculas)\n");
    scanf("%s", novapalavra);

    //colocando no arquivo
    FILE* f;
    f = fopen("palavrasJogo.txt", "r+"); //ler e escrever
    if(f == 0){
      printf("Desculpe, banco de dados nao disponivel\n");
      exit(1); //falha
    }

    int qtdpalavras;
    fscanf(f, "%d", &qtdpalavras);
    qtdpalavras++;

    //posiciona a cabe‡a de leitura
    fseek(f, 0, SEEK_SET); //aponta para o come‡o do arquivo
    fprintf(f, "%d", qtdpalavras);

    fseek(f,0,SEEK_END); //posiciona no fim do arquivo
    fprintf(f, "\n%s", novapalavra);

    fclose(f);


  }

}


int main(){

  escolhepalavra();
  abertura();

  do{ //tem que ser executado ao menos uma vez
    desenhaforca();
    chuta();//captura um novo chute
  } while(!ganhou() && !enforcou()); // ! = nega um booleano (inverte)

  if(ganhou()){
    printf("\nParab‚ns, vocˆ ganhou!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");


  }else{
    printf("\nPuxa, vocˆ foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavrasecreta);

        printf("    _______________         \n");
        printf("   /               \\       \n");
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");

  }

  adicionapalavra();

}
