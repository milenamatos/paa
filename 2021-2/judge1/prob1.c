#include <stdio.h>
#include <stdlib.h>

#define QTD_DIAS 30
struct node
{
    int info;
    struct node *next;
};
struct node *last = NULL;

void insere(int data)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    if (last == NULL)
    {
        temp->info = data;
        temp->next = temp;
        last = temp;
    }
    else
    {
        temp->info = data;
        temp->next = last->next;
        last->next = temp;
        last = temp;
    }
}
void update(int data)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp = last->next;
    temp->info = data;
    last = last->next;
}
void viewList()
{
    if (last == NULL)
        printf("\nList is empty\n");
    else
    {
        struct node *temp;
        temp = last;
        printf("ULTIMO: %d\n", temp->info);
        printf("PRIMEIRO: %d\n", temp->next->info);
        printf("SEGUNDO: %d\n", temp->next->next->info);
    }
}
int calcula_media(int soma)
{
    if (soma % QTD_DIAS == 0)
    {
        return (soma / QTD_DIAS);
    }
    return (soma / QTD_DIAS) + 1;
}
int main()
{
    int qtd_inicial, qtd_final;

    scanf("%d", &qtd_inicial);
    scanf("%d", &qtd_final);

    int objetivo = qtd_final - qtd_inicial;
    int total_usuarios = qtd_inicial;
    int i, media = 0;


    for (i = 0; i < QTD_DIAS; i++)
    {
        int qtd_dia;
        scanf("%d", &qtd_dia);
        insere(qtd_dia);

        total_usuarios += qtd_dia;
        if (total_usuarios >= objetivo)
        {
            printf("\n%d", i);
            return 0;
        }
    }

    int soma_usuarios = total_usuarios;
    int total_dias = QTD_DIAS;
    while (total_usuarios < objetivo)
    {
        media = calcula_media(soma_usuarios);
        total_usuarios += media;

        int primeiro = last->next->info;
        soma_usuarios = soma_usuarios + media - primeiro;

        update(media);

        total_dias++;
    }

    printf("\n%d", total_dias);
    return 0;
}