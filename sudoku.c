#include <stdio.h>

#define N 9

void printsudoku(int *ptr);
void scansudoku(int *);
int solvesudoku(int arr[N][N]);
int findEmptyLocation(int arr[N][N], int *, int *);
int the_rule_checker(int arr[N][N], int, int, int);


int main()
{
    int check = 0;
    do
    {

        int arr[N][N] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0}};
        printsudoku(&arr[0][0]);
        scansudoku(&arr[0][0]);
        int solved = solvesudoku(arr);
        printf("\e[1;1H\e[2J");
        if (solved == 1)
        {
            printsudoku(&arr[0][0]);
            check = 0;
        }
        else
        {
            printf("wrong inputs...try again");
            check = 1;
        }
    } while (check == 1);

    return 0;
}

void printsudoku(int *ptr)
{
    printf("\e[1;1H\e[2J");
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            printf("%d\t", ptr[(row) * N + (col)]);
        }
        printf("\n");
    }
}

void scansudoku(int *ptr)
{
    int check, colm, roww;
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            do
            {
                check = 1;
                printf("Type the given number in position --> row:%d column:%d\n------------------------------------>", (row + 1), (col + 1));
                scanf("%d", &ptr[row * N + col]);
                if (ptr[row * N + col] < 0 || ptr[row * N + col] > 9)
                {
                    printf("Provide a value between 0 and N...\n");
                    check = 0;
                }
                else
                {
                    for (colm = 0; colm < N; colm++)
                    {
                        if (colm != col && ptr[row * N + col] == ptr[row * N + colm] && ptr[row * N + col] != 0)
                        {
                            printf("Typed the same thing in the same row! Try again...\n");
                            check = 0;
                            break;
                        }
                    }
                    for (roww = 0; roww < N; roww++)
                    {
                        if (roww != row && ptr[row * N + col] == ptr[roww * N + col] && ptr[row * N + col] != 0)
                        {
                            printf("Typed the same thing in the same column! Try again...\n");
                            check = 0;
                            break;
                        }
                    }
                }
            } while (!check);
            printsudoku(ptr);
        }
    }
}
int solvesudoku(int arr[N][N]) {
    int row, col;
    int empty_location = findEmptyLocation(arr, &row, &col);
    if ( empty_location == 0 ) {
        return 1;
    }
    for (int num = 1; num <= 9; num++) {
        if (the_rule_checker(arr, row, col, num)) {
            arr[row][col] = num;
            if (solvesudoku(arr)) {
                return 1;
            }
            arr[row][col] = 0;
        }
    }
    return 0;
}
int findEmptyLocation(int arr[N][N], int *row, int *col) {
    for (*row = 0; *row < N; (*row)++) {
        for (*col = 0; *col < N; (*col)++) {
            if (arr[*row][*col] == 0) {
                return 1;
            }
        }
    }
    return 0;
}
int the_rule_checker(int arr[N][N], int row, int col, int num) {

    for (int x = 0; x < N; x++) {
        if (arr[row][x] == num) {
            return 0;
        }
    }

    for (int x = 0; x < N; x++) {
        if (arr[x][col] == num) {
            return 0;
        }
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr[i + startRow][j + startCol] == num) {
                return 0;
            }
        }
    }

    return 1;
}