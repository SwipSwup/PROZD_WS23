#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MAX_SCHEDULE_LENGTH 10
#define VALID_APPOINTMENT_TYPES "fbp"
#define VALID_MENU_ACTIONS "ndlix"

//enum für alle verschiedenen types an terminen mit ihren zugehörigen chars
enum appointmentType
{
    FRIENDS = 'f',
    BUSINESS = 'b',
    PAUSE = 'p'
} typedef appointmentType;

//struct zum speicher der termin daten
struct appointment
{
    appointmentType type;
    int time;
    int duration;
} typedef appointment;

//gibt für jeden appointmentType den zugehörigen string zurück
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

    return "(NULL)";
}

//looped durch das schedule und gibt alle appointments aus
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
    //hilfsvariable um zu schauen, ob eine Terminkollision aufgetreten ist
    int hasCollided = 0;

    //looped durch das schedule und schaut ob der nächste termin mit dem bei i kollidiert. 
    //Wenn ja, wird die hilfsvariable auf 1 gesetzt (true)  
    for (int i = 0; i < length - 1; ++i)
    {
        if (schedule[i].time + schedule[i].duration > schedule[i + 1].time)
        {
            printf("\nEntweder Termin %d oder Termin %d sollte abgesagt werden.", i + 1, i + 2);
            hasCollided = 1;
        }
    }

    //Wenn die hilfsvariable 0 (false) ist, wird ausgegeben das keine Kollision vorkam.
    if (!hasCollided)
    {
        printf("\nDer Kalender hat keine Kollisionen!");
    }

    //looped durch das schedule und schaut, ob zwischen zwei hintereinanderliegende termine ungenutzte Zeit liegt.
    for (int i = 0; i < length - 1; ++i)
    {
        //TODO
        if (schedule[i].time + schedule[i].duration < schedule[i + 1].time)
        {
            printf("\nZwischen den Terminen %d und %d liegen %dh ungeplante Zeit.",
                   i + 1,
                   i + 2,
                   //TODO
                   schedule[i + 1].time - (schedule[i].time + schedule[i].duration)
            );
        }
    }

    //Zählt die AppointmentTypes im Schedule
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

//struct für die daten die beim Abfragen des user inputs notwendig sind
struct userInputParams
{
    //Was für ein input man braucht z.B.: "%d" für int
    char* inputType;
    //Die message die vorm abfragen ausgegeben werden soll
    char* message;
    //sollte nicht nötig sein aber die Angabe ist falsch und es muss einmal ohne "\n" ausgegeben werden
    char* errorMessage;

    //die größe des speichers für die daten z.B.: sizeof(int) für int
    int memSize;
    //extra daten die zum validieren benötigt werden
    void* validationData;
} typedef userInputParams;

//validiert einen type als character.
//Bsp.: bei den appointment types dürfen nur die chars 'f' 'b' 'p' eingegeben werden. Die validation data wäre somit "fbp"
int validateGenericTypeAsChar(const void* type, const void* types)
{
    return strchr((char*) types, *((char*) type)) != NULL;
}

//validiert, ob ein int sich zwischen zwei int befinden
//Bsp.: bei den uhrzeiten dürfen nur zahlen zwischen 8 und 22 uhr eingegeben werden. Die validation data wäre somit ein int array mit 8 und 22
int validateIntegerBoundsIncl(const void* number, const void* bounds)
{
    return *((int*) number) >= ((int*) bounds)[0] && *((int*) number) <= ((int*) bounds)[1];
}

//eine generische funktion die user input parameter und eine validations funktion nimmt.
//returned eine speicheradresse vom heap auf der sich die eingelesenen daten befinden
void* getUserInputWithValidation(const userInputParams params, int validate(const void*, const void*))
{
    void* memory = malloc(params.memSize);
    while (1)
    {
        printf("%s", params.message);
        scanf(params.inputType, memory);

        //ruft die validations funktion auf mit dem eingelesenen wert und den validation daten
        if (validate(memory, params.validationData))
        {
            return memory;
        }

        printf("%s", params.errorMessage);
    }
}

