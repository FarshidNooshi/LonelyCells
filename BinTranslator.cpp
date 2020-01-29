//In The Name Of GOD
#include<time.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<Windows.h>

#define MAXN 512

typedef struct cell cell;

enum blocks { ENERGY = 1, MITOSIS, FORBIDDEN, NORMAL};

struct cell {
    char name[6];
    int x, y, sc;
} mem[MAXN];

int len;
int remain[MAXN][MAXN], rel[MAXN][MAXN], occupied[MAXN][MAXN];


int main() {
    FILE* fr = fopen("map.bin", "rb");
    fread(&len, sizeof(int), 1, fr);
    for (int i = 0; i < len; i++) {
        char tmp2[MAXN];
        fread(tmp2, sizeof(char), len, fr);
        for (int j = 0; j < len; j++)
            rel[j][len - i - 1] = tmp2[j] - '0';
    } 
    fclose(fr);
    FILE* fs = fopen("save.bin", "rb");
    if (fs == NULL) {
        fr = fopen("TEXT.txt", "w");
        fprintf(fr, "The length of the table is %d\n", len);
        for (int i = 0; i < len; i++) 
            for (int j = 0; j < len; j++) {
                fprintf(fr, "{(%d, %d), ", i, j);
                if (rel[i][j] == ENERGY)
                    fprintf(fr, "ENERGY = 100, not occupied}\n");
                else if (rel[i][j] == MITOSIS)
                    fprintf(fr, "MITOSIS, not occupied}\n");
                else if (rel[i][j] == FORBIDDEN)
                    fprintf(fr, "FORBIDDEN, not occupied}\n");
                else 
                    fprintf(fr, "NORMAL, not occupied}\n");
        }
        fclose(fr);
        return 0;
    }
    int cnt = 0;
    int typ;    
    fread(&typ, sizeof(int), 1, fs);
    fread(&len, sizeof(int), 1, fs);
    for (int i = 0; i < len; i++) 
        for (int j = 0; j < len; j++) 
            fread(&rel[j][len - i - 1], sizeof(int), 1, fs);
    for (int i = 0; i < len; i++) 
        for (int j = 0; j < len; j++)
            fread(&remain[j][len - i - 1], sizeof(int), 1, fs);
    if (typ) {
        int turn;
        fread(&turn, sizeof(int), 1, fs);
        int num;
        for (int p = 0; p < 2; p++) {
            fread(&num, sizeof(int), 1, fs);
            for (int i = 0; i < num; i++) {
                fread(mem[cnt].name, sizeof(char) * 6, 6, fs);
                fread(&mem[cnt].x, sizeof(int), 1, fs);
                fread(&mem[cnt].y, sizeof(int), 1, fs);
                fread(&mem[cnt++].sc, sizeof(int), 1, fs);
            }
        }
        fread(&turn, sizeof(int), 1, fs);
    } else {
        int num;
        fread(&num, sizeof(int), 1, fs);
        for (int i = 0; i < num; i++) {
            fread(mem[cnt].name, sizeof(char) * 6, 6, fs);
            fread(&mem[cnt].x, sizeof(int), 1, fs);
            fread(&mem[cnt].y, sizeof(int), 1, fs);
            fread(&mem[cnt++].sc, sizeof(int), 1, fs);
        }
    }
    fclose(fs);
    fr = fopen("TEXT.txt", "w");
    fprintf(fr, "The length of the table is %d\n", len);
    fprintf(fr, "We have the total of %d cells\n", cnt);
    for (int i = 0; i < len; i++) 
        for (int j = 0; j < len; j++) {
            fprintf(fr, "{(%d, %d), ", i, j);
            if (rel[i][j] == ENERGY)
                fprintf(fr, "ENERGY = %d, ", remain[i][j]);
            else if (rel[i][j] == MITOSIS)
                fprintf(fr, "MITOSIS, ");
            else if (rel[i][j] == FORBIDDEN)
                fprintf(fr, "FORBIDDEN, ");
            else 
                fprintf(fr, "NORMAL, ");
            int find = 0;
            for (int k = 0; k < cnt; k++) 
                if (mem[k].x == i && mem[k].y == j) {
                    find = 1;
                    fprintf(fr, "occupied by %s with score of %d}\n", mem[k].name, mem[k].sc);
                    break;
                }
            if (!find)
                fprintf(fr, "not occupied}\n");
        }
    fclose(fr);
}