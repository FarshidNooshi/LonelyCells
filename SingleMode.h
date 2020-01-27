#define ZZ  499349

enum blocks { ENERGY = 1, MITOSIS, FORBIDDEN, NORMAL};

void initname(int x, int y, char* name, int len, char table[512][512][3]) {
    x = IJTOXY(x, y, len);
    y = x % ZZ, x = x / ZZ;
    table[y - 1][x][2] = name[0];
    table[y - 1][x + 1][0] = name[1], table[y - 1][x + 1][1] = name[2], table[y - 1][x + 1][2] = name[3];
    table[y - 1][x + 2][0] = name[4];
}

void move(int col, int num, char table[512][512][3], cell** lstt, int len, int rel[512][512], HANDLE h, WORD wOldColorAttrs, int x, int y) {
    if (!valid(x, y, len, rel, 0)) {
        Print("INVALID INPUT\nTRY AGAIN\n");
        Sleep(1000);
        return ;
    }
    cell* lst = *lstt;
    cell* point = get(0, num);
    initname(point->x, point->y, "     ", len, table);
    initname(x, y, point->name, len, table);
    point->x = x, point->y = y;
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
        x++, y -= (x % 2 == 0);
    else 
        x--, y -= (x % 2 == 0);
    return x * ZZ + y;
}

void split(int col, int num, char table[512][512][3], cell** lstt, int len, int rel[512][512], HANDLE h, WORD wOldColorAttrs) {
    cell* lst = *lstt;
    cell* point = get(0, num);
    int x = point->x;
    int y = point->y;
    int can = 0;
    for (int i = 1; i < 6; i++) 
        if (valid(getdir(i, x, y) / ZZ, getdir(i, x, y) % ZZ, len, rel, 0))
            can = 1;
    if (rel[x][y] != MITOSIS || point->sc < 80 || !can) {
        Print("INVALID INPUT\nTRY AGAIN\n");
        sleep(2);
        return ;
    }
    del(0, point);
    cell* mem = NEW();
    GenerateName(mem);
    mem->x = x, mem->y = y;
    mem->sc = 40;
    add(0, mem);
    initname(mem->x, mem->y, mem->name, len, table);
    int dir = rand() % 6 + 1;
    while (!valid(getdir(dir, x, y) / ZZ, getdir(dir, x, y) % ZZ, len, rel, 0))
        dir = rand() % 6 + 1;
    cell* nem = NEW();
    GenerateName(nem);
    nem->x = getdir(dir, x, y) / ZZ, nem->y = getdir(dir, x, y) % ZZ;
    nem->sc = 40;
    add(0, nem);
    initname(nem->x, nem->y, nem->name, len, table);
}

void TakeTurn(int col, int num, char table[512][512][3], cell** lstt, int len, int rel[512][512], int remain[512][512], HANDLE h, WORD wOldColorAttrs) {
    cell* lst = *lstt;
    cell* point = get(0, num);
    SetConsoleTextAttribute ( h, FOREGROUND_BLUE);
    Print("[1]Move\n");
    Print("[2]Split a cell\n");
    Print("[3]Boost energy\n");
    Print("[4]Save\n");
    Print("[5]Exit\n");
    int typ;    scanf("%d", &typ);
    if (typ == 5) {
        SetConsoleTextAttribute ( h, wOldColorAttrs);     
        exit(0);
    }
    if (typ == 1) {
        Print("[1]North\n");
        Print("[2]South\n");
        Print("[3]Northeast\n");
        Print("[4]Northwest\n");
        Print("[5]Southeast\n");
        Print("[6]Southwest\n");
        int dir;    scanf("%d", &dir);
        int x = point->x, y = point->y;
        x = getdir(dir, x, y);
        y = x % ZZ, x = x / ZZ;
        move(col, num, table, lstt, len, rel, h, wOldColorAttrs, x, y);
    } else if (typ == 2) 
        split(col, num, table, lstt, len, rel, h, wOldColorAttrs);
    else if (typ == 3) {
        int x = point->x, y = point->y;
        if (rel[x][y] == ENERGY) {
            if (remain[x][y] < 15)
                point->sc += remain[x][y], remain[x][y] = 0;
            else 
                point->sc += 15, remain[x][y] -= 15;
                int i = x, j = y;
                x = IJTOXY(i, j, len);
                y = x % ZZ, x = x / ZZ;
                if (remain[i][j] < 10)
                    table[y - 2][x + 1][0] = remain[i][j] + '0', table[y - 2][x + 1][1] = ' ';
                else 
                    table[y - 2][x + 1][0] = remain[i][j] / 10 + '0', table[y - 2][x + 1][1] = remain[i][j] % 10 + '0', table[y - 2][x + 1][2] = ' ';
        } else {
            Print("INVALID INPUT\nTRY AGAIN\n");
            sleep(2);
        }
    } else  // 0, len, Z, table, rel, remain, cell 
        SavePrint1(len, rel, remain);
    SetConsoleTextAttribute ( h, wOldColorAttrs); 
}

void start(char table[512][512][3], cell** lstt, int len, int rel[512][512], int remain[512][512], HANDLE h, WORD wOldColorAttrs, int typ) {
    cell* lst = *lstt;
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
            while (!valid(x, y, len, rel, 0))
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
        TakeTurn(0, --num, table, &lst, len, rel, remain, h, wOldColorAttrs);
    }
}