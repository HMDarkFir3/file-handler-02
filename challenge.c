#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"

void menu();

// Struct
struct types {
  char name[20];
  float quantity;
  float price;

  int month;
  int year;
};

// Util
void clearScreen() { // Limpa tela
    system("cls"); 
}

int searchName() { // Pesquisa o nome
  // Declaracao do struct
  struct types types;

  // Declaracao do struct de ponteiro
  struct types *l;

  // Atribuicao do ponteiro
  l = &types;

  // Variaveis
  char searchedName[20];
  int i = 0, j;

  // Declarando o arquivo
  FILE *f;

  // Limpa tela
  clearScreen();

  // Nome que ira ser pesquisado
  printf("\tProcurar produto pelo nome: ");
  scanf("%s", &searchedName);

  // Abre o arquivo product.txt
  f = fopen("product.txt", "r");

  // Verificando o nome pesquisado e comparando com os dados inseridos
  for(;;i++) {
    fread(&(*l), sizeof(struct types), 1, f);

    for(j = 0; (*l).name[j] != '\0'; j++) {
      if(searchedName[j] != (*l).name[j]) {
        break;
      }
    }

    if(searchedName[j] == '\0' && (*l).name[j] == '\0') {
      // Limpa tela
      clearScreen();

      // Exibindo os valores encontrados
      printf("\tProduto: %s\n", (*l).name);

      if((*l).quantity < 0) {
        printf("\tQuantidade: 0\n", (*l).quantity);
      } else {
        printf("\tQuantidade: %.2f\n", (*l).quantity);
      }

      printf("\tValor: R$ %.2f\n", (*l).price);

      if((*l).month > 9) {
        printf("\tValidade: %d/%d\n", (*l).month, (*l).year);
      } else {
        printf("\tValidade: 0%d/%d\n", (*l).month, (*l).year);
      }

      // Pula linha
      printf("\n");

      // Fecha o arquivo product.txt
      fclose(f);

      return i;
    }
  }

  // Fecha o arquivo product.txt
  fclose(f);

  return -1;
}

// App
void dataEntries(struct types *p) { // Entrada de dados
  // Variaveis
  int i;

  int a;

  // Declarando o arquivo
  FILE *f;

  // Limpa tela
  clearScreen();

  // Abre o arquivo product.txt
  f = fopen("product.txt", "a");

  a = fread(&(*p), sizeof(struct types), 1, f);

  // Valores do struct ficando NULL
  if((*p).name[0] == NULL) {
    for(;;) {
      for(i = 0; i < 20; i++) {
        (*p).name[i] == NULL;

        if(a == 0) {
          break;
        }
      }
    }
  }

  // Entrada de dados
  printf("\tDigite o produto: ");
  scanf("%s", &(*p).name);

  printf("\tDigite a quantidade: ");
  scanf("%f", &(*p).quantity);

  printf("\tDigite a preco: ");
  scanf("%f", &(*p).price);

  printf("\tDigite o mes: ");
  scanf("%d", &(*p).month);

  printf("\tDigite o ano: ");
  scanf("%d", &(*p).year);

  // Dados entrando no arquivo product.txt
  fwrite(&(*p), sizeof(struct types), 1, f);

  // Pula linha
  printf("\n");
  
  // Fecha o arquivo product.txt
  fclose(f);

  // Limpa tela
  clearScreen();

  // Chamada do menu
  menu(&p);
}

