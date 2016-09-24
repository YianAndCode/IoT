#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>

#define ARG_COUNT 2

void showUseage()
{
    printf("Usage: gpioctrl <action> <pin>\n");
}

int main(int argc, char *argv[])
{
    char *action;
    int pin;

    if(argc != ARG_COUNT + 1)
    {
        showUseage();
        exit(-1);
    }

    action = argv[1];
    pin = atoi(argv[2]);

    wiringPiSetup();

    if(strcmp(action, "status") == 0)
    {
        int status;
        status = digitalRead(pin);
        if(status == LOW)
        {
            printf("off\n");
        }
        else if(status == HIGH)
        {
            printf("on\n");
        }
    }
    else if(strcmp(action, "on") == 0)
    {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, HIGH);
        printf("on\n");
    }
    else if(strcmp(action, "off") == 0)
    {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
        printf("off\n");
    }
    else
    {
        printf("Unknown action. Available action: status, on, off\n");
    }

    return 0;
}