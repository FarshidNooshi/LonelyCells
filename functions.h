#ifndef DEBUG
typedef struct cell cell;
struct cell {
    char name[6];
    int x = -1, y = -1, sc = 0;
    cell* nxt;
} *lst[2];
#define DEBUG
#endif

#define MAXN  512
#define ZZ  499349

enum blocks { ENERGY = 1, MITOSIS, FORBIDDEN, NORMAL};

int TakeTurn(int col, int num, char table[MAXN][MAXN][3], int len, int rel[MAXN][MAXN], int remain[MAXN][MAXN], HANDLE h, WORD wOldColorAttrs, int is, int turn, int yes);
void start2(char table[MAXN][MAXN][3], int len, int rel[MAXN][MAXN], int remain[MAXN][MAXN], HANDLE h, WORD wOldColorAttrs, int typ, int turn, int is);
void initname(int x, int y, char* name, int len, char table[MAXN][MAXN][3]);
int move(int col, int num, char table[MAXN][MAXN][3], int len, int rel[MAXN][MAXN], HANDLE h, WORD wOldColorAttrs, int x, int y);
int getdir(int dir, int x, int y);
int split(int col, int num, char table[MAXN][MAXN][3], int len, int rel[MAXN][MAXN], HANDLE h, WORD wOldColorAttrs);
void start(char table[MAXN][MAXN][3], int len, int rel[MAXN][MAXN], int remain[MAXN][MAXN], HANDLE h, WORD wOldColorAttrs, int typ, int is);
cell* NEW();
int find(int num, cell x);
cell* get(int num, int t);
void del(int num, cell* x);
void add(int num, cell* temp);
void AddEnd(int num, cell* temp);
void GenerateName(struct cell* mem);
void printcells(int num, int col, HANDLE h, WORD wOldColorAttrs);
int valid(int x, int y, int len, int rel[MAXN][MAXN]);
int LoadRead(int rel[MAXN][MAXN], int remain[MAXN][MAXN], char table[MAXN][MAXN][3]);
void SavePrint1(int len, int rel[MAXN][MAXN], int remain[MAXN][MAXN]);
void SavePrint2(int len, int rel[MAXN][MAXN], int remain[MAXN][MAXN], int turn);
void Print(char* str);
int IJTOXY(int i, int j, int len);
void PRint(char table[MAXN][MAXN][3], int Z, HANDLE h, WORD wOldColorAttrs);
void init(char table[MAXN][MAXN][3], int len);
int AddToTable(int i, int j, int state, int sc, int len, char table[MAXN][MAXN][3]);
void RunMapEditor(char table[MAXN][MAXN][3], WORD wOldColorAttrs);
void _();