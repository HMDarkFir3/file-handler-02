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

// Strutc
struct types {
    char name[99];
    float quantity;
    float price;

    int month;
    int year;
};

// Util
void clearScreen() { // Limpa tela
    system("cls");
}

void jumpLine() { // Pula linha
    printf("\n");
}

int searchName() { // Pesquisa o nome
    // Limpa tela
    clearScreen();

    // Declaracao de struct
    struct types types[4];

    FILE *f;

    char searchedName[99];
    int i, j;

    printf("\tProcurar produto pelo nome: ");
    scanf("%s", &searchedName);

    f = fopen("product.txt", "r");

    for(i = 0; i < 4; i++) {
        fread(&types[i].name, sizeof(types[i].name), 1, f);
        fread(&types[i].quantity, sizeof(types[i].quantity), 1, f);
        fread(&types[i].price, sizeof(types[i].price), 1, f);
        fread(&types[i].month, sizeof(types[i].month), 1, f);
        fread(&types[i].year, sizeof(types[i].year), 1, f);

        for(j = 0; types[i].name[j] != '\0'; j++) {
            if(searchedName[j] != types[i].name[j]) {
                break;
            }
        }

        if(searchedName[j] == '\0' && types[i].name[j] == '\0') {
            clearScreen();

            printf("\tProduto %d: %s\n", i + 1, types[i].name);
            printf("\tQuantidade: %.2f\n", types[i].quantity);
            printf("\tValor: R$ %.2f\n", types[i].price);

            if(types[i].month > 9) {
                printf("\tValidade: %d/%d\n", types[i].month, types[i].year);
            } else {
                printf("\tValidade: 0%d/%d\n", types[i].month, types[i].year);
            }


            jumpLine();

            fclose(f);
            return i;
        }
    }

    fclose(f);
    return -1;
}

// App
void dataEntries() { // Entrada de dados
    // Limpa tela
    clearScreen();

    int i, j;

    FILE *f;

    f = fopen("product.txt", "w");

    clearScreen();

    clearScreen();

    // Declaracao de struct
    struct types types[4];

    if(types[0].name[0] == NULL) {
        for(i = 0; i < 4; i++) {
            for(j = 0; j < 4; j++) {
                types[i].name[j] == NULL;
            }
        }
    }

    for(i = 0; i < 4; i++) {
        printf("\tDigite o %d produto: ", i + 1);
        scanf("%s", &types[i].name);

        printf("\tDigite a quantidade: ");
        scanf("%f", &types[i].quantity);

        printf("\tDigite a preco: ");
        scanf("%f", &types[i].price);

     
        printf("\tDigite a mes: ");
        scanf("%d", &types[i].month);

        printf("\tDigite a ano: ");
        scanf("%d", &types[i].year);

        jumpLine();
    }

    for(i = 0; i < 4; i++) {
        fwrite(&types[i].name, sizeof(types[i].name), 1, f);
        fwrite(&types[i].quantity, sizeof(types[i].quantity), 1, f);
        fwrite(&types[i].price, sizeof(types[i].price), 1, f);
        fwrite(&types[i].month, sizeof(types[i].month), 1, f);
        fwrite(&types[i].year, sizeof(types[i].year), 1, f);
    }

    jumpLine();

    fclose(f);

    clearScreen();
    menu();
}

void dataList() { // Lista os dados
    // Limpa tela
    clearScreen();

    int i, j;

    // Declara��o de struct
    struct types types[4];

    FILE *f;

    f = fopen("product.txt", "r");

    if(f == NULL) {
        clearScreen();
        printf(YEL "\tATENCAO: Nenhum arquivo encontrado." RESET);
        Sleep(1500);

        clearScreen();
        menu();
    }

    if(types[0].name[0] == NULL) {
        for(i = 0; i < 4; i++) {
            for(j = 0; j < 4; j++) {
                types[i].name[j] == NULL;
            }
        }
    }

    for(int i = 0; i < 4; i++) {
        fread(&types[i].name, sizeof(types[i].name), 1, f);
        fread(&types[i].quantity, sizeof(types[i].quantity), 1, f);
        fread(&types[i].price, sizeof(types[i].price), 1, f);
        fread(&types[i].month, sizeof(types[i].month), 1, f);
        fread(&types[i].year, sizeof(types[i].year), 1, f);
    }

    for(int i = 0; i < 4; i++) {
        if(types[i].name[0] == NULL) {
            break;
        } else {
            printf("\tProduto %d: %s\n", i + 1, types[i].name);
            printf("\tQuantidade: %.2f\n", types[i].quantity);
            printf("\tValor: R$ %.2f\n", types[i].price);

            if(types[i].month > 9) {
                printf("\tValidade: %d/%d\n", types[i].month, types[i].year);
            } else {
                printf("\tValidade: 0%d/%d\n", types[i].month, types[i].year);
            }

             jumpLine();
        }
    }

    jumpLine();

    fclose(f);

    printf("\tPressione qualquer tecla para continuar...");
    getch();

    clearScreen();

    jumpLine();
    menu();

}

