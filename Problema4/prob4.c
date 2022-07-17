#include "stdio.h"
#include "stdlib.h"
#include <string.h>

#define MAX_SIZE 1000

int main()
{
    char *sequencia1 = (char *)malloc(MAX_SIZE * sizeof(char));
    char *sequencia2 = (char *)malloc(MAX_SIZE * sizeof(char));

    scanf("%s", sequencia1);
    scanf("%s", sequencia2);

    int tamanho1 = strlen(sequencia1);
    int tamanho2 = strlen(sequencia2);

    int i = 0, j = 0, k, count = 0;

    while (i < tamanho1 || j < tamanho2)
    {
        if (i >= tamanho1)
        {
            count++;
            break;
        }
        else if (j >= tamanho2)
        {
            count++;
            break;
        }
        else
        {
            int m = 0, n = 0;
            while (m < 4 || n < 4)
            {
                if (i + m >= tamanho1 && j + n < tamanho2)
                {
                    count++;
                    n++;
                }

                else if (j + n >= tamanho2 && i + m < tamanho1)
                {
                    count++;
                    m++;
                }
                else if (sequencia1[i + m] != sequencia2[j + n])
                {
                    count++;

                    if (sequencia1[i + m + 1] == sequencia2[j + n + 1] || tamanho1 == tamanho2)
                    {
                        m++;
                        n++;
                    }
                    else
                    {
                        if (tamanho1 > tamanho2)
                        {
                            m++;
                        }
                        else
                        {
                            n++;
                        }
                    }
                }
                else
                {
                    m++;
                    n++;
                }
            }

            i += 4;
            j += 4;
        }
    }

    printf("%d", count);
}