void dataList(struct types *p) { // Lista os dados
  // Variaveis
  int i, j;
  int error = 0;
  int a;

  // Declarando o arquivo
  FILE *f;

  // Limpa tela
  clearScreen();

  // Abre o arquivo product.txt
  f = fopen("product.txt", "r");

  // Verificando se existe o arquivo product.txt
  if(f == NULL) {
    clearScreen();
    printf(YEL "\tATENCAO: Nenhum arquivo encontrado." RESET);
    Sleep(1500);

    clearScreen();
    menu(&p);
  }

  // Verificando se o struct esta NULL
  if((*p).name[0] == NULL) {
    for(i = 0; i < 20; i++) {
      for(j = 0; j < 20; j++) {
        (*p).name[j] == NULL;
      }
    }
  }

  // Lendo os dados
  for(;;) {
    a = fread(&(*p), sizeof(struct types), 1, f);
    
    if(a == 0) {
      break;
    }

    //Verificando se os dados estao NULL
    if((*p).name[0] == NULL) {
      error++;
      break;
    } else if(
      (*p).name && 
      (*p).quantity && 
      (*p).price && 
      (*p).month && 
      (*p).year
    ) {
      // Exibindo os dados
      printf("\tProduto: %s\n", (*p).name);

      if((*p).quantity < 0) {
        printf("\tQuantidade: 0\n", (*p).quantity);
      } else {
        printf("\tQuantidade: %.2f\n", (*p).quantity);
      }

      printf("\tValor: R$ %.2f\n", (*p).price);

      // Verificando se o mes tem 1 digito
      if((*p).month > 9) {
        printf("\tValidade: %d/%d\n", (*p).month, (*p).year);
      } else {
        printf("\tValidade: 0%d/%d\n", (*p).month, (*p).year);
      }

      // Pula linha
      printf("\n");
    }
  }

  // Fecha o arquivo product.txt
  fclose(f);

  // Verificando se existe algum registro
  if(error == 4) {
    printf("\tNenhum registro encontrado.\n");
  }

  // Pula linha
  printf("\n");

  // Pausando a aplicacao
  printf("\tPressione qualquer tecla para continuar...");
  getch();

  // Limpa tela
  clearScreen();

  // Chamada do menu
  menu(&p);
}

void dataListPriceRange(struct types *p) { // Lista os dados pela faixa de preco
  // Variaveis
  float searchedPriceRange1 = 0;
  float searchedPriceRange2 = 0;
  int error = 0;
  int a;

  // Declarando o arquivo
  FILE *f;

  // Limpa tela
  clearScreen();

  // Entrada de dados
  printf("\tProcurar produto pela faixa de preco 1: ");
  scanf("%f", &searchedPriceRange1);

  printf("\tProcurar produto pela faixa de preco 2: ");
  scanf("%f", &searchedPriceRange2);

  // Abre o arquivo product.txt
  f = fopen("product.txt", "r");

  // Limpa tela
  clearScreen();

  // Exibindo a faixa de preco que o usuaria digitou
  printf("\tFaixa de preco: R$ %.2f - R$ %.2f\n\n", searchedPriceRange1, searchedPriceRange2);

  for(;;) {
    // Lendo os dados
    a = fread(&(*p), sizeof(struct types), 1, f);

    if(a == 0) {
      break;
    }

    // Exibindo os dados apos verificacao da faixa de preco
    if((*p).price >= searchedPriceRange1 && (*p).price <= searchedPriceRange2) {

      if(((*p).name && 
        (*p).quantity && 
        (*p).price && 
        (*p).month && 
        (*p).year)
        ) {
        printf("\tProduto: %s\n", (*p).name);
        printf("\tQuantidade: %.2f\n", (*p).quantity);
        printf("\tValor: R$ %.2f\n", (*p).price);

        // Verificando se o mes tem 1 digito
        if((*p).month > 9) {
          printf("\tValidade: %d/%d\n", (*p).month, (*p).year);
        } else {
          printf("\tValidade: 0%d/%d\n", (*p).month, (*p).year);
        }
      }


      // Pula linha
      printf("\n");

    } else {
      error++;
    }
  }

  // Fecha o arquivo product.txt
  fclose(f);

  // Verificando se existe algum registro
  if(error == 4) {
    printf("\tNenhum registro encontrado.\n");
  }

  // Pula linha
  printf("\n");

  // Pausando a aplicacao
  printf("\tPressione qualquer tecla para continuar...");
  getch();

  // Limpa tela
  clearScreen();

  // Chamada do menu
  menu(&p);
}

void dataSearchName(struct types *p) { // Pesquisar dados por nome
  // Variaveis
  int change;
  int search;

  // Chamada da funcao
  search = searchName(&p);

  // Verificando se existe algum registro
  if(search == -1) {
    clearScreen();
    printf("\tNenhum registro encontrado.\n");
  }

  printf("\n");

  // Pausando a aplicacao
  printf("\tPressione qualquer tecla para continuar...");
  getch();

  // Limpa tela
  clearScreen();

  // Chamada do menu
  menu(&p);
}

