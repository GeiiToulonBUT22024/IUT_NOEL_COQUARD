/* 
 * File:   main.c
 * Author: Table2
 *
 * Created on 5 septembre 2023, 12:28
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
#include "Robot.h"
#include "PWM.h"
#include "main.h"
#include "grafcet.h"
#include "UART.h"
#include "ADC.h"
#include "CB_TX1.h"
#include "CB_RX1.h"
#include <libpic30.h>
#include "UART_Protocol.h"

int main(void) {
    /***************************************************************************************************/
    //Initialisation de l?oscillateur
    /****************************************************************************************************/
    InitOscillator();

    /****************************************************************************************************/
    // Configuration des entr�es sorties
    /****************************************************************************************************/

    /****************************************************************************************************/
    // Appel des fonctions
    /****************************************************************************************************/
    InitIO();
    InitTimer1();
    InitTimer4();
    InitTimer23();
    InitPWM();
    InitADC1();
    InitUART();

    LED_BLANCHE = 1;
    LED_BLEUE = 1;
    LED_ORANGE = 1;

    PWMSetSpeedConsigne(0, MOTEUR_DROIT);
    PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);

    /****************************************************************************************************/
    // Boucle Principale
    /****************************************************************************************************/
    while (1) {
        if (ADCIsConversionFinished()) {
            unsigned int * result = ADCGetResult();
            float volts = ((float) result[0])* 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreExtremeDroite = 34 / volts - 5;

            volts = ((float) result[1])* 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreDroit = 34 / volts - 5;

            volts = ((float) result[2])* 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreCentre = 34 / volts - 5;

            volts = ((float) result[3])* 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreGauche = 34 / volts - 5;

            volts = ((float) result[4])* 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreExtremeGauche = 34 / volts - 5;
            
            

            ADCClearConversionFinishedFlag();
        }
        /*SendMessage((unsigned char*) "Bonjour", 7);
        __delay32(40000000);*/

        /*int i;
        for (i = 0; i < CB_RX1_GetDataSize(); i++) {
            unsigned char c = CB_RX1_Get();
            SendMessage(&c, 1);
        }
        
        unsigned char* payload[7] = {'B', 'o', 'n', 'j', 'o', 'u', 'r'};
        UartEncodeAndSendMessage(0x0080, 7, (unsigned char*)"Bonjour" ) ;
        
        __delay32(40000000) ;*/
    }
}

