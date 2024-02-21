#include <Arduino.h>
#include <iostream>
#include "C:\Users\arthu\OneDrive\Universite\Udes\S2\Projet\RetrouverP15\Map\lib\test.h"

#ifndef PARAM_H
#include "C:\Users\arthu\OneDrive\Universite\Udes\S2\Projet\RetrouverP15\Map\lib\param.h"
#endif

#define RED     "\x1b[31m"      /* Red */
#define GREEN   "\x1b[32m"      /* Green */

using namespace std;



void test_bouton()
{
    Pin pin;
    while(1)
    {
        if(digitalRead(pin.btn_180) == HIGH)
            {
                cout << GREEN;
                cout << "BTN_180 - HIGH" << endl;
            }

        if(digitalRead(pin.btn_gauche) == HIGH)
            {
                cout << GREEN;
                cout << "BTN_GAUCHE - HIGH" << endl;
            }

        if(digitalRead(pin.btn_droit) == HIGH)
            {
                cout << GREEN;
                cout << "BTN_DROIT - HIGH" << endl;
            }

        if(digitalRead(pin.btn_devant) == HIGH)
            {
                cout << GREEN;
                cout << "BTN_DEVANT - HIGH" << endl;
            }

            delay(100);
    }
}

