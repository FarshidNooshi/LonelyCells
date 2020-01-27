#include<stdlib.h>
#ifndef DEBUG
typedef struct cell cell;
struct cell {
    char name[6];
    int x = -1, y = -1, sc = 0;
    cell* nxt;
} *lst[2];
#define DEBUG
#endif

cell* NEW() {
    cell* ret = (cell*)malloc(sizeof(cell));
    ret->nxt = NULL;
    ret->x = -1, ret->y = -1, ret->sc = 0;
    return ret;
}

int find(int num, cell x) {
    int i = 0;
    for (cell* cur = lst[num]; cur != NULL; cur = cur->nxt, i++)
        if (cur->x == x.x && cur->y == x.y)
            return i;
}

cell* get(int num, int t) {
    cell* ptr;
    for (ptr = lst[num]; t && ptr != NULL; t--, ptr = ptr->nxt);
    return ptr;
}

void del(int num, cell* x) {
    int id = find(num, *x);
    if (id == 0) {
        lst[num] = lst[num]->nxt;
        return ;
    }
    cell* prev = get(num, id - 1);
    cell* cur = get(num, id);
    prev->nxt = cur->nxt;
}

void add(int num, cell* temp) {
    temp->nxt = lst[num];
    lst[num] = temp;
}

void GenerateName(struct cell* mem) {
    const char ch[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    int mm = 5;
    for (int i = 0; i < mm; i++) 
        mem->name[i] = ch[rand() % (sizeof(ch) / sizeof(char) - 1)];
    mem->name[5] = '\0';
}

void printcells(int num, int col, HANDLE h, WORD wOldColorAttrs) {
    if (col)
        SetConsoleTextAttribute ( h, FOREGROUND_RED);
    else 
        SetConsoleTextAttribute ( h, FOREGROUND_BLUE);
    int counter = 1;
    for (cell* cur = lst[num]; cur != NULL; cur = cur->nxt, counter++)
        printf("[%d] %s (%d, %d)\n", counter, cur->name, cur->x, cur->y);
    SetConsoleTextAttribute ( h, wOldColorAttrs); 
}

int valid(int x, int y, int len, int rel[512][512], int num) {
    if (x < 0 || x >= len || y < 0 || y >= len || rel[x][y] == 3)
        return 0;
    struct cell* ptr = lst[num];
    while (ptr != NULL) {
        if (ptr->x == x && ptr->y == y)
            return 0;
        ptr = ptr->nxt;
    }
    return 1;
}