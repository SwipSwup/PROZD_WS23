#include <stdio.h>
#include <string.h>

enum dateType
{
    friends = 'f',
    business = 'b',
    pause = 'p'
} typedef dateType;

enum action
{
    new = 'n',
    delete = 'd',
    list = 'l',
    info = 'i',
    exit = 'x'
} typedef action;

struct appointment
{
    dateType type;
    int time;
    int duration;
} typedef appointment;

char* getDateTypeAsString(dateType type)
{
    switch (type)
    {
        case friends:
            return "Freunde";
        case business:
            return "Geschaeftlich";
        case pause:
            return "Pause";
    }

    return "";
}

action getNextAction()
{
    char tmp;
    printf("\nAuswahl: ");
    scanf(" %c", &tmp);
    return (action) tmp;
}

void printAppointments(struct appointment* schedule, int length)
{
    for (int i = 0; i < length; ++i)
    {
        printf("\n%d: %s: %d Uhr, Dauer %dh",
               i + 1,
               getDateTypeAsString(schedule[i].type),
               schedule[i].time,
               schedule[i].duration
        );
    }
}

void printInformation(struct appointment* schedule, int length)
{
    if (length == 0)
    {
        printf("\nDer Kalender hat keine Kollisionen!");
    }

    for (int i = 0; i < length; ++i)
    {
        if (i == length - 1)
        {
            printf("\nDer Kalender hat keine Kollisionen!");
            break;
        }

        if (schedule[i].time + schedule[i].duration > schedule[i + 1].time)
        {
            printf("\nEntweder Termin %d oder Termin %d sollte abgesagt werden.", i + 1, i + 2);
            break;
        }
    }

    for (int i = 0; i < length - 1; ++i)
    {
        if (schedule[i].time + schedule[i].duration < schedule[i + 1].time)
        {
            printf("\nZwischen den Terminen %d und %d liegen %dh ungeplante Zeit.",
                   i + 1,
                   i + 2,
                   schedule[i + 1].time - (schedule[i].time + schedule[i].duration)
            );
        }
    }

    int friendCount = 0, businessCount = 0, pauseCount = 0;
    for (int i = 0; i < length; ++i)
    {
        switch (schedule[i].type)
        {
            case friends:
                friendCount++;
                break;
            case business:
                businessCount++;
                break;
            case pause:
                pauseCount++;
                break;
        }
    }

    printf("\nSie haben %d Geschaeftstermin(e), %d Termin(e) mit Freunden und %d Pause(n) in Ihrem Kalender.",
           businessCount,
           friendCount,
           pauseCount
    );
}

appointment createAppointment()
{
    appointment newAppointment;
    char tempType;

    while (1)
    {

        printf("\nGib einen Typen ein: Freunde (f), Geschaeftlich (b), Pause (p): ");
        scanf(" %c", &tempType);

        if (strchr("fbp", tempType) == NULL)
        {
            printf("\nUngueltige Eingabe!");
            continue;
        }
        newAppointment.type = (dateType) tempType;
        break;
    }

    while (1)
    {
        printf("\nGib eine Uhrzeit ein (8-21): ");
        scanf(" %d", &newAppointment.time);

        if ((newAppointment.time < 8 || newAppointment.time > 21))
        {
            printf("\nUngueltige Eingabe!");
            continue;
        }
        break;
    }

    while (1)
    {
        printf("\nGib eine Dauer ein (1-%d): ", 22 - newAppointment.time);
        scanf(" %d", &newAppointment.duration);

        if (newAppointment.duration < 1 || newAppointment.duration > 22 - newAppointment.time)
        {
            printf("\nUngueltige Eingabe!");
            continue;
        }
        break;
    }

    return newAppointment;
}

void addAppointment(struct appointment* schedule, int* length)
{
    if (*length == 10)
    {
        printf("\nDer Kalender ist voll!");
        return;
    }

    appointment newAppointment = createAppointment();

    for (int i = *length; i >= 0; --i)
    {
        if (!i || schedule[i - 1].time <= newAppointment.time)
        {
            schedule[i] = newAppointment;
            (*length)++;
            return;
        }

        schedule[i] = schedule[i - 1];
    }
}

void deleteAppointment(struct appointment* schedule, int* length)
{
    if (*length == 0)
    {
        printf("\nDer Kalender ist leer!");
        return;
    }

    int index;
    printAppointments(schedule, *length);
    printf("\nWelchen dieser Termine moechten Sie loeschen? (1-%d): ", *length);
    while (1)
    {
        scanf(" %d", &index);
        if (index < 1 || index > *length)
        {
            printf("Ungueltige Eingabe!");
            continue;
        }
        break;
    }

    printf("\nTermin %d wurde geloescht!", index);

    for (int i = index - 1; i < *length - 1; ++i)
    {
        schedule[i] = schedule[i + 1];
    }
    (*length)--;
}

int main()
{
    appointment schedule[10];
    int scheduleCount = 0;
    action nextAction;

    do
    {
        printf("\nNeuen Termin (n), Termin loeschen (d), Termine auflisten (l), Informationen ausgeben (i), Programm beenden (x)");

        nextAction = getNextAction();

        switch (nextAction)
        {
            case new:
                addAppointment(schedule, &scheduleCount);
                break;
            case delete:
                deleteAppointment(schedule, &scheduleCount);
                break;
            case list:
                printAppointments(schedule, scheduleCount);
                break;
            case info:
                printInformation(schedule, scheduleCount);
                break;
            case exit:
                break;
            default:
                printf("\nUngueltige Eingabe!");
        }
    } while (nextAction != exit);

    return 0;
}
