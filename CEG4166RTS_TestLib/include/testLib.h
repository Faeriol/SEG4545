/****************************************************************************//*!
    \file usartSerial.h
    Module: USART Async Serial

    Description:  Provides asynchronous serial communication via any of the four USARTS available in the
    AtMega 2560.

    Both interrupt driven and polling functions are available.

    Uses freeRTOS ring buffers to support interrupt functions.
**********************************************************************************/
/****************************************************************************//*!
 * \addtogroup testLibModule
 * @{
******************************************************************************/

/*-----------------------------------------------------------*/
//Entry Points - documented in c file
/*-----------------------------------------------------------*/
void runUSARTTestsWithoutInterrupts(void);
void runUSARTTestsWithInterrupts(void);

/*!@}*/   // End of testLibModule Group