void dataListPriceRange() { // Lista os dados pela faixa de preco
    // Limpa tela
    clearScreen();

    // Declaracao de struct
    struct types types[4];

    FILE *f;

    float searchedPriceRange1 = 0;
    float searchedPriceRange2 = 0;
    int i, j;

    printf("\tProcurar produto pela faixa de preco 1: ");
    scanf("%f", &searchedPriceRange1);

    printf("\tProcurar produto pela faixa de preco 2: ");
    scanf("%f", &searchedPriceRange2);

    f = fopen("product.txt", "r");

    clearScreen();

    printf("\tFaixa de preco: R$ %.2f - R$ %.2f\n\n", searchedPriceRange1, searchedPriceRange2);

    for(i = 0; i < 4; i++) {
        fread(&types[i].name, sizeof(types[i].name), 1, f);
        fread(&types[i].quantity, sizeof(types[i].quantity), 1, f);
        fread(&types[i].price, sizeof(types[i].price), 1, f);
        fread(&types[i].month, sizeof(types[i].month), 1, f);
        fread(&types[i].year, sizeof(types[i].year), 1, f);

        if(types[i].price >= searchedPriceRange1 && types[i].price <= searchedPriceRange2) {

            printf("\tProduto %d: %s\n", i + 1, types[i].name);
            printf("\tQuantidade: %.2f\n", types[i].quantity);
            printf("\tValor: R$ %.2f\n", types[i].price);

            if(types[i].month > 9) {
                printf("\tValidade: %d/%d\n", types[i].month, types[i].year);
            } else {
                printf("\tValidade: 0%d/%d\n", types[i].month, types[i].year);
            }


            jumpLine();
        }
    }

    fclose(f);

    printf("\tPressione qualquer tecla para continuar...");
    getch();

    clearScreen();
    menu();
}

void dataSearchName() { // Pesquisar dados por nome
    int change;
    int search;

    search = searchName();

    if(search == -1) {
        clearScreen();
        printf("\tNenhum registro encontrado.\n");
        Sleep(1500);
        clearScreen();
    }

    printf("\tPressione qualquer tecla para continuar...");
    getch();

    clearScreen();
    menu();
}

void dataSearchValidateDate() { // Pesquisar dados pela data de validade
    // Limpa tela
    clearScreen();

    // Declaracao de struct
    struct types types[4];

    FILE *f;

    int i, j;
    int searchedValidateDateMonth;
    int searchedValidateDateYear;

    printf("\tDigite o mes: ");
    scanf("%d", &searchedValidateDateMonth);

    printf("\tDigite o ano: ");
    scanf("%d", &searchedValidateDateYear);

    f = fopen("product.txt", "r");

    clearScreen();

    for(i = 0; i < 4; i++) {
        fread(&types[i].name, sizeof(types[i].name), 1, f);
        fread(&types[i].quantity, sizeof(types[i].quantity), 1, f);
        fread(&types[i].price, sizeof(types[i].price), 1, f);
        fread(&types[i].month, sizeof(types[i].month), 1, f);
        fread(&types[i].year, sizeof(types[i].year), 1, f);

        if(types[i].month == searchedValidateDateMonth && types[i].year == searchedValidateDateYear) {
            printf("\tProduto %d: %s\n", i + 1, types[i].name);
            printf("\tQuantidade: %.2f\n", types[i].quantity);
            printf("\tValor: R$ %.2f\n", types[i].price);

            if(types[i].month > 9) {
                printf("\tValidade: %d/%d\n", types[i].month, types[i].year);
            } else {
                printf("\tValidade: 0%d/%d\n", types[i].month, types[i].year);
            }

            jumpLine();
        }
    }

    fclose(f);
    
    printf("\tPressione qualquer tecla para continuar...");
    getch();

    clearScreen();
    menu();
}

void quit() { // Sair do programa
    clearScreen();

    for(int i = 3; i > -1; i--) {
        clearScreen();
        printf("\tFechando em %d", i);
        Sleep(1000);
    }

    exit(0);
}

// Menu
void menu() {
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
    jumpLine();


    printf("\tEscolha uma opcao: ");
    scanf("%d", &change);

    switch(change) {
        case 1: {
            dataEntries();
            break;
        }

        case 2: {
            dataList();
            break;
        }

        case 3: {
            dataListPriceRange();
            break;
        }

        case 4: {
            dataSearchName();
            break;
        }

        case 5: {
            dataSearchValidateDate();
            break;
        }

        case 6: {
            break;
        }

        case 7: {
            break;
        }

        case 8: {
            break;
        }

        case 9: {
            break;
        }

        case 10: {
            quit();
            break;
        }

        default: {
            clearScreen();
            printf(YEL "\tAtencao: Ocorreu um erro no sistema.\n" RESET);
            printf("\tPor favor, digite um numero de 1 a 10.\n\n");

            printf("\tPressione qualquer tecla ...\n");
            getch();

            clearScreen();
            menu();
        }
    }
}

int main(void) {
    clearScreen();
    menu();
    return 0;
}
