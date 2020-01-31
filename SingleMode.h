void initname(int x, int y, char* name, int len, char table[MAXN][MAXN][3]) {
    x = IJTOXY(x, y, len);
    y = x % ZZ, x = x / ZZ;
    table[y - 1][x][2] = name[0];
    table[y - 1][x + 1][0] = name[1], table[y - 1][x + 1][1] = name[2], table[y - 1][x + 1][2] = name[3];
    table[y - 1][x + 2][0] = name[4];
}

int move(int col, int num, char table[MAXN][MAXN][3], int len, int rel[MAXN][MAXN], HANDLE h, WORD wOldColorAttrs, int x, int y, int yes) {
    if (!valid(x, y, len, rel)) {
        if (!col) {
            Print("INVALID INPUT\nTRY AGAIN\n");
            sleep(2);
        }
        return 0;
    }
    cell* point = get(col, num);
    initname(point->x, point->y, "     ", len, table);
    initname(x, y, point->name, len, table);
    point->x = x, point->y = y;
    return 1;
}

int getdir(int dir, int x, int y) {
    if (dir == 1)
        y++;
    else if (dir == 2)
        y--;
    else if (dir == 3) 
        x++, y += (x % 2);
    else if (dir == 4)
        x--, y += (x % 2);
    else if (dir == 5)
        x++, y -= !(x % 2);
    else 
        x--, y -= !(x % 2);
    return x * ZZ + y;
}

int split(int col, int num, char table[MAXN][MAXN][3], int len, int rel[MAXN][MAXN], HANDLE h, WORD wOldColorAttrs, int yes, int* ptrr, order Vector[MAXN]) {
    int ptr = 0;
    if (ptrr)
        ptr = *ptrr;
    cell* point = get(col, num);
    int x = point->x;
    int y = point->y;
    int can = 0;
    for (int i = 1; i < 6; i++) 
        if (valid(getdir(i, x, y) / ZZ, getdir(i, x, y) % ZZ, len, rel))
            can = 1;
    if (rel[x][y] != MITOSIS || point->sc < 80 || !can) {
        if (!col) {
            Print("INVALID INPUT\nTRY AGAIN\n");
            sleep(2);
        }
        return 0;
    }
    Vector[ptr].typ = 2;
    Vector[ptr].ch = *point;
    del(col, point);
    cell* mem = NEW();
    GenerateName(mem);
    mem->x = x, mem->y = y;
    mem->sc = 40;
    add(col, mem);
    initname(mem->x, mem->y, mem->name, len, table);
    Vector[ptr].pa1 = *mem;
    int dir = rand() % 6 + 1;
    while (!valid(getdir(dir, x, y) / ZZ, getdir(dir, x, y) % ZZ, len, rel))
        dir = rand() % 6 + 1;
    cell* nem = NEW();
    GenerateName(nem);
    nem->x = getdir(dir, x, y) / ZZ, nem->y = getdir(dir, x, y) % ZZ;
    nem->sc = 40;
    add(col, nem);
    initname(nem->x, nem->y, nem->name, len, table);
    Vector[(*ptrr)++].pa2 = *nem;
    return 1;
}

