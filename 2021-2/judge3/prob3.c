#include <stdlib.h>
#include <stdio.h>
#define N 8
#define SUM 1
#define REVERT 0

#define TRUE 1
#define FALSE 0

//arrays auxiliares para determinar o prox passo do cavalo
int xMove[N] = {2, 1, -1, -2, -2, -1, 1, 2};
int yMove[N] = {1, 2, 2, 1, -1, -2, -2, -1};

int moves = 0, min_moves = N * N, n_pawns = 0, total_n_pawns;
int pawn_arrived = FALSE;

typedef struct
{
    int pos_i, pos_j;
    int initial_pos_i, initial_pos_j;
    int arrived_top, arrived_bottom;
    int captured;
} pawn;

//tabuleiro
int board[N][N];

//array auxiliar com informações sobre os peões
pawn *pawns;

int hasPawn(int x, int y)
{
    for (int k = 0; k < total_n_pawns; k++)
    {
        pawn item = pawns[k];
        if (item.pos_i == x && item.pos_j == y)
            return TRUE;
    }
    return FALSE;
}

int isSafe(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1) //espaços válidos
           && (hasPawn(x - 1, y) == FALSE);
}

void updatePawns(int i, int j, int type)
{
    int k;
    for (k = 0; k < total_n_pawns; k++)
    {
        pawn item = pawns[k];

        if (item.pos_i == i && item.pos_j == j)
        {
            if (type == SUM)
            {
                n_pawns++;
                item.captured = TRUE;
            }
            else
            {
                n_pawns--;
                item.captured = FALSE;
            }
            pawns[k] = item;
            continue;
        }

        if (item.captured == FALSE)
        {
            if (item.arrived_top && type == REVERT)
            {
                pawn_arrived = TRUE;
                break;
            }
            else if (item.arrived_bottom && type == SUM)
            {
                pawn_arrived = TRUE;
                break;
            }

            if (type == SUM)
            {
                if (item.pos_i == item.initial_pos_i)
                {
                    pawn_arrived = FALSE;
                    item.arrived_top = FALSE;
                }

                item.pos_i++;
                if (item.pos_i == N - 1)
                    item.arrived_bottom = TRUE;
            }
            else
            {
                if (item.pos_i == N - 1 && pawn_arrived)
                {
                    // item.arrived_bottom = TRUE;
                    pawn_arrived = FALSE;
                    // item.arrived_bottom = FALSE;
                }
                else
                {
                    item.pos_i--;
                    item.arrived_bottom = FALSE;
                    pawn_arrived = FALSE;
                }
                if (item.pos_i == item.initial_pos_i)
                {
                    item.arrived_top = TRUE;
                }
            }

            printf("pawn %d to %d\n", k, getPos(item.pos_i, item.pos_j));
            pawns[k] = item;
        }
    }
}

int solveKTUtil(int x, int y)
{
    if (pawn_arrived == TRUE)
        return 0;

    if (n_pawns == total_n_pawns)
        return 1;

    int i;

    for (i = 0; i < N; i++)
    {
        int next_x = x + xMove[i];
        int next_y = y + yMove[i];

        if (!isSafe(next_x, next_y))
            continue;

        board[next_x][next_y] = 1;
        printf("moved to %d\n", getPos(next_x, next_y));
        moves++;
        updatePawns(next_x, next_y, SUM);

        if (solveKTUtil(next_x, next_y) == 1)
        {
            printf("-------------------------found a solution with %d moves\n", moves);
            if (moves < min_moves)
            {
                min_moves = moves;
            }
            // return 1;
            board[next_x][next_y] = -1;
            moves--;
            updatePawns(next_x, next_y, REVERT);
        }
        else
        {
            printf("-------------------------backtracing \n");
            board[next_x][next_y] = -1;
            moves--;
            updatePawns(next_x, next_y, REVERT);

            // x = next_x - xMove[i];
            // y = next_y - yMove[i];
        }
    }

    return 0;
}

getPos(int x, int y)
{
    return (x * N) + (y + 1);
}

int getPosI(int number)
{
    int res = number / 8;
    return number % 8 == 0 ? res - 1 : res;
}

int getPosJ(int number)
{
    int rest = number % 8;
    return rest == 0 ? N - 1 : rest - 1;
}

int main()
{
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            board[x][y] = -1;

    int i, initial_pos;

    scanf("%d", &total_n_pawns);
    pawns = (pawn *)malloc(total_n_pawns * sizeof(pawn));

    for (i = 0; i < total_n_pawns; i++)
    {
        int number;
        scanf("%d", &number);

        pawn item;
        item.pos_i = getPosI(number);
        item.pos_j = getPosJ(number);

        item.initial_pos_i = item.pos_i;
        item.initial_pos_j = item.pos_j;

        item.arrived_top = item.pos_i == 0 ? TRUE : FALSE;
        item.arrived_bottom = item.pos_i == N - 1 ? TRUE : FALSE;
        item.captured = FALSE;

        pawns[i] = item;
    }

    scanf("%d", &initial_pos);
    int initial_pos_i = getPosI(initial_pos);
    int initial_pos_j = getPosJ(initial_pos);

    board[initial_pos_i][initial_pos_j] = 0;

    solveKTUtil(initial_pos_i, initial_pos_j);

    if (min_moves == N * N)
    {
        printf("impossible");
    }
    else
        printf("%d", min_moves);

    return 1;
}