void dataSearchValidateDate(struct types *p) { // Pesquisar dados pela data de validade
  // Variaveis
  int searchedValidateDateMonth;
  int searchedValidateDateYear;
  int i, j;
  int error = 0;
  int a;

  // Declarando o arquivo
  FILE *f;

  // Limpa tela
  clearScreen();

  // Entrada de dados
  printf("\tDigite o mes: ");
  scanf("%d", &searchedValidateDateMonth);

  printf("\tDigite o ano: ");
  scanf("%d", &searchedValidateDateYear);

  // Abre o arquivo product.txt
  f = fopen("product.txt", "r");

  // Limpa tela
  clearScreen();

  for(;;) {
    // Lendo os dados
     a = fread(&(*p), sizeof(struct types), 1, f);

     if(a == 0) {
       break;
     }

    // Exibindo os dados apos verificacao da validade do produto
    if((*p).month == searchedValidateDateMonth && (*p).year == searchedValidateDateYear) {
      if(((*p).name && 
        (*p).quantity && 
        (*p).price && 
        (*p).month && 
        (*p).year)
        ) {
        printf("\tProduto: %s\n", (*p).name);
        printf("\tQuantidade: %.2f\n", (*p).quantity);
        printf("\tValor: R$ %.2f\n", (*p).price);

        // Verificando se o mes tem 1 digito
        if((*p).month > 9) {
          printf("\tValidade: %d/%d\n", (*p).month, (*p).year);
        } else {
          printf("\tValidade: 0%d/%d\n", (*p).month, (*p).year);
        }
      }

      // Pula linha
      printf("\n");

    } else {
      error++;
    }
  }

  // Fecha o arquivo product.txt
  fclose(f);

  // Verificando se existe algum registro
  if(error == 4) {
    printf("\tNenhum registro encontrado.\n");
  }

  // Pula linha
  printf("\n");

  // Pausando a aplicacao
  printf("\tPressione qualquer tecla para continuar...");
  getch();

  // Limpa tela
  clearScreen();

  // Chamada do menu
  menu(&p);
}

void dataEditName(struct types *p) {  // Alterar nome do produto
  // Variaveis
  int n_reg;
  int a;

  // Declarando o arquivo
  FILE *f;

  // Limpa tela
  clearScreen();

  // Chamada da funcao
  n_reg = searchName(&p);

  // Verificando se existe algum registro
  if(n_reg == -1) {
    clearScreen();
    printf("\tNenhum registro encontrado.\n");

    // Pula linha
    printf("\n");

    // Pausando a aplicacao
    printf("\tPressione qualquer tecla para continuar...");
    getch();

    // Limpa tela
    clearScreen();

    // Chamada do menu
    menu(&p);
  }

  // Abre o arquivo product.txt
  f = fopen("product.txt", "r+");

  // Lendo os dados
  for(;;) {
    // Pulando a struct (bytes)
    fseek(f, n_reg * sizeof(struct types), 0);

    a = fread(&(*p), sizeof(struct types), 1, f);

    if(a == 1) {
      break;
    }
  }
  
  // Variaveis
  char aux1[20];
  int aux2;

  // aux1 pegando valor de types.name
  for(int i = 0; i < 20; i++) {
    aux1[i] = (*p).name[i];
  }

  // Alterando produto
  printf("\tAlterar %s ->: ", aux1);
  scanf("%s", &(*p).name);

  // Pulando a struct (bytes)
  fseek(f, n_reg * sizeof(struct types), 0);

  // Inserindo dados alterados
  fwrite(&(*p).name, sizeof((*p).name), 1, f);

  // Fecha o arquivo product.txt
  fclose(f);

  // Limpa tela
  clearScreen();

  printf(GRN "\tProduto alterado(a) com sucesso." RESET);
  Sleep(1500);

  // Limpa tela
  clearScreen();

  // Chamada do menu
  menu(&p);
}

