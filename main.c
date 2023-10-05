#include <stdio.h>

int encode(int h, int m);

int read();

int hours(int t);

int minutes(int t);

void print(int t);

int add(int t1, int t2);

int total_minutes(int t);

/* D O N T   T O U C H   T H I S */
void Test_1() {
    int h, m;
    printf("h: ");
    scanf("%d", &h);
    printf("m: ");
    scanf("%d", &m);
    printf("encoded: %04d", encode(h, m));
}

void Test_2() {
    printf("read: %04d", read());
}

void Test_3() {
    int t;
    printf("hours: %02d\n", hours(t = read()));
    printf("minutes: %02d\n", minutes(t));
}

void Test_4() {
    print(read());
}

void Test_5() {
    int t1 = read();
    int t2 = read();
    printf("add: ");
    print(t1);
    printf(" + ");
    print(t2);
    printf(" = ");
    print(add(t1, t2));
}

void Test_6() {
    int t = read();
    printf("read: %d\n", total_minutes(t));
}

int main() {
    /* Input */
    int num;
    /* List of all available tests */
    void (*tests[])() = { Test_1, Test_2, Test_3, Test_4, Test_5, Test_6 };
    int num_of_tests = (int)(sizeof(tests) / sizeof(void (*)()));

    /* Read test number */
    printf("Test #: ");
    scanf("%d", &num);

    /* Check valid range */
    if (num >= 1 && num <= num_of_tests) {
        /* Call the selected test */
        printf("Executing Test_%d.\n", num);
        tests[num - 1]();
    } else {
        /* Print error */
        printf("Invalid test number!");
    }

    return 0;
}

int encode(int h, int m) {
    return h * 100 + m;
}

int read() {
    int h, m;

    printf("hours: ");
    scanf(" %d", &h);

    printf("minutes: ");
    scanf(" %d", &m);

    return encode(h, m);
}

int hours(int t) {
    return t / 100;
}

int minutes(int t) {
    return t % 100;
}

void print(int t) {
    printf("%02d:%02d", hours(t), minutes(t));
}

int add(int t1, int t2) {
    int _hours = hours(t1) + hours(t2);
    int _minutes = minutes(t1) + minutes(t2);

    if(_minutes > 59) {
        _minutes -= 60;
        _hours++;
    }

    if(_hours > 23) {
        _hours -= 24;
    }

    return encode(_hours, _minutes);
}

int total_minutes(int t) {
    return hours(t) * 60 + minutes(t);
}