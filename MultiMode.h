void start2(char table[MAXN][MAXN][3], int len, int rel[MAXN][MAXN], int remain[MAXN][MAXN], HANDLE h, WORD wOldColorAttrs, int typ, int turn, int is, int yes, order Vector[MAXN]) {
    int Z = 4 * len + 3;
    if (typ) {
        Print("Do you want to play against computer ?\n[1]Yes\n[2]No\n");
        scanf("%d", &yes);
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
        int num;
        if (yes == 2 || !turn)
            scanf("%d", &num);
        else if (turn)
            num = 0;
        int tmp = TakeTurn(turn, --num, table, len, rel, remain, h, wOldColorAttrs, is, turn, (yes == 1), NULL, Vector);
        while (!tmp && yes == 1 && turn) 
            tmp = TakeTurn(turn, -1, table, len, rel, remain, h, wOldColorAttrs, is, turn, (yes == 1), NULL, Vector);
        if (tmp == 1)
            turn = 1 - turn;
        else if (tmp == 2)
            break;
    }
    SetConsoleTextAttribute ( h, FOREGROUND_BLUE);
    int sm = 0;
    for (cell* cur = lst[0]; cur; cur = cur->nxt)
        sm += cur->sc;
    Print("The total score of player one is ");
    printf("%d\n", sm);
    SetConsoleTextAttribute ( h, FOREGROUND_RED);
    sm = 0;
    for (cell* cur = lst[1]; cur; cur = cur->nxt)
        sm += cur->sc;
    Print("The total score of player two is ");
    printf("%d\n", sm);
    sleep(5);
    lst[0] = NULL;
    lst[1] = NULL;
}