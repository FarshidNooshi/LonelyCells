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
    return ret;
}

int find(cell* lst, cell x) {
    int i = 0;
    for (cell* cur = lst; cur != NULL; cur = cur->nxt, i++)
        if (cur->x == x.x && cur->y == x.y)
            return i;
}

cell* get(cell* lst, int t) {
    cell* ptr = lst;
    while (t--)
        ptr = ptr->nxt;
    return ptr;
}

void del(cell* lst, cell x) {
    int id = find(lst, x);
    if (id == 0) {
        lst = lst->nxt;
        return ;
    }
    cell* prev = get(lst, id - 1);
    cell* cur = get(lst, id);
    prev->nxt = cur->nxt;
}

void add(cell* lst, cell temp) {
    cell* cur;
    for (cur = lst; cur->nxt != NULL; cur = cur->nxt);
    cur->nxt = &temp;
    temp.nxt = NULL;
}