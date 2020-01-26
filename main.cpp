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
    int x, y, sc = 0;
    struct cell* nxt;
} *lst;

int rel[MAXN][MAXN], remain[MAXN][MAXN];
int IsSingle, len, Z,  n = 3;
char table[MAXN][MAXN][3];

void DEL(struct cell* , struct cell* );
struct cell* get(struct cell*, int);
void GenerateName(struct cell*);
void move(struct cell* , int);
int valid(int, int );
void init();

int main() {
    system("cls");
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
        RunMapEditor(table);
    FILE* fr = fopen("map.bin", "rb");
    fread(&len, sizeof(int), 1, fr);
    for (int i = 0; i < len; i++) {
        char tmp2[MAXN];
        fread(tmp2, sizeof(char), len, fr);
        for (int j = 0; j < len; j++)
            rel[j][len - i - 1] = tmp2[j] - '0';
    } 
    fclose(fr);
    int Z = 4 * len + 3;
    system("cls");
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
        system("cls");
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
    }
}

void DEL(struct cell** lstt, struct cell* pt) {
    struct cell* ls = *lstt;
    if (pt->x == ls->x && pt->y == ls->y) {
        ls = ls->nxt;
        return;
    }
    struct cell* cur = ls;
    for (; cur->nxt != NULL; cur = cur->nxt)
        if (cur->nxt->x == pt->x && cur->nxt->y == pt->y) {
            cur->nxt->nxt = pt->nxt;
            break;
        }
}

struct cell* get(struct cell* ls, int nm) {
    struct cell* ptr = ls;
    while (--nm)
        ptr = ptr->nxt;
    return ptr;
}

int valid(int x, int y) {
    if (x < 0 || x > len || y < 0 || y > len || rel[x][y] == FORBIDDEN)
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