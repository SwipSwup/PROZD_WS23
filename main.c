#include <stdio.h>

// Definiere das Startkapital
#define INITIAL_CREDIT 100
// Definiere das Kapital aus dem Startkapital, dem Gewinn, den Ausgaben und den steuern.
#define CREDIT (INITIAL_CREDIT + earnings - expenses - taxes)

// Global variablen zum Speichern der Ausgaben, des Gewinns und den Steuern
double expenses = 0, earnings = 0, taxes = 0;

void calcTaxes(double value);

int expense(double value);

int main() {
    // Zählvariablen der Einnahmen und Ausgaben für die statistik.
    short cntEarnings = 0, cntExpenses = 0;
    double value;
    char type;

    // Endlosschleife für die Eingabe
    while (1) {
        printf("\nGuthaben: %.2lf Euro", CREDIT);

        // Eingabe des typen. Bricht die schleife ab, wenn der type '=' ist.
        printf("\nTyp: ");
        scanf(" %c", &type);
        if (type == '=') {
            break;
        }

        // Eingabe des Betrags. Wenn der Wert unter 0 ist, wird die Eingabe wiederholt.
        printf("\nBetrag in Euro: ");
        scanf(" %lf", &value);
        if (value < 0) {
            printf("\nDer Betrag kann nicht negativ sein.");
            continue;
        }

        // Abfragen der types und ausführen der korrekten Funktionen
        switch (type) {
            case 'e':
                // Berechnet die steuern von value.
                // Fällt durch zum nächsten case da der rest ident mit der steuerfreien Eingabe ist
                calcTaxes(value);
            case 's':
                // Addiere den value zu den earnings dazu und erhöhe den Zähler für die Statistik
                earnings += value;
                cntEarnings++;
                break;
            case 'k':
                // Checkt, ob die expense Funktion erfolgreich war und wenn ja, erhöhe den Zähler für die Statistik
                if (expense(value))
                    cntExpenses++;
                break;
        }
    }

    // Gib die statistik aus
    printf("\nRestguthaben: %.2lf Euro", CREDIT);
    // Checkt, ob es Einnahmen od Ausgaben gab, um die division durch 0 zu vermeiden
    printf("\n%d Einnahmen mit durchschnittlichem Wert %.2lf Euro", cntEarnings,
           cntEarnings == 0 ? 0 : (earnings - taxes) / cntEarnings);
    printf("\n%d Ausgaben mit durchschnittlichem Wert %.2lf Euro", cntExpenses,
           cntExpenses == 0 ? 0 : expenses / cntExpenses);
    printf("\nGezahlte Steuern: %.2lf Euro", taxes);

    return 0;
}

void calcTaxes(double value) {
    double tmpTax = 0;

    // Arbeitet sich von hinten nach vorne durch und berechnet sie die Steuern für den value
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

    // Addiere die berechneten Steuern zu den Gesamtsteuern und gibt diese aus.
    taxes += tmpTax;
    printf("\nGezahlte Steuern: %.2lf Euro", tmpTax);
}

int expense(double value) {
    // Checkt, ob genug Kapital vorhanden ist. Wenn ja, addiere value zu den Gesamtkosten und wenn nicht, gib eine Fehlermeldung aus.
    // Wenn genug Kapital vorhanden ist, wird 1 (true) zurückgegeben und wenn nicht 0 (false);
    if (value > CREDIT) {
        printf("\nDiese Kosten koennen nicht bezahlt werden.");
        return 0;
    }

    expenses += value;
    return 1;
}