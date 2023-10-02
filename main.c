#include <stdio.h>

void taxFree(double value);

void taxBound(double value);

void expense(double value);

static double credit = 100, expenses = 0, earnings = 0, totalTax = 0;

int main() {
    int numEarnings = 0, numExpenses = 0;
    double value;
    char type;

    while (1) {
        printf("\nGuthaben: %.2lf Euro\n", credit);
        printf("Typ: ");
        scanf("%c", &type);
        if (type == '=') {
            break;
        }

        printf("\nBetrag in Euro: ");
        scanf("%lf", &value);
        if (value < 0) {
            printf("Der Betrag kann nicht negativ sein.\n");
            continue;
        }

        switch (type) {
            case 'e':
                taxBound(value);
                numEarnings++;
                break;
            case 's':
                taxFree(value);
                numEarnings++;
                break;
            case 'k':
                expense(value);
                numExpenses++;
                break;
        }
    }

    printf("\nRestguthaben: %.2lf Euro\n", credit);
    printf("%d Einnahmen mit durchschnittlichem Wert %.2lf Euro\n", numEarnings, numEarnings == 0 ? 0 : earnings / numEarnings);
    printf("%d Ausgaben mit durchschnittlichem Wert %.2lf Euro\n", numExpenses, numExpenses == 0 ? 0 : expenses / numExpenses);
    printf("Gezahlte Steuern: %.2lf Euro\n", totalTax);

    return 0;
}

void taxFree(double value) {
    credit += value;
    earnings += value;
}


// 210 = 200 = 150

void taxBound(double value) {
    if (value <= 20) {
        taxFree(value);
        printf("Gezahlte Steuern: 0.00 Euro\n");
        return;
    }

    double tax = 0, tmp = value;

    if (value > 200) {
        tax += (value - 200) * 0.4;
        value -= value - 200;
    }

    if (value > 50) {
        tax += (value - 50) * 0.2;
        value -= value - 50;
    }

    if (value > 20) {
        tax += (value - 20) * 0.1;
    }

    printf("%lf", tmp);

    credit += tmp - tax;
    earnings += tmp - tax;
    totalTax += tax;

    printf("Gezahlte Steuern: %.2lf Euro\n", tax);
}

void expense(double value) {
    if (value > credit) {
        printf("Diese Kosten koennen nicht bezahlt werden.\n");
        return;
    }

    credit -= value;
    expenses += value;
}
