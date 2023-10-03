#include <stdio.h>

#define INITIAL_CREDIT 100

void taxFree(double value);

void taxBound(double value);

int expense(double value);

double getCredit();

static double expenses = 0, earnings = 0, taxes = 0;

int main() {
    int numEarnings = 0, numExpenses = 0;
    double value;
    char type;

    while (1) {
        printf("\nGuthaben: %.2lf Euro", getCredit());

        printf("\nTyp: ");
        scanf(" %c", &type);
        if (type == '=') {
            break;
        }

        printf("\nBetrag in Euro: ");
        scanf(" %lf", &value);
        if (value < 0) {
            printf("\nDer Betrag kann nicht negativ sein.");
            continue;
        }

        switch (type) {
            case 'e':
                printf("\n");
                taxBound(value);
                numEarnings++;
                break;
            case 's':
                taxFree(value);
                numEarnings++;
                break;
            case 'k':
                if (expense(value))
                    numExpenses++;
                break;
        }
    }

    printf("\nRestguthaben: %.2lf Euro", getCredit());
    printf("\n%d Einnahmen mit durchschnittlichem Wert %.2lf Euro", numEarnings,
           numEarnings == 0 ? 0 : (earnings - taxes) / numEarnings);
    printf("\n%d Ausgaben mit durchschnittlichem Wert %.2lf Euro", numExpenses,
           numExpenses == 0 ? 0 : expenses / numExpenses);
    printf("\nGezahlte Steuern: %.2lf Euro", taxes);

    return 0;
}

double getCredit() {
    return INITIAL_CREDIT + earnings - expenses - taxes;
}

void taxFree(double value) {
    earnings += value;
}

void taxBound(double value) {
    if (value <= 20) {
        taxFree(value);
        printf("Gezahlte Steuern: 0.00 Euro");
        return;
    }

    double tmpTax = 0;
    earnings += value;

    if (value > 200) {
        tmpTax += (value - 200) * 0.4;
        value -= value - 200;
    }

    if (value > 50) {
        tmpTax += (value - 50) * 0.2;
        value -= value - 50;
    }

    if (value > 20) {
        tmpTax += (value - 20) * 0.1;
    }

    taxes += tmpTax;
    printf("Gezahlte Steuern: %.2lf Euro", tmpTax);
}

int expense(double value) {
    if (value > getCredit()) {
        printf("\nDiese Kosten koennen nicht bezahlt werden.");
        return 0;
    }

    expenses += value;
    return 1;
}