void dataEditQuantity(struct types *p) { // Alterar quantidade do produto
  // Variaveis
  int n_reg;
  int a;

  // Declarando o arquivo
  FILE *f;

  // Limpa tela
  clearScreen();

  // Chamada da funcao
  n_reg = searchName(&p);

  // Verificando se existe algum registro
  if(n_reg == -1) {
    clearScreen();
    printf("\tNenhum registro encontrado.\n");

    // Pula linha
    printf("\n");

    // Pausando a aplicacao
    printf("\tPressione qualquer tecla para continuar...");
    getch();

    // Limpa tela
    clearScreen();

    // Chamada do menu
    menu(&p);
  }

  // Abre o arquivo product.txt
  f = fopen("product.txt", "r+");

  // Lendo os dados
  for(;;) {
    // Pulando a struct (bytes)
    fseek(f, n_reg * sizeof(struct types), 0);

    // Lendo os dados
    a = fread(&(*p), sizeof(struct types), 1, f);

    if(a == 1) {
      break;
    }
  }

  // Variaveis
  float aux;
  float quantity1;

  // aux pegando valor de types.quantity
  aux = (*p).quantity;

  // Alterando produto
  printf("\tAlterar %.2f ->: ", aux);
  scanf("%f", &quantity1);

  // Inserindo o dados no types.quantity
  if(quantity1 >= 0) {
    (*p).quantity = (*p).quantity + quantity1;
  } else if(quantity1 < 0) {
    (*p).quantity = (*p).quantity + quantity1;
  }

  // Volta ao inicio do arquivo
  rewind(f);

  // Pulando a struct (bytes)
  fseek(f, (n_reg * sizeof(struct types)) + sizeof((*p).name), 0);

  // Inserindo dados alterados
  fwrite(&(*p).quantity, sizeof((*p).quantity), 1, f);

  // Fecha o arquivo product.txt
  fclose(f);

  // Limpa tela
  clearScreen();

  printf(GRN "\tQuantidade alterado(a) com sucesso." RESET);
  Sleep(1500);

  // Limpa tela
  clearScreen();

  // Chamada do menu
  menu(&p);
}

void dataEditPrice(struct types *p) { // Alterar preco do produto
  // Variaveis
  int n_reg;
  int a;

  // Declarando o arquivo
  FILE *f;

  // Limpa tela
  clearScreen();

  // Chamada da funcao
  n_reg = searchName(&p);

  // Verificando se existe algum registro
  if(n_reg == -1) {
    clearScreen();
    printf("\tNenhum registro encontrado.\n");

    // Pula linha
    printf("\n");

    // Pausando a aplicacao
    printf("\tPressione qualquer tecla para continuar...");
    getch();

    // Limpa tela
    clearScreen();

    // Chamada do menu
    menu(&p);
  }

  // Abre o arquivo product.txt
  f = fopen("product.txt", "r+");

  // Lendo os dados
  for(;;) {
    // Pulando a struct (bytes)
    fseek(f, n_reg * sizeof(struct types), 0);

    a = fread(&(*p), sizeof(struct types), 1, f);

    if(a == 1) {
      break;
    }
  }

  // Variaveis
  float aux;

  // aux pegando valor de types.price
  aux = (*p).price;

  // Alterando produto
  printf("\tAlterar R$ %.2f ->: ", aux);
  scanf("%f", &(*p).price);

  // Volta ao inicio do arquivo
  rewind(f);

  // Pulando a struct (bytes)
  fseek(f, (n_reg * sizeof(struct types)) + sizeof((*p).name) + sizeof((*p).quantity), 0);

  // Inserindo dados alterados
  fwrite(&(*p).price, sizeof((*p).price), 1, f);

  // Fecha o arquivo product.txt
  fclose(f);

  // Limpa tela
  clearScreen();

  printf(GRN "\tPreco alterado(a) com sucesso." RESET);
  Sleep(1500);

  // Limpa tela
  clearScreen();

  // Chamada do menu
  menu(&p);
}

