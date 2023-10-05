#include <stdio.h>

#define anz 10

double praemien(double betraege[], int anzahl, double grenze, double praemie);

int eingabe(double betraege[], int max);

double sum(double betraege[], int anzahl);

int main() {
    double arr[anz] = {0};
    double grenze, praemie, gesamt;
    int n;

    n = eingabe(arr, anz);
    printf("Untergrenze: ");
    scanf("%lf", &grenze);
    printf("Praemie: ");
    scanf("%lf", &praemie);

    printf("Summe vor Praemien: %.2f\n", sum(arr, n));
    gesamt = praemien(arr, n, grenze, praemie);
    printf("Praemien gesamt: %.2f\n", gesamt);
    printf("Summe nach Praemien: %.2f\n", sum(arr, n));

    return 0;
}

double praemien(double betraege[], int anzahl, double grenze, double praemie) {
    int cntPraemien = 0;

    for (int i = 0; i < anzahl; ++i) {
        if (betraege[i] >= grenze) {
            betraege[i] += praemie;
            cntPraemien++;
        }
    }

    return cntPraemien * praemie;
}

int eingabe(double betraege[], int max) {
    int cnt = 0;
    double n;
    for (int i = 0; i < max; ++i, ++cnt) {
        printf("Zahl %d: ", i + 1);
        scanf(" %lf", &n);
        if (n < 0)
            break;

        betraege[i] = n;
    }

    return cnt;
}

double sum(double betraege[], int anzahl) {
    double sum = 0;
    for (int i = 0; i < anzahl; ++i) {
        sum += betraege[i];
    }

    return sum;
}