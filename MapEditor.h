#define ZZ  499349

void Print(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        Sleep(10);
        printf("%c", str[i]);
    }
}

int IJTOXY(int i, int j, int len) {
    int x = 4 * i + 2, y = 4 * (len - j - 1) + 3;
    if (i % 2 == 1) 
        y += 2;
    return x * ZZ + y;
}

void PRint(char table[512][512][3], int Z, HANDLE h, WORD wOldColorAttrs) {
    SetConsoleTextAttribute ( h, FOREGROUND_GREEN);
    for (int i = 0; i < Z; i++) {
        for (int j = 0; j < Z; j++) 
            for (int k = 0; k < 3; k++) {
                char tmp = table[i][j][k];
                if ((tmp >= '0' && tmp <= '9')) 
                    SetConsoleTextAttribute ( h, FOREGROUND_RED | FOREGROUND_GREEN);
                else if (tmp == '*')
                    SetConsoleTextAttribute ( h, FOREGROUND_GREEN);
                else 
                    SetConsoleTextAttribute ( h, FOREGROUND_RED | FOREGROUND_BLUE);
                printf("%c", tmp);
            }
        printf("\n");
    }
    SetConsoleTextAttribute ( h, wOldColorAttrs);
}

void init(char table[512][512][3], int len) {
    const char st[] = "** ", ts[] = "   ";
    int n = 3;
    int Z = 4 * len + 3;
    for (int i  = 0; i < Z; i++) {
        for (int j = 0; j < Z; j++) {
            int w = i % (2 * n - 2), x = j % (4 * n - 4);
            if ((Z - i <= 2) && (Z - j <= 2 || j <= 2) && len % 2) {
                for (int k = 0; k < n; k++)    table[i][j][k] = ts[k];
                continue;
            } else if (!(len % 2) && ((Z - i <= 2 && j <= 2) || (Z - j <= 2 && i <= 2))) {
                for (int k = 0; k < n; k++)    table[i][j][k] = ts[k];
                continue;
            }
            if (w < n) {
                if (w == n - 1) {
                    if (!j) 
                        for (int k = 0; k < n; k++)    table[i][j][k] = st[k];
                    else {
                        if (j < 3 * n - 3) {
                        for (int k = 0; k < n; k++)    table[i][j][k] = ts[k];
                            continue;
                        }
                        int y = j - (2 * n - 2);
                        x = y % (4 * n - 4);
                        if (x >= n - 1 && x <= 2 * n - 2)
                            for (int k = 0; k < n; k++)    table[i][j][k] = st[k];
                        else
                            for (int k = 0; k < n; k++)    table[i][j][k] = ts[k];
                    }
                } else {
                    if (!w) {
                        if (x >= n - 1 && x <= 2 * n - 2)
                            for (int k = 0; k < n; k++)    table[i][j][k] = st[k];
                        else 
                            for (int k = 0; k < n; k++)    table[i][j][k] = ts[k];
                    } else {
                        if (x == n - 1 - w || x == 2 * n - 2 + w)
                            for (int k = 0; k < n; k++)    table[i][j][k] = st[k];
                        else 
                            for (int k = 0; k < n; k++)    table[i][j][k] = ts[k];
                    }
                }
            } else {
                int y = w - (n - 1);
                w = n - 1 - y;
                if (x == n - 1 - w || x == 2 * n - 2 + w)
                    for (int k = 0; k < n; k++)    table[i][j][k] = st[k];
                else 
                    for (int k = 0; k < n; k++)    table[i][j][k] = ts[k];
            }
        }
    }
    for (int j = 0; j < len; j++) 
        for (int i = 0; i < len; i++) {
            int x = 4 * j + 2, y = 4 * i + 1;
            if (j % 2 == 0)
                y += 2;
            else 
                y += 4;
            table[y][x][2] = '(', table[y][x + 1][0] = j + '0', table[y][x + 1][1] = ',', 
            table[y][x + 1][2] = '0' + len - i - 1, table[y][x + 2][0] = ')';
            table[y - 2][x + 1][0] = 'N';
        }
}

void RunMapEditor(char table[512][512][3], WORD wOldColorAttrs) {
    int rel[512][512];
    for (int i = 0; i < 512; i++)
        for (int j = 0; j < 512; j++)
            rel[i][j] = -1;
    char st[] = "** ", ts[] = "   ";
    Print("Please enter the length of the table. (It should be smaller than 10 in order to fit in The CMD. )\n");
    int n = 3, len; scanf("%d", &len);
    int Z = 4 * len + 3;
    init(table, len);
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    sleep(.5);
    system("cls");
    SetConsoleTextAttribute ( h, FOREGROUND_BLUE);
    Print("Now it's the primary table, I'm waiting for your order's to initialize the table.\n");
    PRint(table, Z, h, wOldColorAttrs);
    int Q;
    SetConsoleTextAttribute ( h, FOREGROUND_BLUE);
    Print("It's the user manual. First tell me the number of changes you wish for.\n");
    scanf("%d", &Q);
    while (Q--) {
        sleep(.5);
        system("cls");
        PRint(table, Z, h, wOldColorAttrs);
        int i, j;
        SetConsoleTextAttribute ( h, FOREGROUND_BLUE);
        Print("please say the cordinates that you wish to change it's state.(It's format should be like I J)\n");
        scanf("%d%d", &i, &j);
        Print("[1] = ENERGY\n");
        Print("[2] = MITOSIS\n");
        Print("[3] = FORBIDDEN\n");
        Print("[4] = NORMAL\n");
        int state;  scanf("%d", &state);
        int x = 4 * i + 2, y = 4 * (len - j - 1) + 3;
        if (i % 2 == 1) 
            y += 2;
        if (i >= len || j >= len || state < 1 || state > 4 || i < 0 || j < 0 || rel[i][j] != -1) {
            Print("INVALID INPUT\nTRY AGAIN\n");
            Sleep(1000);
            Q++;
            continue;
        }
        rel[i][j] = state;
        char tmp = 'E';
        if (state == 2) 
            tmp = 'M';
        else if (state == 3)
            tmp = 'F';
        else if (state == 4)
            tmp = 'N';
        if (tmp == 'E')
            table[y - 2][x][1] = tmp, table[y - 2][x][2] = '=', table[y - 2][x + 1][0] = '1', table[y - 2][x + 1][1] = '0', table[y - 2][x + 1][2] = '0';
        else 
            table[y - 2][x + 1][1] = tmp;
    }
    sleep(.5);
    system("cls");
    PRint(table, Z, h, wOldColorAttrs);
    FILE* fp = fopen("map.bin", "wb");
    fwrite(&len, sizeof(int), 1, fp);
    for (int i = 0; i < len; i++) 
        for (int j = 0; j < len; j++) {
            if (rel[j][len - i - 1] == -1) 
                rel[j][len - i - 1] = 4;
            char tmp = rel[j][len - i - 1] + '0';
            fwrite(&tmp, sizeof(char), 1, fp);
        }
    fclose(fp);
}