//In The Name Of GOD
#include<time.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<unistd.h>

#define MAXN 512

struct ZEUS {
    int state;
}rel[MAXN][MAXN];

int main() {
    printf("PLEASE ENTER THE LENGTH OF THE TABLE. (IT SHOULD BE SMALLER THAN 10 IN ORDER TO FIR IN THE CMD. )\n");
    int n = 3, len;  scanf("%d", &len);
    char st[] = "** ", ts[] = "   ";
    int Z = 4 * len + 3;
    char table[MAXN][MAXN][3];
    for (int i  = 0; i < Z; i++) {
        for (int j = 0; j < Z; j++) {
            int w = i % (2 * n - 2), x = j % (4 * n - 4);
            if ((Z - i <= 2) && (Z - j <= 2 || j <= 2) && len % 2) {
                for (int k = 0; k < n; k++)    table[i][j][k] = ts[k];
                continue;
            } else if (!(len % 2) && ((Z - i <= 2 && j <= 2) || (Z - j <= 2 && i <= 2))) {
                for (int k = 0; k < n; k++)    table[i][j][k] = ts[k];
                continue;
            }
            if (w < n) {
                if (w == n - 1) {
                    if (!j) 
                        for (int k = 0; k < n; k++)    table[i][j][k] = st[k];
                    else {
                        if (j < 3 * n - 3) {
                        for (int k = 0; k < n; k++)    table[i][j][k] = ts[k];
                            continue;
                        }
                        int y = j - (2 * n - 2);
                        x = y % (4 * n - 4);
                        if (x >= n - 1 && x <= 2 * n - 2)
                            for (int k = 0; k < n; k++)    table[i][j][k] = st[k];
                        else
                            for (int k = 0; k < n; k++)    table[i][j][k] = ts[k];
                    }
                } else {
                    if (!w) {
                        if (x >= n - 1 && x <= 2 * n - 2)
                            for (int k = 0; k < n; k++)    table[i][j][k] = st[k];
                        else 
                            for (int k = 0; k < n; k++)    table[i][j][k] = ts[k];
                    } else {
                        if (x == n - 1 - w || x == 2 * n - 2 + w)
                            for (int k = 0; k < n; k++)    table[i][j][k] = st[k];
                        else 
                            for (int k = 0; k < n; k++)    table[i][j][k] = ts[k];
                    }
                }
            } else {
                int y = w - (n - 1);
                w = n - 1 - y;
                if (x == n - 1 - w || x == 2 * n - 2 + w)
                    for (int k = 0; k < n; k++)    table[i][j][k] = st[k];
                else 
                    for (int k = 0; k < n; k++)    table[i][j][k] = ts[k];

            }
        }
    }
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    WORD wOldColorAttrs;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    wOldColorAttrs = csbiInfo.wAttributes; 
    for (int j = 0; j < len; j++) 
        for (int i = 0; i < len; i++) {
            int x = 4 * j + 2, y = 4 * i + 1;
            if (j % 2 == 0)
                y += 2;
            else 
                y += 4;
            table[y][x][0] = j + '0', table[y][x][1] = ' ', table[y][x][2] = '0' + len - i - 1;
        }
    SetConsoleTextAttribute ( h, FOREGROUND_BLUE);
    printf("Now it's the primary table, I'm waiting for your order's to initialize the table.\n");
    SetConsoleTextAttribute ( h, FOREGROUND_GREEN);
    for (int i = 0; i < Z; i++) {
        for (int j = 0; j < Z; j++) {
            if (table[i][j][0] >= '0' && table[i][j][0] <= '9') 
                SetConsoleTextAttribute ( h, FOREGROUND_RED | FOREGROUND_GREEN);
            for (int k = 0; k < n; k++) 
                printf("%c", table[i][j][k]);
            if (table[i][j][0] >= '0' && table[i][j][0] <= '9') 
                SetConsoleTextAttribute ( h, FOREGROUND_GREEN);
        }
        printf("\n");
    }
    int Q;
    SetConsoleTextAttribute ( h, FOREGROUND_BLUE);
    printf("It's the user manual. First tell me the number of changes you wish for.\n");
    scanf("%d", &Q);
    while (Q--) {
        sleep(.5);
        system("cls");
        SetConsoleTextAttribute ( h, FOREGROUND_GREEN);
        for (int i = 0; i < Z; i++) {
            for (int j = 0; j < Z; j++) {
                if (table[i][j][0] >= '0' && table[i][j][0] <= '9') 
                    SetConsoleTextAttribute ( h, FOREGROUND_RED | FOREGROUND_GREEN);
                for (int k = 0; k < n; k++) 
                    printf("%c", table[i][j][k]);
                if (table[i][j][0] >= '0' && table[i][j][0] <= '9') 
                    SetConsoleTextAttribute ( h, FOREGROUND_GREEN);
            }
            printf("\n");
        }
        int i, j;
        SetConsoleTextAttribute ( h, FOREGROUND_BLUE);
        printf("please say the cordinates that you wish to change it's state.(It's format should be like I J)\n");
        scanf("%d%d", &i, &j);
        printf("[1] = ENERGY\n");
        printf("[2] = MITOSIS\n");
        printf("[3] = FORBIDDEN\n");
        printf("[4] = NORMAL\n");
        int state;  scanf("%d", &state);
        if (i >= len || j >= len || state < 1 || state > 4 || i < 0 || j < 0) {
            printf("INVALID INPUT\nTRY AGAIN\n");
            Q++;
        }
        int x = 4 * j + 2, y = 4 * i + 1;
        if (j % 2 == 0)
            y += 2;
        else 
            y += 4;
        rel[x][y].state = state;
    }
    SetConsoleTextAttribute ( h, wOldColorAttrs);
    return 0;
}