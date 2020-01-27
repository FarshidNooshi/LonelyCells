#include<stdlib.h>
#ifndef DEBUG
typedef struct cell cell;
struct cell {
    char name[6];
    int x = -1, y = -1, sc = 0;
    cell* nxt;
} *lst;
#define DEBUG
#endif

cell* NEW() {
    cell* ret = (cell*)malloc(sizeof(cell));
    ret->nxt = NULL;
    ret->x = -1, ret->y = -1, ret->sc = 0;
    return ret;
}

int find(cell** lstt, cell x) {
    cell* lst = *lstt;
    int i = 0;
    for (cell* cur = lst; cur != NULL; cur = cur->nxt, i++)
        if (cur->x == x.x && cur->y == x.y)
            return i;
}

cell* get(cell* lst, int t) {
    cell* ptr;
    for (ptr = lst; t && ptr != NULL; t--, ptr = ptr->nxt);
    return ptr;
}

void del(cell** lstt, cell x) {
    cell* lst = *lstt;
    int id = find(&lst, x);
    if (id == 0) {
        lst = lst->nxt;
        return ;
    }
    cell* prev = get(lst, id - 1);
    cell* cur = get(lst, id);
    prev->nxt = cur->nxt;
}

void add(cell** lstt, cell* temp) {
    temp->nxt = *lstt;
    *lstt = temp;
}

void GenerateName(struct cell* mem) {
    const char ch[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    int mm = 5;
    for (int i = 0; i < mm; i++) 
        mem->name[i] = ch[rand() % (sizeof(ch) / sizeof(char) - 1)];
    mem->name[5] = '\0';
}
