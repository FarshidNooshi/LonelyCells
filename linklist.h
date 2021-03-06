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

void upd(int col, int num, int val) {
    cell* point = get(col, num);
    point->sc += val;
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

void AddEnd(int num, cell* temp) {
    if (lst[num] == NULL) {
        lst[num] = temp;
        lst[num]->nxt = NULL;
    } else {
        cell* cur;
        for (cur = lst[num]; cur->nxt != NULL; cur = cur->nxt);
        cur->nxt = temp;
        temp->nxt = NULL;
    }
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

int valid(int x, int y, int len, int rel[MAXN][MAXN]) {
    if (x < 0 || x >= len || y < 0 || y >= len || rel[x][y] == 3)
        return 0;
    for (int p = 0; p < 2; p++) {
        struct cell* ptr = lst[p];
        while (ptr) {
            if (ptr->x == x && ptr->y == y)
                return 0;
            ptr = ptr->nxt;
        }
    }
    return 1;
}

int LoadRead(int rel[MAXN][MAXN], int remain[MAXN][MAXN], char table[MAXN][MAXN][3], int* ptrr, order Vector[MAXN]) {
    int ptr = *ptrr;
    int against;
    FILE* fs = fopen("save.bin", "rb");
    int typ;    fread(&typ, sizeof(int), 1, fs);
    int len, turn;   
    fread(&len, sizeof(int), 1, fs);
    for (int i = 0; i < len; i++) 
        for (int j = 0; j < len; j++) 
            fread(&rel[j][len - i - 1], sizeof(int), 1, fs);
    for (int i = 0; i < len; i++) 
        for (int j = 0; j < len; j++)
            fread(&remain[j][len - i - 1], sizeof(int), 1, fs);
    if (typ) {
        fread(&turn, sizeof(int), 1, fs);
        int num;
        for (int p = 0; p < 2; p++) {
            fread(&num, sizeof(int), 1, fs);
            for (int i = 0; i < num; i++) {
                cell* mem = NEW();
                fread(mem->name, sizeof(char) * 6, 6, fs);
                fread(&mem->x, sizeof(int), 1, fs);
                fread(&mem->y, sizeof(int), 1, fs);
                fread(&mem->sc, sizeof(int), 1, fs);
                AddEnd(p, mem);
                initname(mem->x, mem->y, mem->name, len, table);
            }
        }
        fread(&against, sizeof(int), 1, fs);
    } else {
        int num;
        fread(&num, sizeof(int), 1, fs);
        for (int i = 0; i < num; i++) {
            cell* mem = NEW();
            fread(mem->name, sizeof(char) * 6, 6, fs);
            fread(&mem->x, sizeof(int), 1, fs);
            fread(&mem->y, sizeof(int), 1, fs);
            fread(&mem->sc, sizeof(int), 1, fs);
            AddEnd(0, mem);
            initname(mem->x, mem->y, mem->name, len, table);
        }
        fread(ptrr, sizeof(int), 1, fs);
        ptr = *ptrr;
        for (int i = 0; i < ptr; i++) {
            fread(&Vector[i].typ, sizeof(int), 1, fs);
            if (Vector[i].typ == 1) {
                fread(Vector[i].ch.name, sizeof(char) * 6, 6, fs);
                fread(&Vector[i].ch.x, sizeof(int), 1, fs);
                fread(&Vector[i].ch.y, sizeof(int), 1, fs);
                fread(&Vector[i].ch.sc, sizeof(int), 1, fs);
                fread(&Vector[i].dir, sizeof(int), 1, fs);
            } else if (Vector[i].typ == 2) {
                fread(Vector[i].ch.name, sizeof(char) * 6, 6, fs);
                fread(&Vector[i].ch.x, sizeof(int), 1, fs);
                fread(&Vector[i].ch.y, sizeof(int), 1, fs);
                fread(&Vector[i].ch.sc, sizeof(int), 1, fs);
                fread(Vector[i].pa1.name, sizeof(char) * 6, 6, fs);
                fread(&Vector[i].pa1.x, sizeof(int), 1, fs);
                fread(&Vector[i].pa1.y, sizeof(int), 1, fs);
                fread(&Vector[i].pa1.sc, sizeof(int), 1, fs);
                fread(Vector[i].pa2.name, sizeof(char) * 6, 6, fs);
                fread(&Vector[i].pa2.x, sizeof(int), 1, fs);
                fread(&Vector[i].pa2.y, sizeof(int), 1, fs);
                fread(&Vector[i].pa2.sc, sizeof(int), 1, fs);
            } else {
                fread(Vector[i].pa1.name, sizeof(char) * 6, 6, fs);
                fread(&Vector[i].pa1.x, sizeof(int), 1, fs);
                fread(&Vector[i].pa1.y, sizeof(int), 1, fs);
                fread(&Vector[i].pa1.sc, sizeof(int), 1, fs);
                fread(&Vector[i].dir, sizeof(int), 1, fs);
            }
        }
    }
    fclose(fs);
    init(table, len);
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len; j++) 
            AddToTable(i, j, rel[i][j], remain[i][j], len, table);
    for (cell* cur = lst[0]; cur; cur = cur->nxt)
        initname(cur->x, cur->y, cur->name, len, table);
    if (typ) 
        for (cell* cur = lst[1]; cur; cur = cur->nxt)
            initname(cur->x, cur->y, cur->name, len, table);
    return ((len * 2 + typ) * ZZ + turn) * 2 + against;
}

void SavePrint1(int len, int rel[MAXN][MAXN], int remain[MAXN][MAXN], int ptr, order Vector[MAXN]) {
    FILE* fs = fopen("save.bin", "wb");
    int tmp = 0;
    fwrite(&tmp, sizeof(int), 1, fs);
    fwrite(&len, sizeof(int), 1, fs);
    for (int i = 0; i < len; i++) 
        for (int j = 0; j < len; j++) 
            fwrite(&rel[j][len - i - 1], sizeof(int), 1, fs);
    for (int i = 0; i < len; i++) 
        for (int j = 0; j < len; j++)
            fwrite(&remain[j][len - i - 1], sizeof(int), 1, fs);
    int cnt = 0;
    cell* pnt = lst[0];
    while (pnt)    pnt = pnt->nxt, cnt++;
    fwrite(&cnt, sizeof(int), 1, fs);
    for (pnt = lst[0]; pnt; pnt = pnt->nxt) {
        fwrite(pnt->name, sizeof(char) * 6, 6, fs);
        fwrite(&pnt->x, sizeof(int), 1, fs);
        fwrite(&pnt->y, sizeof(int), 1, fs);
        fwrite(&pnt->sc, sizeof(int), 1, fs);
    }
    fwrite(&ptr, sizeof(int), 1, fs);
    for (int i = 0; i < ptr; i++) {
        fwrite(&Vector[i].typ, sizeof(int), 1, fs);
        if (Vector[i].typ == 1) {
            fwrite(Vector[i].ch.name, sizeof(char) * 6, 6, fs);
            fwrite(&Vector[i].ch.x, sizeof(int), 1, fs);
            fwrite(&Vector[i].ch.y, sizeof(int), 1, fs);
            fwrite(&Vector[i].ch.sc, sizeof(int), 1, fs);
            fwrite(&Vector[i].dir, sizeof(int), 1, fs);
        } else if (Vector[i].typ == 2) {
            fwrite(Vector[i].ch.name, sizeof(char) * 6, 6, fs);
            fwrite(&Vector[i].ch.x, sizeof(int), 1, fs);
            fwrite(&Vector[i].ch.y, sizeof(int), 1, fs);
            fwrite(&Vector[i].ch.sc, sizeof(int), 1, fs);
            fwrite(Vector[i].pa1.name, sizeof(char) * 6, 6, fs);
            fwrite(&Vector[i].pa1.x, sizeof(int), 1, fs);
            fwrite(&Vector[i].pa1.y, sizeof(int), 1, fs);
            fwrite(&Vector[i].pa1.sc, sizeof(int), 1, fs);
            fwrite(Vector[i].pa2.name, sizeof(char) * 6, 6, fs);
            fwrite(&Vector[i].pa2.x, sizeof(int), 1, fs);
            fwrite(&Vector[i].pa2.y, sizeof(int), 1, fs);
            fwrite(&Vector[i].pa2.sc, sizeof(int), 1, fs);
        } else {
            fwrite(Vector[i].pa1.name, sizeof(char) * 6, 6, fs);
            fwrite(&Vector[i].pa1.x, sizeof(int), 1, fs);
            fwrite(&Vector[i].pa1.y, sizeof(int), 1, fs);
            fwrite(&Vector[i].pa1.sc, sizeof(int), 1, fs);
            fwrite(&Vector[i].dir, sizeof(int), 1, fs);
        }
    }
    fclose(fs);
}

void SavePrint2(int len, int rel[MAXN][MAXN], int remain[MAXN][MAXN], int turn, int yes) {
    FILE* fs = fopen("save.bin", "wb");
    int tmp = 1;
    fwrite(&tmp, sizeof(int), 1, fs);
    fwrite(&len, sizeof(int), 1, fs);
    for (int i = 0; i < len; i++) 
        for (int j = 0; j < len; j++) 
            fwrite(&rel[j][len - i - 1], sizeof(int), 1, fs);
    for (int i = 0; i < len; i++) 
        for (int j = 0; j < len; j++)
            fwrite(&remain[j][len - i - 1], sizeof(int), 1, fs);
    fwrite(&turn, sizeof(int), 1, fs);
    for (int p = 0; p < 2; p++) {
        int cnt = 0;
        cell* pnt = lst[p];
        while (pnt)    pnt = pnt->nxt, cnt++;
        fwrite(&cnt, sizeof(int), 1, fs);
        for (pnt = lst[p]; pnt; pnt = pnt->nxt) {
            fwrite(pnt->name, sizeof(char) * 6, 6, fs);
            fwrite(&pnt->x, sizeof(int), 1, fs);
            fwrite(&pnt->y, sizeof(int), 1, fs);
            fwrite(&pnt->sc, sizeof(int), 1, fs);
        }
    }
    fwrite(&yes, sizeof(int), 1, fs);
    fclose(fs);
}