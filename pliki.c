#include <stdio.h>
#include "pliki.h"
#include <string.h>
#define max_len 50
#define top 5
typedef struct {
    int wynik;
    char nazwa[max_len];
    int nr;
}Gracz;
void tworzenie() {
    FILE *file = fopen("wyniki.txt", "w");
    //bedzie trzeba dodac napisa tablica wynikow
    fprintf(file,"1    NONE    0\n2    NONE    0\n3    NONE    0\n4    NONE    0\n5    NONE    0");
    fclose(file);
}
void update(char s[], int rating) {
    FILE *przed = fopen("wyniki.txt", "r");
    FILE *po = fopen("temp.txt", "w");
    Gracz gracze[top];
    int i=0;
    while (fscanf(przed, "%d %s %d", &gracze[i].nr, gracze[i].nazwa, &gracze[i].wynik) != EOF) {
        i++;
    }
    if(rating > gracze[top-1].wynik) {
        strcpy(gracze[top - 1].nazwa, s); //przypisanie stringa do stringa -> w C normalnie to error
        gracze[top-1].wynik=rating;
    }
    for(int i=0;i<top-1;i++) {
        for(int j=i+1;j<top;j++) {
            if(gracze[i].wynik<gracze[j].wynik) {
                Gracz tmp = gracze[j];
                gracze[j]=gracze[i];
                gracze[i]=tmp;
            }
        }
    }
    for (int j = 0; j < top; j++) {
        fprintf(po, "%d %s %d\n", j + 1, gracze[j].nazwa, gracze[j].wynik);
    }
    fclose(przed);
    fclose(po);

    //przenoszenie danych
    remove("wyniki.txt");  // usuwanie pliku obecnego
    rename("temp.txt", "wyniki.txt");//zamiana nazwy
}
void wypisz() {
    FILE *file = fopen("wyniki.txt","r");
    Gracz gracze[top];
    int i=0;
    while (fscanf(file, "%d %s %d", &gracze[i].nr, gracze[i].nazwa, &gracze[i].wynik) != EOF) {
        i++;
    }
    printf("    LEADERBOARD\n");
    for(int i=0;i<top;i++) {
        printf("%d   %s   %d\n",gracze[i].nr,gracze[i].nazwa,gracze[i].wynik);
    }
    fclose(file);
}
