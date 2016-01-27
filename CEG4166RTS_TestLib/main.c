/****************************************************************************//*!
 * \file main.c
 * \author Gilbert Arbez
 * \date Jun3 4 2015
 * \brief Tests for the USART module.
******************************************************************************/
/****************************************************************************//*!
 * \defgroup testingUSARTModule  USART Asynchronous Serial Module Testing
 * @{
******************************************************************************/

// Doxygen documentation: Test Plan
/******************************************************************************//*!
 * \mainpage USART Asynchronous Serial Module Test Plan
 *
 * \section Test Case 1
 *
 * The initial test is to simply check that the USART0 transmit functions are operating properly
 * as the default USART.
 * Send a test string to the terminal using the following functions:
 * 1) usart_print - to print string
 * 2) usart_print_P - to print string from program memory
 * 3) usart_printf - to print formated string
 * 4) usart_printf_P - to print formated string from program memory
 * 5) usart_xprint - to print string using interrupts
 * 6) usart_xprint_P - to print string from program memory using interrupts
 * 7) usart_xprintf - to print formated string using interrupts
 * 8) usart_xprintf_P - to print formated string from program memory using interrupts
 * This test case needs to pass before attempting all other tests since results from tests are
 * displayed on the terminal connected to USART0.
 *
 * \section Test Case 2
 *
 * Checks string functions to transmit directly to USART0 .
 * Send a test string to the terminal using the following functions:
 * 1) usart_fprint - to print string
 * 2) usart_fprint_P - to print string from program memory
 * 3) usart_fprintf - to print formated string
 * 4) usart_fprintf_P - to print formated string from program memory
 * 5) usart_xfprint - to print string using interrupts
 * 6) usart_xfprint_P - to print string from program memory using interrupts
 * 7) usart_xfprintf - to print formated string using interrupts
 * 8) usart_xfprintf_P - to print formated string from program memory using interrupts
 *
 * \section Test Case 3
 *
 * Checks that USART can be closed and opened
 * 1) usartOpen - setups up connection to a USART
 * 2) usartClose - Closes a connection to a USART
 *
 * \section Test Case 4
 *
 * Checks reading and writing characters to/from terminal
 * 1) usartWrite - reads character from USART (with polling)
 * 2) usartRead - writes character to USART (with polling)
 * 3) usart_xgetChar - gets character from ring buffer(requires interrupts)
 * 4) usart_xputChar - add character to ring buffer (requires interrupts)
 *
 * \section Test Case 5
 *
 * Checks buffer count in USART0 receive ring buffer and flush characters in the buffer
 * 1) usart_AvailableCharRx  - number of available characters in the input buffer
 * 2) usart_xflushRx - deletes characters in receive buffer.
 *
 * \section Test Case 6
 *
 * Transmits large message (800 characters) to check the filling of the
 * transmit buffer.
 * 1) usart_xfprint_P  - transmit messages stored in program memory.
 *
 * \section Test Case 7
 *
 * Test transmission and reception between USART1 and USART2.  The Rx lines from the USARTs must
 * be connected to the Tx lines of the other USARTs (i.e. NULL modem connection.
 * 1) usartOpen - setups up connection to a USART
 * 2) usartClose - Closes a connection to a USART
 * 3) usart_xgetChar - gets character from ring buffer(requires interrupts)
 * 4) usart_xfprint  - transmit messages stored in program memory.
  *
 * \section Test Case 8
 *
 * Test transmission and reception between USART2 and USART3.  The Rx lines from the USARTs must
 * be connected to the Tx lines of the other USARTs (i.e. NULL modem connection.
 * 1) usartOpen - setups up connection to a USART
 * 2) usartClose - Closes a connection to a USART
 * 3) usart_xgetChar - gets character from ring buffer(requires interrupts)
 * 4) usart_xfprint  - transmit messages stored in program memory.
 *
 *************************************************************************************************/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include <avr/io.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* serial interface include file. */
#include "usartSerial.h"

// test includes
#include "testLib.h"

// Definitions
#define BUFSIZ 50  // Small buffer

/*-----------------------------------------------------------*/
static void runTests(void *pvParameters); // Run test cases

/*-----------------------------------------------------------*/

/* Main program loop */
int main(void) __attribute__((OS_main));

int main(void)
{
    // turn on the serial port for debugging or for other USART reasons. Tests non-interrupt print functions.
	runUSARTTestsWithoutInterrupts();  // Configures USART0 as the default USART

    xTaskCreate(
		runTests
		,  (const portCHAR *)"runTests"
		,  1024
		,  NULL
		,  3
		,  NULL ); // */

    usart_printf_P(PSTR("\r\n\nFree Heap Size: %u\r\n"),xPortGetFreeHeapSize() ); // needs heap_1 or heap_2 for this function to succeed.

	vTaskStartScheduler();

	usart_print_P(PSTR("\r\n\n\nGoodbye... no space for idle task!\r\n")); // Doh, so we're dead...

}

/*-----------------------------------------------------------*/


static void runTests(void *pvParameters)
{
    (void) pvParameters;;
    TickType_t xLastWakeTime;
	/* The xLastWakeTime variable needs to be initialised with the current tick
	count.  Note that this is the only time we access this variable.  From this
	point on xLastWakeTime is managed automatically by the vTaskDelayUntil()
	API function. */
	xLastWakeTime = xTaskGetTickCount();

	DDRB |= _BV(DDB7);

    while(1)
    {
    	runUSARTTestsWithInterrupts();

		PORTB &= ~_BV(PORTB7);       // main (red IO_B7) LED off. EtherMega LED off
		vTaskDelayUntil( &xLastWakeTime, ( 10000 / portTICK_PERIOD_MS ) );
    }
}

/*-----------------------------------------------------------*/


void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    portCHAR *pcTaskName )
{

	DDRB  |= _BV(DDB7);
	PORTB |= _BV(PORTB7);       // main (red PB7) LED on. Mega main LED on and die.
	while(1);
}

/*-----------------------------------------------------------*/

