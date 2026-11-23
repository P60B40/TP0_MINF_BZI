/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "Mc32DriverLcd.h"
#include "Mc32Delays.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    //static uint32_t n = 0;

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            //init lcd + ADC
            lcd_init();
            BSP_InitADC10();
            lcd_bl_on();

            //timer on
            DRV_TMR0_Start();
            //print message
            lcd_gotoxy(1,1);
            printf_lcd("TP0 Led+AD <2027>");
            lcd_gotoxy(1,2);
            printf_lcd("Zitouni");
            
            //initialisation des état de base
            appData.firstEntry = true;
            appData.flag_chenillard = false;
            //fonction allume led
            Led_on();

            //retour à l'état attente
            APP_UpdateState(APP_STATE_WAIT);
            
            break;
        }
        case APP_STATE_WAIT:
        {
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
            //lecture et affichage de la valeur ADC 
            appData.adcRes = BSP_ReadAllADC();
            lcd_gotoxy(1,3);
            printf_lcd("CH0 %4d / CH1 %4d", appData.adcRes.Chan0,appData.adcRes.Chan1 );
            // regarde la flag de la fct callback pour appellé le chenillard si true
            if(appData.flag_chenillard){
            chenillard();
            appData.flag_chenillard = false; // remet le flag à false pour le prochain cycle
            }
            //retour à l'état attente
            APP_UpdateState(APP_STATE_WAIT);
            break;
        }

        /* TODO: implement your application state machine.*/
        

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

void APP_TMR0_Callback (void){

    static uint8_t cptChenillard = 0;
    static uint8_t cptStart = 0;
    
    cptStart++;
    //attente de 3 seconde sinon sort de la fonction
    if(cptStart <29)
    {
       return; 
    }
    //compteur 
    cptChenillard++;
    //le chenillatd s'active que lorsque que le compteur est à 2
    if(cptChenillard >= 2){
        //active la flag pour le service task
        appData.flag_chenillard = true;
        cptChenillard = 0; //remet le cpt à zero pour le prochain cycle
    }
    APP_CHANGE_STATE(APP_STATE_SERVICE_TASKS);
    
}

void APP_CHANGE_STATE(APP_STATES newState)
{
    appData.state = newState;
}

void APP_UpdateState(APP_STATES newState){
    appData.state = newState;
}

void Led_on(void){
    BSP_LEDOn(BSP_LED_0);
    BSP_LEDOn(BSP_LED_1);
    BSP_LEDOn(BSP_LED_2);
    BSP_LEDOn(BSP_LED_3);
    BSP_LEDOn(BSP_LED_4);
    BSP_LEDOn(BSP_LED_5);
    BSP_LEDOn(BSP_LED_6);
    BSP_LEDOn(BSP_LED_7);
}

void Led_off(void){
    BSP_LEDOff(BSP_LED_0);
    BSP_LEDOff(BSP_LED_1);
    BSP_LEDOff(BSP_LED_2);
    BSP_LEDOff(BSP_LED_3);
    BSP_LEDOff(BSP_LED_4);
    BSP_LEDOff(BSP_LED_5);
    BSP_LEDOff(BSP_LED_6);
    BSP_LEDOff(BSP_LED_7);
}

void chenillard(void){

    static uint8_t led = 0;

    Led_off();

    switch(led)
    {
        case 0: BSP_LEDOn(BSP_LED_0); break;
        case 1: BSP_LEDOn(BSP_LED_1); break;
        case 2: BSP_LEDOn(BSP_LED_2); break;
        case 3: BSP_LEDOn(BSP_LED_3); break;
        case 4: BSP_LEDOn(BSP_LED_4); break;
        case 5: BSP_LEDOn(BSP_LED_5); break;
        case 6: BSP_LEDOn(BSP_LED_6); break;
        case 7: BSP_LEDOn(BSP_LED_7); break;
    }
    // boucle pour le chenillard
    led = (led + 1) % 8;
}
/*******************************************************************************
 End of File
 */
