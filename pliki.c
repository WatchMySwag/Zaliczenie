#include <stdio.h>
#include "pliki.h"

void tworzenie() {
    FILE *file = fopen("wyniki.txt", "w");
    if (file == NULL) {
        perror("Błąd przy otwieraniu pliku");
        return;
    }
    fprintf(file, "Miejsce Wynik Nazwa\n");
    fclose(file);
    printf("jestem");
}
