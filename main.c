#include <stdio.h>
#include <string.h>

enum dateType
{
    friends = 'f',
    business = 'b',
    pause = 'p'
} typedef dateType;

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
            return "freunde";
        case business:
            return "Geschäftlich";
        case pause:
            return "Pause";
    }
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
            printf("Ungeultige Eingabe!");
            continue;
        }
        newAppointment.type = tempType;

        printf("\nGib eine Uhrzeit ein (8-21): ");
        scanf(" %d", &newAppointment.time);

        if ((newAppointment.time < 8 || newAppointment.time > 21))
        {
            printf("Ungeultige Eingabe!");
            continue;
        }

        printf("\nGib eine Dauer ein (1-%d): ", 22 - newAppointment.time);
        scanf(" %d", &newAppointment.duration);

        if (newAppointment.duration < 1 || newAppointment.duration > 22 - newAppointment.time)
        {
            printf("Ungeultige Eingabe!");
            continue;
        }
        break;
    }

    return newAppointment;
}

void printAppointments(struct appointment* schedule, int length)
{
    for (int i = 0; i < length; ++i)
    {
        printf("\n%d: %s: %dUhr, Dauer %dh",
               i + 1,
               getDateTypeAsString(schedule[i].type),
               schedule[i].time,
               schedule[i].duration
        );
    }
}

void addAppointment(struct appointment* schedule, int* length)
{
    if (*length == 10)
    {
        printf("Der Kalender ist voll!");
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

int main()
{
    appointment appointments[10];
    int appointmentCount = 0;
    char prozess;

    while(1) {

    }

    return 0;
}
