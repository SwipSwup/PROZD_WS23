#include <stdio.h>

#define INITIAL_CREDIT 100
#define CREDIT (INITIAL_CREDIT + earnings - expenses - taxes)

static double expenses = 0, earnings = 0, taxes = 0;

void calcTaxes(double value);

int expense(double value);

int main() {
    short cntEarnings = 0, cntExpenses = 0;
    double value;
    char type;

    while (1) {
        printf("\nGuthaben: %.2lf Euro", CREDIT);

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
                calcTaxes(value);
            case 's':
                earnings += value;
                cntEarnings++;
                break;
            case 'k':
                if (expense(value))
                    cntExpenses++;
                break;
        }
    }

    printf("\nRestguthaben: %.2lf Euro", CREDIT);
    printf("\n%d Einnahmen mit durchschnittlichem Wert %.2lf Euro", cntEarnings,
           cntEarnings == 0 ? 0 : (earnings - taxes) / cntEarnings);
    printf("\n%d Ausgaben mit durchschnittlichem Wert %.2lf Euro", cntExpenses,
           cntExpenses == 0 ? 0 : expenses / cntExpenses);
    printf("\nGezahlte Steuern: %.2lf Euro", taxes);

    return 0;
}

void calcTaxes(double value) {
    double tmpTax = 0;

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
    printf("\nGezahlte Steuern: %.2lf Euro", tmpTax);
}

int expense(double value) {
    if (value > CREDIT) {
        printf("\nDiese Kosten koennen nicht bezahlt werden.");
        return 0;
    }

    expenses += value;
    return 1;
}