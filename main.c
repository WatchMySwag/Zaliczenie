#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int opt;
    int poziom = 0;

    while ((opt = getopt(argc, argv, "l:")) != -1) {
        switch (opt) {
            case 'l':
                poziom = atoi(optarg);
            if (poziom < 1 || poziom > 3) {
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
        printf("Uzycie: %s -l [1-3]\n", argv[0]);
        printf("  -l  Wybor poziomu trudnosci (1: latwy, 2: sredni, 3: trudny)\n");
        return 1;
    }
    switch (poziom) {
        case 1:
            printf("Wybrales poziom latwy.\n");
        break;
        case 2:
            printf("Wybrales poziom sredni.\n");
        break;
        case 3:
            printf("Wybrales poziom trudny.\n");
        break;
    }

    return 0;
}

