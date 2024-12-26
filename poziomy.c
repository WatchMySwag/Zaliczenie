#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "poziomy.h"

#include "pliki.h"

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
    int plant = 0;
    while (plant != miny) {
        int x = rand() % size;
        int y = rand() % size2;

        // Umieszczamy minę wszędzie, z wyjątkiem wybranej komórki (wybrane_x, wybrane_y)
        if (!(x == wybrane_x && y == wybrane_y)) {
            mines[x][y] = '*';  // Umieszczamy minę

            // Zaktualizuj otaczające komórki
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && ny >= 0 && nx < size && ny < size2 && mines[nx][ny] != '*') {
                        mines[nx][ny]++;  // Zwiększamy liczbę min wokół tej komórki
                    }
                }
            }
            plant++;  // Zwiększamy liczbę umieszczonych min
        }
    }
}




void flaga(int x, int y) {
    if (board[x][y] == '-') board[x][y] = 'F'; // dodaj
    else if (board[x][y] == 'F') board[x][y] = '-'; // usun
}
void wypisz_tablice(int x, int y) {
    printf("   ");
    for (int j = 0; j < y; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    for (int i = 0; i < x; i++) {
        printf("%2d ", i);
        for (int j = 0; j < y; j++) {
            printf("%2c ", board[i][j]);
        }
        printf("\n");
    }
}
void odkrywanie(int sizex, int sizey, int x, int y) {
    if (x >= 0 && y >= 0 && x < sizex && y < sizey && board[x][y] == '-') {
        board[x][y] = mines[x][y];
        if (mines[x][y] == '0') {
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && ny >= 0 && nx < sizex && ny < sizey && board[nx][ny] == '-') {
                        odkrywanie(sizex, sizey, nx, ny); //odkrywanie sasiednich rekrurencyjnie a co
                    }
                }
            }
        }
    }
}
void wypisz_miny(int x, int y) {
    printf("   ");
    for (int j = 0; j < y; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 0; i < x; i++) {
        printf("%2d ", i);
        for (int j = 0; j < y; j++) {
            if (board[i][j] == '-' && mines[i][j]!='*') {
                printf("%2c ", '-');
            } else if (board[i][j] == 'F' && mines[i][j]!='*' ) {
                printf("%2c ", 'F');
            } else if (mines[i][j] == '*') {
                printf("%2c ", '*');
            } else {
                printf("%2c ", board[i][j]);
            }
        }
        printf("\n");
    }
}

int gra(int sizex, int sizey, int mines_count) {
    int wynik = 0;
    int maks_odsloniete = (sizex * sizey) - mines_count;
    int x, y;
    char command;
    tworzenie_tab(sizex, sizey);
    while (1) {
        wypisz_tablice(sizex, sizey);
        printf("Podaj poczatkowe wspolrzedne x (0-%d): ", sizex - 1);
        scanf("%d", &x);
        printf("Podaj poczatkowe wspolrzedne y (0-%d): ", sizey - 1);
        scanf("%d", &y);

        if (x >= 0 && x < sizex && y >= 0 && y < sizey) {
            break;
        } else {
            printf("Nieprawidlowe wspolrzedne! Sprobuj ponownie.\n");
        }
    }
    miny(sizex, sizey, mines_count, x, y);
   wypisz_miny(sizex, sizey);

    odkrywanie(sizex, sizey, x, y);

    while (1) {
        wypisz_tablice(sizex, sizey);
        int odkryte_pola = 0;
        for (int i = 0; i < sizex; i++) {
            for (int j = 0; j < sizey; j++) {
                if (board[i][j] != '-' && board[i][j] != 'F') {
                    odkryte_pola++;
                }
            }
        }
        if (odkryte_pola == maks_odsloniete) {
            printf("Gratulacje! Wygrales!\n");
            wypisz_tablice(sizex, sizey);
            wynik = odkryte_pola;
            break;
        }
        printf("Wybierz akcje: (1) Odkryj pole (2) Postaw flage (0) Zakoncz gre\n");
        scanf(" %c", &command);

        if (command == '0') {
            printf("Gra zakonczona. Wynik: %d\n", wynik);
            break;
        }
        while (1) {
            printf("Podaj wspolrzedne x (0-%d): ", sizex - 1);
            scanf("%d", &x);
            printf("Podaj wspolrzedne y (0-%d): ", sizey - 1);
            scanf("%d", &y);

            if (x >= 0 && x < sizex && y >= 0 && y < sizey) {
                break;
            } else {
                printf("Nieprawidlowe wspolrzedne! Sprobuj ponownie.\n");
            }
        }
        if (command == '1') {
            if (board[x][y] != '-') {
                printf("To pole jest juz odkryte lub oznaczone flaga!\n");
                continue;
            }
            if (mines[x][y] == '*') {
                printf("Trafiles na mine! Koniec gry.\n");
                wypisz_miny(sizex, sizey);
                wynik = odkryte_pola;
                break;
            }
            odkrywanie(sizex, sizey, x, y);
        } else if (command == '2') {
            flaga(x, y);
        } else {
            printf("Nieznana komenda. Sprobuj ponownie.\n");
        }
    }
    return wynik;
}




