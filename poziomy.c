#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "poziomy.h"

char **mines;
char **board;
void tworzenie_tab(int x, int y) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            board[i][j] = '-';
            mines[i][j] = '0';
        }
    }
}
void miny(int size, int size2, int miny, int wybrane_x, int wybrane_y) {
    int plant=0;
    while(plant!=miny) {
        int x = rand()%size;
        int y = rand()%size2;
        if (mines[x][y] == '0' && !(x == wybrane_x && y == wybrane_y)) {
            mines[x][y]='*';
            for (int dx = -1; dx <= 1; dx++) { //   majac kolumny 0 1 2 nasza bomba jest na 1 wiec musimy dojsc do wszystkich
                for (int dy = -1; dy <= 1; dy++) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && ny >= 0 && nx < size && ny < size2 && mines[nx][ny] != '*') {
                        mines[nx][ny]++;
                    }
                }
            }
            plant++;
        }
    }
}
void flaga(int x, int y) {
    if (board[x][y] == '-') board[x][y] = 'F'; // dodaj
    else if (board[x][y] == 'F') board[x][y] = '-'; // usun
}
