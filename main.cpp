//In The Name Of GOD
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"READER.h"
#include"Computer.h"
#include"MapEditor.h" 
#include"GraphicPrint.h"

#define MAXN 128

typedef struct Cell     sCell;
typedef struct table    stable;

struct String {
    char s[MAXN];
    int sz;
};

struct Cell {
    int x, y;
    String name;
    sCell* nxt;
};

struct table {
    int x, y;
};

sCell* lst;//سلول ها 
stable Tbl[MAXN][MAXN];
int n;

int main() {
    
}