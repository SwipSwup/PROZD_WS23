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

    printf("\nGib einen Typen ein: Freunde (f), Geschaeftlich (b), Pause (p): ");
    scanf(" %c", &tempType);

    printf("\nGib eine Uhrzeit ein (8-21): ");
    scanf(" %d", &newAppointment.time);

    printf("\nGib eine Dauer ein (1-%d): ", 22 - newAppointment.time);
    scanf(" %d", &newAppointment.duration);

    if ((newAppointment.time < 8 || newAppointment.time > 21)
        || strchr("fbp", tempType) != NULL
        || (newAppointment.duration < 1 || newAppointment.duration < 22 - newAppointment.time))
    {
        printf("Ungeultige Eingabe!");
        return createAppointment();
    }
    newAppointment.type = tempType;

    return newAppointment;
}

void printAppointments(struct appointment* schedule, int length)
{
    for (int i = 0; i < length; ++i)
    {
        printf("\n%d: %s: %dUhr, Dauer %dh",
               i + 1,
               getDateTypeAsString(schedule->type),
               schedule->time,
               schedule->duration
        );
    }
}

void addAppointment(struct appointment* schedule, int* length)
{
    if(*length == 10) {
        printf("Der Kalender ist voll!");
        return;
    }

    appointment newAppointment = createAppointment();
    for (int i = *length - 1; i >= 0; --i)
    {
        if(i == 0) {
            schedule[i] = newAppointment;
            return;
        }
        schedule[i + 1] = schedule[i];
    }

}

int main()
{
    char input;
    dateType type;
    appointment appointments[10];
    int appointmentCount;

    while (1)
    {

    }

    return 0;
}
