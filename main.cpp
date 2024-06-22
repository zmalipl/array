#include <cstdio>
#include <cstdlib>
#include <ctime>

// Deklaracje funkcji
void displayArray(int *array, int size);
float calcAverage(int *array, int size);
int calcMin(int *array, int size);
int calcMax(int *array, int size);
void fetchData(int *array, int size);
void editValue(int *array, int size);
void saveToFile(int *array, int size, const char *filename);
void readFromFile(int *array, int size, const char *filename);
int *resizeArray(int *array, int oldSize, int newSize);

// Definicje funkcji
void displayArray(int *array, int size) {
    for (int i = 0; i < size; ++i) {
        printf("*(array + %d) = %d\n", i, *(array + i));
    }
}

float calcAverage(int *array, int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += *(array + i);
    }
    return static_cast<float>(sum) / size;
}

int calcMin(int *array, int size) {
    int min = *array;
    for (int i = 1; i < size; ++i) {
        if (*(array + i) < min)
            min = *(array + i);
    }
    return min;
}

int calcMax(int *array, int size) {
    int max = *array;
    for (int i = 1; i < size; ++i) {
        if (*(array + i) > max)
            max = *(array + i);
    }
    return max;
}

void fetchData(int *array, int size) {
    for (int i = 0; i < size; ++i) {
        printf("*(array + %d) = ", i);
        scanf("%d", (array + i));
    }
}

void editValue(int *array, int size) {
    int index, newValue;
    printf("Podaj indeks elementu, ktory chcesz edytowac: ");
    scanf("%d", &index);
    if (index >= 0 && index < size) {
        printf("Podaj nowa wartosc: ");
        scanf("%d", &newValue);
        array[index] = newValue;
        printf("Zmieniono wartosc elementu o indeksie %d na %d\n", index, newValue);
    } else {
        printf("Niepoprawny indeks!\n");
    }
}

void saveToFile(int *array, int size, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        for (int i = 0; i < size; ++i) {
            fprintf(file, "%d\n", array[i]);
        }
        fclose(file);
        printf("Dane zapisane do pliku \"%s\".\n", filename);
    } else {
        printf("Nie udalo sie otworzyc pliku do zapisu.\n");
    }
}

void readFromFile(int *array, int size, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        for (int i = 0; i < size; ++i) {
            if (fscanf(file, "%d", &array[i]) != 1) {
                printf("Blad odczytu danych z pliku.\n");
                break;
            }
        }
        fclose(file);
        printf("Dane odczytane z pliku \"%s\".\n", filename);
    } else {
        printf("Nie udalo sie otworzyc pliku do odczytu.\n");
    }
}

int *resizeArray(int *array, int oldSize, int newSize) {
    int *newArray = (int *)realloc(array, newSize * sizeof(int));
    if (newArray == NULL) {
        printf("Blad alokacji pamieci!\n");
        return array;
    } else {
        if (newSize > oldSize) {
            for (int i = oldSize; i < newSize; ++i) {
                newArray[i] = 0;
            }
        }
        printf("Tablica zmieniona na rozmiar %d.\n", newSize);
        return newArray;
    }
}

int main() {
    int *array;
    int size;
    int choice;

    printf("Podaj rozmiar tablicy: ");
    scanf("%d", &size);

    array = (int *)malloc(size * sizeof(int));

    if (array == NULL) {
        printf("Blad alokacji pamieci!\n");
        return 1;
    }

    srand(time(NULL));
    for (int i = 0; i < size; ++i) {
        array[i] = (rand() % 100) + 1;
    }

    do {
        printf("\nMenu:\n");
        printf("1. Wyswietl tablice\n");
        printf("2. Oblicz srednia\n");
        printf("3. Znajdz minimum\n");
        printf("4. Znajdz maksimum\n");
        printf("5. Wprowadz dane\n");
        printf("6. Edytuj pojedyncza wartosc\n");
        printf("7. Zapisz dane do pliku\n");
        printf("8. Odczytaj dane z pliku\n");
        printf("9. Zmien rozmiar tablicy\n");
        printf("10. Wyjdz\n");
        printf("Wybierz opcje: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("\nTablica:\n");
            displayArray(array, size);
            break;
        case 2:
            printf("\nSrednia wynosi: %f\n", calcAverage(array, size));
            break;
        case 3:
            printf("\nMinimum wynosi: %d\n", calcMin(array, size));
            break;
        case 4:
            printf("\nMaksimum wynosi: %d\n", calcMax(array, size));
            break;
        case 5:
            printf("\nWprowadz nowe dane:\n");
            fetchData(array, size);
            break;
        case 6:
            editValue(array, size);
            break;
        case 7:
            saveToFile(array, size, "dane.txt");
            break;
        case 8:
            readFromFile(array, size, "dane.txt");
            break;
        case 9: {
            int newSize;
            printf("Podaj nowy rozmiar tablicy: ");
            scanf("%d", &newSize);
            array = resizeArray(array, size, newSize);
            size = newSize;
            break;
        }
        case 10:
            printf("\nWyjscie...\n");
            break;
        default:
            printf("\nNiepoprawny wybor!\n");
        }
    } while (choice != 10);

    free(array);

    return 0;
}
