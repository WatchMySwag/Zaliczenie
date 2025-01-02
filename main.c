#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "pliki.h"
#include "poziomy.h"
#include <string.h>
int main(int argc, char *argv[]) {
    FILE *file = fopen("wyniki.txt", "r");
    if(file == NULL) {
        tworzenie();
    }
    fclose(file);
    srand(time(NULL));
    int opt;
    int poziom = 0;
    while ((opt = getopt(argc, argv, "l:")) != -1) {
        switch (opt) {
            case 'l':
                poziom = atoi(optarg);
                if (poziom < 1 || poziom > 4) {
                    printf("Blad: Poziom trudnosci musi byc od 1 do 3.\n");
                    return 1;
                }
                break;
            case '?':
                printf("Nieznana opcja: -%c\n", optopt);
                return 1;
        }
    }

    if (poziom == 0) {
        printf("Uzycie: %s -l [1-4]\n", argv[0]);
        printf("  -l  Wybor poziomu trudnosci (1: latwy, 2: sredni, 3: trudny, 4: wlasna mapa)\n");
        return 1;
    }

    switch (poziom) {
        case 1:
            printf("Wybrano poziom latwy.\n");
            break;
        case 2:
            printf("Wybrano poziom sredni.\n");
            break;
        case 3:
            printf("Wybrano poziom trudny.\n");
            break;
        case 4:
            printf("Wybrano wlasna mape.\n");
    }
    if(poziom == 1) {
        int x = 9;
        mines = (char **)malloc(x * sizeof(char *));
        board = (char **)malloc(x * sizeof(char *));
        for (int i = 0; i < x; i++) {
            mines[i] = (char *)malloc(x * sizeof(char));
            board[i] = (char *)malloc(x * sizeof(char));
        }
        int wynik = gra(x,x,10);
        char s[51];
        if(wynik!=0) {
            printf("Twoj wynik to: %d\nPodaj swoja nazwe skladajaca sie maksymalnie z 50 znakow: \n",wynik);
            scanf("%50s", s); //ograniczenie dla stringa - ciekawa opcja
            update(s,wynik);
        }
            wypisz();
    }
    if(poziom == 2) {
        int x = 16;
        mines = (char **)malloc(x * sizeof(char *));
        board = (char **)malloc(x * sizeof(char *));
        for (int i = 0; i < x; i++) {
            mines[i] = (char *)malloc(x * sizeof(char));
            board[i] = (char *)malloc(x * sizeof(char));
        }
        int wynik = gra(x,x,40);
        char s[51];
        wynik*=2;
        if(wynik!=0) {
            printf("Twoj wynik to: %d\nPodaj swoja nazwe skladajaca sie maksymalnie z 50 znakow: \n",wynik);
            scanf("%50s", s); //ograniczenie dla stringa - ciekawa opcja
            update(s,wynik);
        }
        wypisz();
    }
    if(poziom == 3) {
        int x = 16,y=30;
        mines = (char **)malloc(16 * sizeof(char *));
        board = (char **)malloc(16 * sizeof(char *));
        for (int i = 0; i < x; i++) {
            mines[i] = (char *)malloc(30 * sizeof(char));
            board[i] = (char *)malloc(30 * sizeof(char));
        }
        int wynik = gra(x,y,99);
        wynik*=3;
        char s[51];
        if(wynik!=0) {
            printf("Twoj wynik to: %d\nPodaj swoja nazwe skladajaca sie maksymalnie z 50 znakow: \n",wynik);
            scanf("%50s", s); //ograniczenie dla stringa - ciekawa opcja
            update(s,wynik);
        }
        wypisz();
    }
    if (poziom == 4) {
        //dokonczyc warunek ilosci min
        int a,b;
        int minty;
        while(1) {
            printf("Podaj wymiary planszy a x b:\na = ");
            scanf("%d",&a);
            printf("b = ");
            scanf("%d",&b);
            printf("Podaj ilosc min: ");
            scanf("%d", &minty);
            if(minty<=0 || a <=0 || b<=0) {
                printf("Jedna z podanych warosci jest ujemna,badz rowna 0, podaj wartosci jeszcze raz!\n");
            }
            else if(minty >= a*b) {
                printf("Ilosc min musi byc mniejsza niz wymiary planszy, twoj obecny wymiar planszy ma wartosc %d\n", a*b);
            }
            else {
                break;
            }
        }
        mines = (char **)malloc(a * sizeof(char *));
        board = (char **)malloc(a * sizeof(char *));
        for (int i = 0; i < a; i++) {
            mines[i] = (char *)malloc(b * sizeof(char));
            board[i] = (char *)malloc(b * sizeof(char));
        }
       int wynik = gra(a,b,minty);
        printf("Twoj wynik: %d\n Customowe gry nie wliczaja sie do rankingu. Natomiast jesli chcesz walczyc z najlepszymi rozpocznij gre jeszcze raz i wybierz poziom trudnosci od 1-3!", wynik);
    }
    return 0;
}