int TakeTurn(int col, int num, char table[MAXN][MAXN][3], int len, int rel[MAXN][MAXN], int remain[MAXN][MAXN], HANDLE h, WORD wOldColorAttrs, int is, int turn, int yes, int* ptrr, order Vector[MAXN]) {
    int ptr = 0;
    if (ptrr)
        ptr = *ptrr;
    cell* point;
    if (num == -1) {
        int cnt = 0;
        while (get(col, cnt)) cnt++;
        num = rand() % cnt;
    }
    point = get(col, num);
    if (point == NULL) {
        Print("INVALID INPUT\nTRY AGAIN\n");
        sleep(2);
        SetConsoleTextAttribute ( h, wOldColorAttrs); 
        return 0;
    }
    if (is)
        SetConsoleTextAttribute ( h, turn ? FOREGROUND_RED : FOREGROUND_BLUE);
    else 
        SetConsoleTextAttribute ( h, FOREGROUND_BLUE);
    int typ = rand() % 3 + 1;
    if (!yes || col == 0) {
        Print("[1]Move\n");
        Print("[2]Split a cell\n");
        Print("[3]Boost energy\n");
        Print("[4]Save\n");
        if (!is) {
            Print("[5]Exit\n");
            Print("[6]Undo\n");
        } else 
            Print("[5]Exit\n");
        scanf("%d", &typ);
    }
    if (typ == 6) {
        if (ptr == 0) {
            Print("INVALID INPUT\nTRY AGAIN\n");
            sleep(2);
            SetConsoleTextAttribute ( h, wOldColorAttrs); 
            return 0;
        }
        ptr--;
        if (Vector[--(*ptrr)].typ == 1) {
            int x = Vector[ptr].ch.x, y = Vector[ptr].ch.y;
            int x2 = x, y2 = y;
            x = getdir(Vector[ptr].dir, x, y);
            y = x % ZZ, x = x / ZZ;
            initname(x2, y2, Vector[ptr].ch.name, len, table);
            initname(x, y, "     ", len, table);
            Vector[ptr].ch.x = x, Vector[ptr].ch.y = y;
            cell* po = get(0, find(0, Vector[ptr].ch));
            po->x = x2, po->y = y2;
        } else if (Vector[*ptrr].typ == 2) {
            cell* po = get(0, find(0, Vector[ptr].pa1));
            initname(po->x, po->y, "     ", len, table);
            del(0, po);
            po = get(0, find(0, Vector[ptr].pa2));
            initname(po->x, po->y, "     ", len, table);
            del(0, po);
            cell nem = Vector[ptr].ch;
            cell* mem = NEW();
            for (int i = 0; i < 6; i++)     mem->name[i] = nem.name[i];
            add(0, mem);
            mem->x = nem.x, mem->y = nem.y;
            mem->sc = nem.sc;
            initname(mem->x, mem->y, mem->name, len, table);
        } else {
            int x = Vector[ptr].ch.x, y = Vector[ptr].ch.y;
            remain[x][y] += Vector[ptr].dir;
            cell* po = get(0, find(0, Vector[ptr].ch));
            po->sc -= Vector[ptr].dir;
            int i = x, j = y;
            x = IJTOXY(i, j, len);
            y = x % ZZ, x = x / ZZ;
            if (remain[i][j] < 10)
                table[y - 2][x + 1][0] = remain[i][j] + '0', table[y - 2][x + 1][1] = ' ';
            else if (remain[i][j] < 100)
                table[y - 2][x + 1][0] = remain[i][j] / 10 + '0', table[y - 2][x + 1][1] = remain[i][j] % 10 + '0', table[y - 2][x + 1][2] = ' ';
            else 
                table[y - 2][x + 1][0] = '1', table[y - 2][x + 1][1] ='0', table[y - 2][x + 1][2] = '0';
        }
    }
    if (typ == 5) {
        SetConsoleTextAttribute ( h, wOldColorAttrs);     
        return 2;
    }
    if (typ == 1) {
        int dir = rand() % 6 + 1;    
        if (!yes || col == 0) {
            Print("[1]North\n");
            Print("[2]South\n");
            Print("[3]Northeast\n");
            Print("[4]Northwest\n");
            Print("[5]Southeast\n");
            Print("[6]Southwest\n");
            scanf("%d", &dir);
        }
        int x2 = point->x, y2 = point->y;
        int x = point->x, y = point->y;
        x = getdir(dir, x, y);
        y = x % ZZ, x = x / ZZ;
        int tmp = move(col, num, table, len, rel, h, wOldColorAttrs, x, y, yes);
        if (is && !tmp)
            return 0;
        if (!is && tmp) { 
            Vector[ptr].typ = 1;
            Vector[ptr].ch = *point;
            Vector[ptr].dir = dir;
            Vector[ptr].ch.x = x2, Vector[(*ptrr)++].ch.y = y2;
        }
    } else if (typ == 2) {
        int tmp = split(col, num, table, len, rel, h, wOldColorAttrs, yes, ptrr, Vector);
        if (is && !tmp)
            return 0;
    } else if (typ == 3) {
        int x = point->x, y = point->y;
        if (rel[x][y] == ENERGY) {
            Vector[ptr].typ = 3;
            Vector[ptr].ch = *point;
            if (remain[x][y] < 15)
                point->sc += remain[x][y], Vector[ptr].dir = remain[x][y], remain[x][y] = 0;
            else 
                point->sc += 15, remain[x][y] -= 15, Vector[ptr].dir = 15;
            if (ptrr)    (*ptrr)++;
            int i = x, j = y;
            x = IJTOXY(i, j, len);
            y = x % ZZ, x = x / ZZ;
            if (remain[i][j] < 10)
                table[y - 2][x + 1][0] = remain[i][j] + '0', table[y - 2][x + 1][1] = ' ';
            else 
                table[y - 2][x + 1][0] = remain[i][j] / 10 + '0', table[y - 2][x + 1][1] = remain[i][j] % 10 + '0', table[y - 2][x + 1][2] = ' ';
        } else {
            if (!yes || col == 0) {
                Print("INVALID INPUT\nTRY AGAIN\n");
                sleep(2);
            }
            return 0;
        }
    } else {  // 0, len, Z, table, rel, remain, cell 
        if (!is)
            SavePrint1(len, rel, remain, ptr, Vector);
        else 
            SavePrint2(len, rel, remain, turn, yes);// yes = 0 -> human // yes = 1 -> cpu
        return 0;
    }
    SetConsoleTextAttribute ( h, wOldColorAttrs); 
    return 1;
}

void start(char table[MAXN][MAXN][3], int len, int rel[MAXN][MAXN], int remain[MAXN][MAXN], HANDLE h, WORD wOldColorAttrs, int typ, int is, int* ptrr, order Vector[MAXN]) {
    int Z = 4 * len + 3;
    if (typ) {
        SetConsoleTextAttribute ( h, FOREGROUND_BLUE);
        Print("Please enter your preferred number of cells\n");
        int n1; scanf("%d", &n1);
        for (int i = 0; i < n1; i++) {
            cell* mem = NEW();
            GenerateName(mem);
            add(0, mem);
            int x = rand() % len, y = rand() % len;
            while (!valid(x, y, len, rel))
                x = rand() % len, y = rand() % len;
            mem->x = x, mem->y = y;
            initname(mem->x, mem->y, mem->name, len, table);
        }
    }
    while (true) {
        system("cls");
        PRint(table, Z, h, wOldColorAttrs);
        printcells(0, 0, h, wOldColorAttrs);
        SetConsoleTextAttribute ( h, FOREGROUND_BLUE);
        int num;    scanf("%d", &num);
        int x = TakeTurn(0, --num, table, len, rel, remain, h, wOldColorAttrs, is, 0, 0, ptrr, Vector);
        if (x == 2)
            break;
    }
    SetConsoleTextAttribute ( h, FOREGROUND_BLUE);
    int sm = 0;
    for (cell* cur = lst[0]; cur; cur = cur->nxt)
        sm += cur->sc;
    Print("The total score of player one is ");
    printf("%d\n", sm);
    sleep(5);
    lst[0] = NULL;
}