#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define ON 1
#define OFF 0

float getTemp()
{
    FILE *fp;
    char strTemp[10];
    int intTemp;
    if((fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r")) == NULL)
    {
            printf("Can't open temp file\n");
            exit(1);
    }
    fgets(strTemp, 10, fp);
    intTemp = atoi(strTemp);
    return intTemp / 1000.0;
}

int main()
{

    float currentTemp;
    int currentStatus;
    char fanStatus[2] = {"off", "on"};

    wiringPiSetup();

    // 使用 WirinfPi 编号为 0 的引脚进行控制
    pinMode(0, OUTPUT);
    digitalWrite(0, HIGH);
    currentStatus = ON;
    printf("Fan is on\n");
    delay(30000);

    while(1)
    {
        currentTemp = getTemp();
        // 高于 45.0 摄氏度则开启风扇
        if(currentTemp > 45.0)
        {
            digitalWrite(0, HIGH);
            currentStatus = ON;
            printf("Current temp is: %.2f, higher than 45.0, fan is on\n", currentTemp);
        }
        // 低于 37.0 摄氏度关闭风扇
        else if(currentTemp < 37.0 && currentStatus == ON)
        {
            digitalWrite(0, LOW);
            currentStatus = OFF;
            printf("Current temp is: %.2f, lower than 37.0, fan is off\n", currentTemp);
        }
        else
        {
            printf("Current temp is: %.2f, fan is %s\n", currentTemp, fanStatus[currentStatus]);
        }
        delay(10000);
    }
    return 0;
}
