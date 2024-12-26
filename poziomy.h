#ifndef POZIOMY_H
#define POZIOMY_H
extern char **mines;   // zmienne globalne TRZEBA ICH PAMIEC ZALOKOWAC W MAIN
extern char **board;
void tworzenie_tab(int x, int y);
void miny(int size, int size2, int miny, int wybrane_x, int wybrane_y);
void flaga(int x, int y);
void wypisz_tablice(int x, int y);
void odkrywanie(int sizex, int sizey, int x, int y);
int gra (int sizex, int sizey, int mines); //trzeba dodac informacje o usuwaniu flagi
void wypisz_miny(int x, int y);
#endif
