int TakeTurn(int col, int num, char table[512][512][3], int len, int rel[512][512], int remain[512][512], HANDLE h, WORD wOldColorAttrs, int is, int turn);

void start2(char table[512][512][3], int len, int rel[512][512], int remain[512][512], HANDLE h, WORD wOldColorAttrs, int typ, int turn, int is) {
    int Z = 4 * len + 3;
    if (typ) {
        SetConsoleTextAttribute ( h, FOREGROUND_BLUE);
        Print("Please enter your preferred number of cells for player one\n");
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
        SetConsoleTextAttribute ( h, FOREGROUND_RED);
        Print("Please enter your preferred number of cells for player two\n");
        int n2; scanf("%d", &n1);
        for (int i = 0; i < n1; i++) {
            cell* mem = NEW();
            GenerateName(mem);
            add(1, mem);
            int x = rand() % len, y = rand() % len;
            while (!valid(x, y, len, rel))
                x = rand() % len, y = rand() % len;
            mem->x = x, mem->y = y;
            initname(mem->x, mem->y, mem->name, len, table);
        }
    }
    while (true) {
        system("cls");
        SetConsoleTextAttribute ( h, FOREGROUND_BLUE);
        PRint(table, Z, h, wOldColorAttrs);
        Print("Player one cells are :\n");
        printcells(0, 0, h, wOldColorAttrs);
        Print("Player two cells are :\n");
        printcells(1, 1, h, wOldColorAttrs);
        SetConsoleTextAttribute ( h, turn ? FOREGROUND_RED : FOREGROUND_BLUE);
        turn ? Print("Player 2:\n") : Print("Player 1:\n");
        int num;    scanf("%d", &num);
        int tmp = TakeTurn(turn, --num, table, len, rel, remain, h, wOldColorAttrs, is, turn);
        if (tmp)
            turn = 1 - turn;
    }
}