void dataDelete(struct types *p) { // Deletar produto
  // Variaveis
  int n_reg;
  int a;

  // Declarando o arquivo
  FILE *f;

  // Limpa tela
  clearScreen();

  // Chamada da funcao
  n_reg = searchName(&p);

  // Verificando se existe algum registro
  if(n_reg == -1) {
    clearScreen();
    printf("\tNenhum registro encontrado.\n");

    // Pula linha
    printf("\n");

    // Pausando a aplicacao
    printf("\tPressione qualquer tecla para continuar...");
    getch();

    // Limpa tela
    clearScreen();

    // Chamada do menu
    menu(&p);
  }

  // Abre o arquivo product.txt
  f = fopen("product.txt", "r+");

  /// Lendo os dados
  for(;;) {
    // Pulando a struct (bytes)
    fseek(f, n_reg * sizeof(struct types), 0);

    a = fread(&(*p), sizeof(struct types), 1, f);

    if(a == 1) {
      break;
    }
  }

  // Variaveis
  int aux1;
  int aux2;

  // Tornando valores NULL
  (*p).name[0] = '*';
  aux1 = (*p).quantity;
  aux2 = (*p).price;
  aux1 = NULL;
  aux2 = NULL;
  (*p).quantity = aux1;
  (*p).price = aux2;
  (*p).month = NULL;
  (*p).year = NULL;

  // Pulando a struct (bytes)
  fseek(f, n_reg * sizeof(struct types), 0); 

  // Inserindo dados excluidos
  fwrite(&(*p), sizeof(struct types), 1, f);

  // Fecha o arquivo product.txt
  fclose(f);

  //Limpa tela
  clearScreen();

  printf(GRN "\tProduto excluido(a) com sucesso." RESET);
  Sleep(1500);

  // Limpa tela
  clearScreen();

  // Chamada do menu
  menu(&p);
}

void quit() { // Sair do programa
  // Limpa tela
  clearScreen();

  // Contador do tempo de fechamento do progrma
  for(int i = 3; i > -1; i--) {
    clearScreen();
    printf("\tFechando em %d", i);
    Sleep(1000);
  }

  // Fechando programa
  exit(0);
}

// Menu
void menu(struct types *p) {
  // Variaveis
  int change;

  // Menu Top
  printf("\t|-------------------------------------------------------------------------|\n");

  // Menu Item
  printf("\t| 1 - Entrada de dados                                                    |\n");
  printf("\t| 2 - Listar todos os produtos                                            |\n");
  printf("\t| 3 - Listar produtos por faixa de preco                                  |\n");
  printf("\t| 4 - Pesquisar um produto pelo nome completo                             |\n");
  printf("\t| 5 - Pesquisar data de validade (mes/ano)                                |\n");
  printf("\t| 6 - Altera produto pesquisado pelo nome completo                        |\n");
  printf("\t| 7 - Altera quantidade em estoque (entrada e saida) pesquisado pelo nome |\n");
  printf("\t| 8 - Altera preco de um produto pesquisado pelo nome completo            |\n");
  printf("\t| 9 - Excluir produto                                                     |\n");
  printf("\t| 10 - Sair                                                               |\n");

  // Menu bottom
  printf("\t|-------------------------------------------------------------------------|\n");

  // Pula a linha
  printf("\n");

  // Opcao escolhida do usario
  printf("\tEscolha uma opcao: ");
  scanf("%d", &change);

  // Escolhas
  switch(change) {
    case 1: {
      // Entrada de dados
      dataEntries(&p);
      break;
    }

    case 2: {
      // Lista de dados
      dataList(&p);
      break;
    }

    case 3: {
      // Lista de dados pela faixa de preco
      dataListPriceRange(&p);
      break;
    }

    case 4: {
      // Pesquisa dados pelo nome
      dataSearchName(&p);
      break;
    }

    case 5: {
      // Pesquisa dados pela data de validade
      dataSearchValidateDate(&p);
      break;
    }

    case 6: {
      dataEditName(&p);
      break;
    }

    case 7: {
      dataEditQuantity(&p);
      break;
    }

    case 8: {
      dataEditPrice(&p);
      break;
    }

    case 9: {
      dataDelete(&p);
      break;
    }

    case 10: {
      // Sair do programa
      quit();
      break;
    }

    default: {
      // Limpa tela
      clearScreen();

      // WARNING
      printf(YEL "\tATENCAO: Ocorreu um erro no sistema.\n" RESET);
      printf(YEL "\tPor favor, digite um numero de 1 a 10.\n\n" RESET);

      // Pausando a aplicacao
      printf("\tPressione qualquer tecla ...\n");
      getch();

      // Limpa tela
      clearScreen();

      // Chamada do menu
      menu(&p);
    }
  }
}

int main(void) {
  // Declaracao do struct
  struct types types;

  // Declaracao do struct de ponteiro
  struct types *p;

  // Atribuicao do ponteiro
  p = &types;

  // Limpa tela
  clearScreen();

  // Chamada do menu
  menu(&p);

  return 0;
}
