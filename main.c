#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define SCHEDULE_LENGTH 10
#define VALID_APPOINTMENT_TYPES "fbp"
#define VALID_MENU_ACTIONS "ndlix"

enum appointmentType
{
    FRIENDS = 'f',
    BUSINESS = 'b',
    PAUSE = 'p'
} typedef appointmentType;

struct appointment
{
    appointmentType type;
    int time;
    int duration;
} typedef appointment;

char* getAppointmentTypeAsString(appointmentType type)
{
    switch (type)
    {
        case FRIENDS:
            return "Freunde";
        case BUSINESS:
            return "Geschaeftlich";
        case PAUSE:
            return "Pause";
    }

    return "";
}

void printAppointments(struct appointment* schedule, int length)
{
    for (int i = 0; i < length; ++i)
    {
        printf("\n%d: %s: %d Uhr, Dauer %dh",
               i + 1,
               getAppointmentTypeAsString(schedule[i].type),
               schedule[i].time,
               schedule[i].duration
        );
    }
}

void printInformation(struct appointment* schedule, int length)
{
    int hasCollided = 0;

    for (int i = 0; i < length - 1; ++i)
    {
        if (schedule[i].time + schedule[i].duration > schedule[i + 1].time)
        {
            printf("\nEntweder Termin %d oder Termin %d sollte abgesagt werden.", i + 1, i + 2);
            hasCollided = 1;
            break;
        }
    }

    if (!hasCollided)
    {
        printf("\nDer Kalender hat keine Kollisionen!");
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

    int friendAppointmentCnt = 0, businessAppointmentCnt = 0, pauseAppointmentCnt = 0;
    for (int i = 0; i < length; ++i)
    {
        switch (schedule[i].type)
        {
            case FRIENDS:
                friendAppointmentCnt++;
                break;
            case BUSINESS:
                businessAppointmentCnt++;
                break;
            case PAUSE:
                pauseAppointmentCnt++;
                break;
        }
    }

    printf("\nSie haben %d Geschaeftstermin(e), %d Termin(e) mit Freunden und %d Pause(n) in Ihrem Kalender.",
           businessAppointmentCnt,
           friendAppointmentCnt,
           pauseAppointmentCnt
    );
}

struct userInputParams
{
    char* inputType;
    char* message;
    //sollte nicht nötig sein aber die Angabe ist falsch und es muss einmal ohne "\n" ausgegeben werden
    char* errorMessage;

    int bufferSize;
    void* validationData;
} typedef userInputParams;

int validateGenericTypeAsChar(const void* type, const void* types)
{
    return strchr(types, *((char*) type)) != NULL;
}

int validateIntegerBoundsIncl(const void* number, const void* bounds)
{
    return *((int*) number) >= ((int*) bounds)[0] && *((int*) number) <= ((int*) bounds)[1];
}

void* getUserInputWithValidation(const userInputParams params, int validate(const void*, const void*))
{
    void* buffer = malloc(params.bufferSize);
    while (1)
    {
        printf("%s", params.message);
        scanf(params.inputType, buffer);

        if (!validate(buffer, params.validationData))
        {
            printf("%s", params.errorMessage);
            continue;
        }
        return buffer;
    }
}

appointment createAppointment()
{
    appointment newAppointment;

    void* buffer = getUserInputWithValidation(
            (userInputParams) {
                    " %c",
                    "\nGib einen Typen ein: Freunde (f), Geschaeftlich (b), Pause (p): ",
                    "\nUngueltige Eingabe!",
                    sizeof(char),
                    VALID_APPOINTMENT_TYPES
            },
            validateGenericTypeAsChar
    );
    newAppointment.type = (appointmentType) *((char*) buffer);

    buffer = getUserInputWithValidation(
            (userInputParams) {
                    " %d",
                    "\nGib eine Uhrzeit ein (8-21): ",
                    "\nUngueltige Eingabe!",
                    sizeof(int),
                    (int[]) {8, 21}
            },
            validateIntegerBoundsIncl
    );
    newAppointment.time = *((int*) buffer);

    char temp[30];
    sprintf(temp, "\nGib eine Dauer ein (1-%d): ", 22 - newAppointment.time);

    buffer = getUserInputWithValidation(
            (userInputParams) {
                    " %d",
                    temp,
                    "\nUngueltige Eingabe!",
                    sizeof(int),
                    (int[]) {1, 22 - newAppointment.time}
            },
            validateIntegerBoundsIncl
    );
    newAppointment.duration = *((int*) buffer);

    free(buffer);
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

    printAppointments(schedule, *length);
    printf("\nWelchen dieser Termine moechten Sie loeschen? (1-%d): ", *length);

    void* buffer = getUserInputWithValidation(
            (userInputParams) {
                    " %d",
                    "",
                    "Ungueltige Eingabe!",
                    sizeof(int),
                    (int[]) {1, *length}
            },
            validateIntegerBoundsIncl
    );
    int index = *((int*) buffer);
    free(buffer);

    printf("\nTermin %d wurde geloescht!", index);
    for (int i = index - 1; i < *length - 1; ++i)
    {
        schedule[i] = schedule[i + 1];
    }
    (*length)--;
}

enum menuAction
{
    NEW_APPOINTMENT = 'n',
    DELETE_APPOINTMENT = 'd',
    LIST_SCHEDULE = 'l',
    INFO_SCHEDULE = 'i',
    EXIT_PROGRAM = 'x'
} typedef menuAction;

void programMenu(appointment* schedule, int* scheduleCount)
{
    void* userInputBuffer = NULL;

    while (1)
    {
        userInputBuffer = getUserInputWithValidation(
                (userInputParams) {
                        " %c",
                        "\nNeuen Termin (n), Termin loeschen (d), Termine auflisten (l), Informationen ausgeben (i), Programm beenden (x)\nAuswahl: ",
                        "\nUngueltige Eingabe!",
                        sizeof(char),
                        VALID_MENU_ACTIONS
                },
                validateGenericTypeAsChar
        );

        switch ((menuAction) *((char*) userInputBuffer))
        {
            case NEW_APPOINTMENT:
                addAppointment(schedule, scheduleCount);
                break;
            case DELETE_APPOINTMENT:
                deleteAppointment(schedule, scheduleCount);
                break;
            case LIST_SCHEDULE:
                printAppointments(schedule, *scheduleCount);
                break;
            case INFO_SCHEDULE:
                printInformation(schedule, *scheduleCount);
                break;
            case EXIT_PROGRAM:
                free(userInputBuffer);
                return;
        }
    }
}

int main()
{
    appointment schedule[SCHEDULE_LENGTH];
    int scheduleCount = 0;

    programMenu(schedule, &scheduleCount);

    return 0;
}
