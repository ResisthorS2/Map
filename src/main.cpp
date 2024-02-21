#include <Arduino.h>

#ifndef PARAM_H
#include "C:\Users\arthu\OneDrive\Universite\Udes\S2\Projet\RetrouverP15\Map\lib\param.h"
#endif

#ifndef TEST_H
#include "C:\Users\arthu\OneDrive\Universite\Udes\S2\Projet\RetrouverP15\Map\lib\test.h"
#endif


void setup() 
{

    Pin pin;

    //bouton
    pinMode(pin.btn_devant, INPUT);
    pinMode(pin.btn_droit, INPUT);
    pinMode(pin.btn_gauche, INPUT);
    pinMode(pin.btn_180, INPUT);


}


int main()
{
    
    test_bouton();

    return 0;
}