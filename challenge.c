#include <stdio.h>

///Utils
void jumpLine() { // Pula a linha
    printf("\n");
}

void clearScreen() { // Limpa a tela
    system("cls");
}

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

    //Menu bottom
    buildMenuBottomLine();

    // Pula a linha
    jumpLine();

    printf("\tEscolha uma opcao: ");
    scanf("%d", &change);
}
main() {
    menu();
}
