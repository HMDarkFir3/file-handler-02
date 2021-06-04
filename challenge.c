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

int searchName() {
    // Limpa tela
    clearScreen();

    // Declaração de struct
    struct types types;

    FILE *f;

    char searchedName[99];
    int i, j;

    printf("\tProcurar produto pelo nome: ");
    scanf("%s", &searchedName);

    f = fopen("product.txt", "r");

    for(i = 0; i < 3; i++) {
        fread(&types.name, sizeof(types.name), 1, f);
        fread(&types.quantity, sizeof(types.quantity), 1, f);
        fread(&types.price, sizeof(types.price), 1, f);
        fread(&types.month, sizeof(types.month), 1, f);
        fread(&types.year, sizeof(types.year), 1, f);

        for(j = 0; types.name[j] != '\0'; j++) {
            if(searchedName[j] != types.name[j]) {
                break;
            }
        }

        if(searchedName[j] == '\0' && types.name[j] == '\0') {
            clearScreen();

            printf("\tNome procurado: \n");
            printf("\t%s: %.2f unidade(s)\n", types.name, types.quantity);
            printf("\tValor: R$ %.2f\n", types.price);

            if(types.month > 9) {
                printf("\tValidade: %d/%d\n", types.month, types.year);
            } else {
                printf("\tValidade: 0%d/%d\n", types.month, types.year);
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

    int i, j = i;


    FILE *f;

    f = fopen("product.txt", "w");

    int k;

    printf("\tQuantos produtos deseja adicionar: ");
    scanf("%d", &k);

    clearScreen();

    // Declaração de struct
    struct types types[k];

    for(i < 0; i < k + j; i++) {
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

        fwrite(&types[i].name, sizeof(types[i].name), 1, f);
        fwrite(&types[i].quantity, sizeof(types[i].quantity), 1, f);
        fwrite(&types[i].price, sizeof(types[i].price), 1, f);
        fwrite(&types[i].month, sizeof(types[i].month), 1, f);
        fwrite(&types[i].year, sizeof(types[i].year), 1, f);

        jumpLine();
    }

    fclose(f);

    clearScreen();
    menu();
}

void dataList() {
    // Limpa tela
    clearScreen();

    // Declaração de struct
    struct types types[99];

    FILE *f;

    f = fopen("product.txt", "r");

    if(f == NULL) {
        clearScreen();
        printf(YEL "\tATENCAO: Nenhum arquivo encontrado." RESET);
        Sleep(1500);

        clearScreen();
        printf(BLU "\tRedirecionando para entrada de dados." RESET);
        Sleep(1500);

        dataEntries();
    }

    printf("\tProduto(s):\n");

    for(int i = 0; i < 99; i++) {
        fread(&types[i].name, sizeof(types[i].name), 1, f);
        fread(&types[i].quantity, sizeof(types[i].quantity), 1, f);
        fread(&types[i].price, sizeof(types[i].price), 1, f);
        fread(&types[i].month, sizeof(types[i].month), 1, f);
        fread(&types[i].year, sizeof(types[i].year), 1, f);

        if(types[i].name && types[i].quantity && types[i].price) {
            jumpLine();

            printf("\t%s: %.2f\n", types[i].name, types[i].quantity);
            printf("\tValor: R$ %.2f\n", types[i].price);

            if(types[i].month > 9) {
                printf("\tValidade: %d/%d\n", types[i].month, types[i].year);
            } else {
                printf("\tValidade: 0%d/%d\n", types[i].month, types[i].year);
            }
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
            dataEntries(); //Entrada de dados
            break;
        }

        case 2: {
            dataList(); //Listar dados
            break;
        }

        case 3: {
            break;
        }

        case 4: {
            dataSearchName();
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
