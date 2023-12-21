#ifndef REGISTERS_F
#define REGISTERS_F

#include <stdio.h>
#include "hardware/rtc.h"


#include "harmonogram/harmonogram.cpp"
#include "time/time.cpp"

void updatedR1();
void updatedR2();

    //[0] 0-4 godzina, 5,6,7 - dzien tygodnia, [1] minuty, [3] akcja
#ifdef TIME_F
    void (* DEV_NEW_TIME_FUNC)() = newTimeFunc;
#endif

#ifdef HARMONOGRAM_F
    void (* DEV_NEW_HARMONOGRAM_FUNC)() = newHarmonogramData;
    //[0] 0-4 godzina, 5,6,7 - dzien tygodnia, [1] minuty, [3] akcja
#endif
bool REBOOT_FLAG = false;

void doReboot() {
    REBOOT_FLAG = true;
}



uint8_t DEV_ERRORS [5];
uint8_t DEV_STATUS = 0;


uint8_t DEV_REG_01 = 255;
uint8_t DEV_REG_02[5] = {31,21,1,2,3};


void updatedR1() {
    printf("regi 0 updated new val: %i: \n", DEV_REG_01);
}

void updatedR2() {
    printf("regi 1 updated new val: %i: \n", DEV_REG_02[0]);
    printf("regi 1 updated new val: %i: \n", DEV_REG_02[1]);
    printf("regi 1 updated new val: %i: \n", DEV_REG_02[2]);
    printf("regi 1 updated new val: %i: \n", DEV_REG_02[3]);
    printf("regi 1 updated new val: %i: \n", DEV_REG_02[4]);
}




#endif