#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *arquivo;
    FILE *temp;

    int a;
    char nome[50], linha[100], item[50];
    int quantidade, remover;
    int encontrado;
    char b;
inicio:
    printf("================================\n");
    printf(" Controle de Estoque\n");
    printf("================================\n");
    printf("1. Adicionar Item\n");
    printf("2. Remover Item\n");
    printf("3. Listar Estoque\n");
    printf("4. Sair\n");
    printf("Opcao: ");
    scanf("%d", &a);
    if (a != 1 && a != 2 && a != 3 && a != 4) {
        printf("Opcao invalida! Tente novamente.\n");
        goto inicio;
    }
    if (a == 1) {
        arquivo = fopen("estoque.txt", "a");

        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }

        printf("Digite o nome do item: ");
        scanf("%s", nome);

        printf("Digite a quantidade: ");
        scanf("%d", &quantidade);

        if (quantidade <= 0) {
            printf("Quantidade invalida.\n");
            fclose(arquivo);
            return 1;
        }

        fprintf(arquivo, "%s\n", nome);
        fprintf(arquivo, "%d\n", quantidade);

        fclose(arquivo);
        printf("Item adicionado com sucesso!\n");
        printf ("Deseja realizar outra operação? (s/n):");
        scanf("%c", b);
        if (b == 's' || b == 'S'){
            goto inicio;
        } else {
            printf("Obrigado por usar o Controle de Estoques! Ate a proxima.\n");
            return 0;
        }
        
    }
    if (a == 2) {
        encontrado = 0;

        arquivo = fopen("estoque.txt", "r");
        temp = fopen("temp.txt", "w");

        if (arquivo == NULL || temp == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }

        printf("Digite o nome do item: ");
        scanf("%s", item);

        printf("Digite a quantidade a ser removida: ");
        scanf("%d", &remover);

        while (fgets(nome, sizeof(nome), arquivo) != NULL) {
            nome[strcspn(nome, "\n")] = '\0';

            fgets(linha, sizeof(linha), arquivo);
            quantidade = atoi(linha);

            if (strcmp(nome, item) == 0) {
                encontrado = 1;

                if (quantidade < remover) {
                    printf("Estoque insuficiente. Quantidade disponivel: %d\n", quantidade);
                    fprintf(temp, "%s\n%d\n", nome, quantidade);
                } else {
                    quantidade -= remover;

                    if (quantidade == 0) {
                        printf("Item removido do estoque!\n");
                    } else {
                        fprintf(temp, "%s\n%d\n", nome, quantidade);
                        printf("Quantidade atualizada com sucesso!\n");
                    }
                }
            } else {
                fprintf(temp, "%s\n%d\n", nome, quantidade);
            }
        }

        fclose(arquivo);
        fclose(temp);

        remove("estoque.txt");
        rename("temp.txt", "estoque.txt");

        if (!encontrado) {
            printf("Item nao encontrado.\n");
        }
    }
    if (a == 3) {
        arquivo = fopen("estoque.txt", "r");

        if (arquivo == NULL) {
            printf("O estoque está vazio.\n");
            return 0;
        }

        fseek(arquivo, 0, SEEK_END);

        if (ftell(arquivo) == 0) {
            printf("O estoque esta vazio.\n");
            fclose(arquivo);
            return 0;
        } else {

        printf("================================\nEstoque Atual\n================================\n");

        while (fgets(nome, sizeof(nome), arquivo) != NULL) {
            nome[strcspn(nome, "\n")] = '\0';
            fgets(linha, sizeof(linha), arquivo);
            quantidade = atoi(linha);

            printf("Nome:\n%s\n\nQuantidade:\n%d\n", nome, quantidade);
        }
        
        fclose(arquivo);
    
    }}
    if (a == 4) {
        printf("Obrigado por usar o Controle de Estoques! Ate a proxima.\n");
        return 0;
    }
}