appointment createAppointment()
{
    appointment newAppointment;

    //Frag den User nach neuen Input
    void* mem = getUserInputWithValidation(
            //Erstellt user input parameter
            (userInputParams) {
                    " %c",
                    "\nGib einen Typen ein: Freunde (f), Geschaeftlich (b), Pause (p): ",
                    "\nUngueltige Eingabe!",
                    sizeof(char),
                    VALID_APPOINTMENT_TYPES
            },
            validateGenericTypeAsChar
    );
    //Castet den void Pointer zu nem char und den char dann als appointmentType
    newAppointment.type = (appointmentType) *((char*) mem);

    mem = getUserInputWithValidation(
            (userInputParams) {
                    " %d",
                    "\nGib eine Uhrzeit ein (8-21): ",
                    "\nUngueltige Eingabe!",
                    sizeof(int),
                    (int[]) {8, 21}
            },
            validateIntegerBoundsIncl
    );
    //Caste den void pointer zu nem int
    newAppointment.time = *((int*) mem);

    //Bereitet die Message fürs Abfragen der länge vor
    char preparedMessage[30];
    //sprintf formatiert einen string.
    sprintf(preparedMessage, "\nGib eine Dauer ein (1-%d): ", 22 - newAppointment.time);

    mem = getUserInputWithValidation(
            (userInputParams) {
                    " %d",
                    preparedMessage,
                    "\nUngueltige Eingabe!",
                    sizeof(int),
                    (int[]) {1, 22 - newAppointment.time}
            },
            validateIntegerBoundsIncl
    );
    //caste den void* zu nem int
    newAppointment.duration = *((int*) mem);

    //Lösche den void* aus dem heap
    free(mem);
    return newAppointment;
}

void addAppointment(struct appointment* schedule, int* length)
{
    if (*length == MAX_SCHEDULE_LENGTH)
    {
        printf("\nDer Kalender ist voll!");
        return;
    }

    appointment newAppointment = createAppointment();

    //Checkt, ob der Termin links von i kleiner als der neue Termin ist.
    //Wenn ja, wird der neue Termin an der Stelle i eingesetzt
    for (int i = *length; i >= 0; --i)
    {
        if (!i || schedule[i - 1].time < newAppointment.time)
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

    //Frag den user nach dem Index
    void* mem = getUserInputWithValidation(
            (userInputParams) {
                    " %d",
                    "",
                    "Ungueltige Eingabe!",
                    sizeof(int),
                    (int[]) {1, *length}
            },
            validateIntegerBoundsIncl
    );
    //Caste den void* zu nem int
    int index = *((int*) mem);
    free(mem);

    printf("\nTermin %d wurde geloescht!", index);
    //Schieb alle element ab dem index nach links
    for (int i = index - 1; i < *length - 1; ++i)
    {
        schedule[i] = schedule[i + 1];
    }
    (*length)--;
}
//TODO
enum menuAction
{
    NEW_APPOINTMENT = 'n',
    DELETE_APPOINTMENT = 'd',
    LIST_SCHEDULE = 'l',
    INFO_SCHEDULE = 'i',
    EXIT_PROGRAM = 'x'
} typedef menuAction;
//TODO
void programMenu(appointment* schedule, int* scheduleCount)
{
    void* mem = NULL;

    while (1)
    {
        //Frag den User nach Input
        mem = getUserInputWithValidation(
                (userInputParams) {
                        " %c",
                        "\nNeuen Termin (n), Termin loeschen (d), Termine auflisten (l), Informationen ausgeben (i), Programm beenden (x)\nAuswahl: ",
                        "\nUngueltige Eingabe!",
                        sizeof(char),
                        VALID_MENU_ACTIONS
                },
                validateGenericTypeAsChar
        );

        //Castet den void pointer zu nem menuAction und ruft dann die richtige Funktion auf
        switch ((menuAction) *((char*) mem))
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
                //Lösch den void pointer aus dem heap
                free(mem);
                return;
        }
    }
}

int main()
{
    appointment schedule[MAX_SCHEDULE_LENGTH];
    int scheduleCount = 0;

    programMenu(schedule, &scheduleCount);

    return 0;
}
