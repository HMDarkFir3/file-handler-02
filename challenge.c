#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"

// Strutc
struct types {
    char name[99];
    float quantity;
    float price;

    int month;
    int year;

};

// Utils
void jumpLine() { // Pula a linha
    printf("\n");
}

void clearScreen() { // Limpa a tela
    system("cls");
}

// App
void dataEntries() { // Entrada de dados
    // Limpa tela
    clearScreen();

    struct types types;

    FILE *f;

    f = fopen("product.txt", "w");

    printf("\tDigite o produto: ");
    scanf("%s", &types.name);

    printf("\tDigite a quantidade: ");
    scanf("%.2f", &types.quantity);

    printf("\tDigite a preco: ");
    scanf("%.2f", &types.price);

    printf("\tDigite a mes: ");
    scanf("%d", &types.month);

    printf("\tDigite a ano: ");
    scanf("%d", &types.year);

    char validateDate[5];

    validateDate[5] = types.month + "/" + types.year;

    fwrite(&types.name, sizeof(types.name), 1, f);
    fwrite(&types.quantity, sizeof(types.quantity), 1, f);
    fwrite(&types.price, sizeof(types.price), 1, f);
    fwrite(&validateDate, sizeof(validateDate), 1, f);

    fclose(f);

    clearScreen();
    menu();
}

void quit() { // Sair
    clearScreen();

    for(int i = 3; i > -1; i--) {
        clearScreen();
        printf("\tFechando em %d", i);
        Sleep(1000);
    }

    exit(0);
}

// Menu
void buildMenuTopLine() { // Linha superior do menu
    printf("\t%c", 201);

    for(int i = 0; i < 73; i++) {
        printf("%c", 205);
    }

    printf("%c", 187);

    jumpLine();
}

void buildMenuItem(char str[]) { // Seleção do menu

    int countLetters = 0;

    for(int i = 0; i < 73; i++) {
        if(str[i] == '\0') {
            break;
        } else {
            countLetters++;
        }
    }

    printf("\t%c", 186);
    printf("%s", str);

    while(countLetters < 73) {
        printf("%c", 32);
        countLetters++;
    }

    printf("%c", 186);
}

void buildMenuBottomLine() { // Linha inferior do menu

    printf("\t%c", 200);

    for(int i = 0; i < 73; i++) {
        printf("%c", 205);
    }

    printf("%c", 188);

    jumpLine(); //
}

void menu() { // Menu
    int change;
    // Menu Top
    buildMenuTopLine();

    // Menu Item
    buildMenuItem(" 1 - Entrada de dados");
    jumpLine();
    buildMenuItem(" 2 - Listar todos os produtos");
    jumpLine();
    buildMenuItem(" 3 - Listar produtos por faixa de preço");
    jumpLine();
    buildMenuItem(" 4 - Pesquisar um produto pelo nome completo");
    jumpLine();
    buildMenuItem(" 5 - Pesquisar data de validade (mês/ano)");
    jumpLine();
    buildMenuItem(" 6 - Altera produto pesquisado pelo nome completo");
    jumpLine();
    buildMenuItem(" 7 - Altera quantidade em estoque (entrada e saída) pesquisado pelo nome");
    jumpLine();
    buildMenuItem(" 8 - Altera preço de um produto pesquisado pelo nome completo");
    jumpLine();
    buildMenuItem(" 9 - Excluir produto");
    jumpLine();
    buildMenuItem(" 10 - Sair");
    jumpLine();

    // Menu bottom
    buildMenuBottomLine();

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
            break;
        }

        case 3: {
            break;
        }

        case 4: {
            break;
        }

        case 5: {
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
            main();
        }

    }
}

main() {
    // Menu
    menu();
}
