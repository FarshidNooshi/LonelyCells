//In The Name Of GOD
#include<time.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<Windows.h>
#include"MapEditor.h"

#define MAXN  512

enum blocks {
 ENERGY = 1,
 MITOSIS,
 FORBIDDEN,
 NORMAL
};


struct cell {
    char name[6];
    int x, y;
    struct cell* nxt;
} *lst;

int rel[MAXN][MAXN], remain[MAXN][MAXN];
int IsSingle, len, Z,  n = 3;
char table[MAXN][MAXN][3];

void GenerateName(struct cell*);
int valid(int, int );
void init();

int main() {
    // system("cls");
    srand(time(NULL));
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    WORD wOldColorAttrs;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    wOldColorAttrs = csbiInfo.wAttributes; 
    SetConsoleTextAttribute ( h, FOREGROUND_BLUE);
    Print("Hi.\nMy name is Farshid, I'm the developer of this program. It's my universoty final project.\nI hope you enjoy it!\n");
    Print("Lets begin.\nDo you want to use the Map editor or not?\n[1]Yes\n[2]No\n");
    int tmp; scanf("%d", &tmp);
    if (tmp == 1)
        RunMapEditor();
    FILE* fr = fopen("map.bin", "rb");
    fread(&len, sizeof(int), 1, fr);
    for (int i = 0; i < len; i++) {
        char tmp2[MAXN];
        fread(tmp2, sizeof(char), len, fr);
        for (int j = 0; j < len; j++)
            rel[j][len - i - 1] = tmp2[j] - '0';
    } 
    fclose(fr);
    init();
    int Z = 4 * len + 3;
    // system("cls");
    Print("Welcome to the game\n");
    printf("[1]Load\n");
    printf("[2]New single player game\n");
    printf("[3]New Multiplayer game\n");
    printf("[4]Exit\n");
    scanf("%d", &tmp);
    if (tmp == 2) {
        lst = (struct cell*)malloc(sizeof(struct cell));
        lst->x = -1;
        lst->nxt = NULL;
        struct cell *ptr = lst->nxt;
        struct cell *prv = lst;
        IsSingle = 1;
        int m, cnt = 0;
        scanf("%d", &m);
        for (int i = 0; i < len; i++)
            for (int j = 0; j < len; j++)
                cnt += rel[i][j] == FORBIDDEN;
        if (m + cnt > len * len) {
            Print("Wrong input\n");
            return 0;
        }
        for (int i = 0; i < m; i++) {
            ptr = (struct cell*)malloc(sizeof(struct cell));
            ptr->nxt = NULL;
            prv->nxt = ptr;
            GenerateName(prv);
            int x = rand() % len, y = rand() % len;
            while (!valid(x, y))
                x = rand() % len, y = rand() % len;
            prv->x = x, prv->y = y;
            x = 4 * prv->x + 2, y = 4 * (len - prv->y - 1) + 3;
            if (prv->x % 2) 
                y += 2;
            table[y - 1][x][2] = prv->name[0];
            table[y - 1][x + 1][0] = prv->name[1], table[y - 1][x + 1][1] = prv->name[2], table[y - 1][x + 1][2] = prv->name[3];
            table[y - 1][x + 2][0] = prv->name[4];
            prv = ptr;
            ptr = NULL;
        }
        // system("cls");
        SetConsoleTextAttribute ( h, FOREGROUND_GREEN);
        for (int i = 0; i < Z; i++) {
            for (int j = 0; j < Z; j++) 
                for (int k = 0; k < n; k++) {
                    char tmp2 = table[i][j][k];
                    if ((tmp2 >= '0' && tmp2 <= '9')) 
                        SetConsoleTextAttribute ( h, FOREGROUND_RED | FOREGROUND_GREEN);
                    else if (tmp2 == '*')
                        SetConsoleTextAttribute ( h, FOREGROUND_GREEN);
                    else 
                        SetConsoleTextAttribute ( h, FOREGROUND_RED | FOREGROUND_BLUE);
                    printf("%c", tmp2);
                }
            printf("\n");
        }
        while (1) {
            Print("Please choose one of your cells:\n");
            int counter = 1;
            for (struct cell* cur = lst; cur->nxt != NULL; cur = cur->nxt)
                printf("[%d] %s (%d, %d)\n", counter++, cur->name, cur->x, cur->y); 
            scanf("%d", &tmp);
            
        }
    }
}

void init() {
    const char st[] = "** ", ts[] = "   ";
    int Z = 4 * len + 3;
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
    for (int j = 0; j < len; j++) 
        for (int i = 0; i < len; i++) {
            int x = 4 * j + 2, y = 4 * i + 1;
            if (j % 2 == 0)
                y += 2;
            else 
                y += 4;
            table[y][x][2] = '(', table[y][x + 1][0] = j + '0', table[y][x + 1][1] = ',', 
            table[y][x + 1][2] = '0' + len - i - 1, table[y][x + 2][0] = ')';
        }
    for (int i = 0; i < len; i++) 
        for (int j = 0; j < len; j++) {
            int x = 4 * i + 2, y = 4 * (len - j - 1) + 3;
            char tmp = 'E';
            if (rel[i][j] == 2) 
                tmp = 'M';
            else if (rel[i][j] == 3)
                tmp = 'F';
            else if (rel[i][j] == 4)
                tmp = 'N';
            if (i % 2 == 1) 
                y += 2;
            if (tmp == 'E')
                table[y - 2][x][1] = tmp, table[y - 2][x][2] = '=', table[y - 2][x + 1][0] = '1'
                , table[y - 2][x + 1][1] = '0', table[y - 2][x + 1][2] = '0';
            else 
                table[y - 2][x + 1][1] = tmp;
    }
}

int valid(int x, int y) {
    if (rel[x][y] == FORBIDDEN)
        return 0;
    struct cell* ptr = lst;
    while (ptr->nxt != NULL) {
        if (ptr->x == x && ptr->y == y)
            return 0;
        ptr = ptr->nxt;
    }
    return 1;
}

void GenerateName(struct cell* mem) {
    const char ch[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    int mm = 5;
    for (int i = 0; i < mm; i++) 
        mem->name[i] = ch[rand() % (sizeof(ch) / sizeof(char) - 1)];
    mem->name[5] = '\0';
}