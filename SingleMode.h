#define ZZ  499349

int valid(int x, int y, int len, int rel[512][512], cell** lstt) {
    cell* lst = *lstt;
    if (x < 0 || x > len || y < 0 || y > len || rel[x][y] == 3)
        return 0;
    struct cell* ptr = lst;
    while (ptr != NULL) {
        if (ptr->x == x && ptr->y == y)
            return 0;
        ptr = ptr->nxt;
    }
    return 1;
}

void printcells(cell* lst, int col, HANDLE h, WORD wOldColorAttrs) {
    if (col)
        SetConsoleTextAttribute ( h, FOREGROUND_RED);
    else 
        SetConsoleTextAttribute ( h, FOREGROUND_BLUE);
    int counter = 1;
    for (cell* cur = lst; cur != NULL; cur = cur->nxt, counter++)
        printf("[%d] %s (%d, %d)\n", counter, cur->name, cur->x, cur->y);
    SetConsoleTextAttribute ( h, wOldColorAttrs); 
}

void initname(int x, int y, char* name, int len, char table[512][512][3]) {
    x = IJTOXY(x, y, len);
    y = x % ZZ, x = x / ZZ;
    table[y - 1][x][2] = name[0];
    table[y - 1][x + 1][0] = name[1], table[y - 1][x + 1][1] = name[2], table[y - 1][x + 1][2] = name[3];
    table[y - 1][x + 2][0] = name[4];
}

void move(int col, int num, char table[512][512][3], cell** lstt, int len, int rel[512][512], HANDLE h, WORD wOldColorAttrs, int x, int y) {
    if (!valid(x, y, len, rel, lstt)) {
        Print("INVALID INPUT\nTRY AGAIN\n");
        Sleep(1000);
        return ;
    }
    cell* lst = *lstt;
    cell* point = get(lst, num);
    initname(point->x, point->y, "     ", len, table);
    initname(x, y, point->name, len, table);
    point->x = x, point->y = y;
}

void TakeTurn(int col, int num, char table[512][512][3], cell** lstt, int len, int rel[512][512], HANDLE h, WORD wOldColorAttrs) {
    cell* lst = *lstt;
    cell* point = get(lst, num);
    SetConsoleTextAttribute ( h, FOREGROUND_BLUE);
    Print("[1]Move\n");
    Print("[2]Split a cell\n");
    Print("[3]Boost energy\n");
    Print("[4]Save\n");
    Print("[5]Exit\n");
    int typ;    scanf("%d", &typ);
    if (typ == 5)
        exit(0);
    if (typ == 1) {
        Print("[1]North\n");
        Print("[2]South\n");
        Print("[3]Northeast\n");
        Print("[4]Northwest\n");
        Print("[5]Southeast\n");
        Print("[6]Southwest\n");
        int dir;    scanf("%d", &dir);
        int x = point->x, y = point->y;
        if (dir == 1)
            y++;
        else if (dir == 2)
            y--;
        else if (dir == 3) 
            x++, y += (x % 2 == 0);
        else if (dir == 4)
            x--, y += (x % 2 == 0);
        else if (dir == 5)
            x++, y -= (x % 2);
        else 
            x--, y -= (x % 2);
        move(col, num, table, lstt, len, rel, h, wOldColorAttrs, x, y);
    }   
}

void start(char table[512][512][3], cell** lstt, int len, int rel[512][512], HANDLE h, WORD wOldColorAttrs) {
    cell* lst = *lstt;
    SetConsoleTextAttribute ( h, FOREGROUND_BLUE);
    Print("Please enter your preferred number of cells\n");
    int Z = 4 * len + 3;
    int n1; scanf("%d", &n1);
	for (int i = 0; i < n1; i++) {
		cell* mem = NEW();
		GenerateName(mem);
		add(&lst, mem);
		int x = rand() % len, y = rand() % len;
		while (!valid(x, y, len, rel, lstt))
			x = rand() % len, y = rand() % len;
		mem->x = x, mem->y = y;
        initname(mem->x, mem->y, mem->name, len, table);
    }
    while (true) {
        system("cls");
        PRint(table, Z, h, wOldColorAttrs);
        printcells(lst, 0, h, wOldColorAttrs);
        int num;    scanf("%d", &num);
        TakeTurn(0, --num, table, &lst, len, rel, h, wOldColorAttrs);
    }
}