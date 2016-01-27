/****************************************************************************//*!
 * \file main.c
 * \author Gilbert Arbez
 * \date Jun3 4 2015
 * \brief Tests for the USART module.
******************************************************************************/
/****************************************************************************//*!
 * \defgroup testLibModule  USART Asynchronous Serial Module Testing
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
 * be connected to the Tx lines of the other USARTs (i.e. NULL modem connection.  USART1 will also
 * be tested as the default USART.
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

// Definitions
#define BUFSIZ 50  // Small buffer

// Test Module Include
#include "testLib.h"

/*-----------------------------------------------------------*/
int testCase1a();
void testCase1b();
void testCase2a();
void testCase2b();
void testCase3();
void testCase4a();
void testCase4b();
void testCase5();
void testCase6();
void testCase7a();
void testCase7b();
void testCase8();
void testing2USARTS(int, int, uint8_t *);

/*-----------------------------------------------------------*/


void runUSARTTestsWithoutInterrupts(void)
{
    // turn on the serial port for debugging or for other USART reasons. Tests non-interrupt print functions.
	testCase1a();  // Sets up USART0 as the default
	testCase2a();
	testCase4a();  // tests reading/writing of characters from/to terminal
}

/*-----------------------------------------------------------*/


void runUSARTTestsWithInterrupts()
{
    	testCase1b();
    	testCase2b();  // uses explicit USART0 in print function args.
    	testCase3();  // Closes USART0
    	testCase4b();  // Reads/Write chars using interrupt functions - returns only when S hit by user
    	testCase5();  // Check Rx ring buffer count and flushing
    	testCase6();  // fill transmit buffer
    	testCase7a();  // Connect Rx/Tx lines between two USARTS and select appropriate test case
    	              //  USARTs           Test Case
    	              // USART1, USART2    testCase7a and testCase7b
    	              // USART2, USART3    testCase8
    	testCase7b();
}

/*************************************************************************************//*!
 * Testing  print functions to USART0 as default USART without interrupts.  Leaves the connection
 * to USART0 open. To be executed before enabling interrupts.
 *
 * @return - the USART identifier of the opened USART - that is USART0.
 */
char buffer[BUFSIZ];
char buffer2[BUFSIZ];
int testCase1a()
{
    int uid;

    // turn on the serial port for debugging or for other USART reasons.
	uid = usartOpen( USART0_ID, 115200, portSERIAL_BUFFER_TX, portSERIAL_BUFFER_RX); //  serial port: WantedBaud, TxQueueLength, RxQueueLength (8n1)

	// Test print functions with devault USR
    usart_print_P(PSTR("\nTest Case 1a\n"));
	sprintf(buffer,"Printing string using %s\n","usart_print");
	usart_print((uint8_t *) buffer); // to print string
	usart_print_P(PSTR("Printing string using usart_print_P\n")); //to print string from program memory*/
	strcpy(buffer,"Printing string using %s\n");
	strcpy(buffer2,"usart_printf");
	usart_printf(buffer, buffer2); // to print formated string
	usart_printf_P(PSTR("Printing string using %s\n"), "usart_printf_P"); //to print formated string from program memory
	sprintf(buffer,"Printing string using %s\n","usart_print");
	return(uid);
}


/*************************************************************************************//*!
 * Testing  print functions to USART0 as default USART with interrupts.  It is expected
 *  that the default 0 is already opened.
 */
void testCase1b()
{
	usart_xprint((uint8_t *) "\nTest Case 1b\n");
	sprintf(buffer,"Printing string using %s\n","usart_xprint");
	usart_xprint((uint8_t *) buffer); // to print string using interrupts
	usart_xprint_P(PSTR("Printing string using usart_xprint_P\n")); //to print string from program memory using interrupts
	strcpy(buffer,"Printing string using %s\n");
	usart_xprintf(buffer,"usart_xprintf"); // to print formated string using interrupts
	usart_xprintf_P(PSTR("Printing string using %s\n"), "usart_xprintf_P" ); //to print formated string from program memory using interrupts
}


/*************************************************************************************//*!
 * Testing  print functions to USART0 as default USART without interrupts.  Leaves the connection
 * to USART0 open. To be executed before enabling interrupts.
 *
 * @return - the USART identifier of the opened USART - that is USART0.
 */
void testCase2a()
{
	// Test fprint functions
    usart_print_P(PSTR("\nTest Case 2a\n"));
	sprintf(buffer,"\nPrinting string using %s\n","usart_fprint");
	usart_fprint(USART0_ID,(uint8_t *) buffer); // to print string
	usart_fprint_P(USART0_ID, PSTR("Printing string using usart_fprint_P\n")); //to print string from program memory
	strcpy(buffer,"Printing string using %s\n");
	strcpy(buffer2,"usart_fprintf");
	usart_fprintf(USART0_ID, buffer, buffer2); // to print formated string
	usart_fprintf_P(USART0_ID,PSTR("Printing string using %s\n"), "usart_fprintf_P"); //to print formated string from program memory*/
}

/*************************************************************************************//*!
 * Testing  print functions to USART0 defined explicitly (with interrupts).  It is expected
 *  that USART0 is already opened.
 */
void testCase2b()
{
	usart_xprint((uint8_t *) "\nTest Case 2b\n");
	sprintf(buffer,"Printing string using %s\n","usart_xfprint");
	usart_xfprint(USART0_ID,(uint8_t *) buffer); // to print string using interrupts
	usart_xfprint_P(USART0_ID,PSTR("Printing string using usart_xfprint_P\n")); //to print string from program memory using interrupts
	strcpy(buffer,"Printing string using %s\n");
	usart_xfprintf(USART0_ID,buffer,"usart_xfprintf"); // to print formated string using interrupts
	usart_xfprintf_P(USART0_ID,PSTR("Printing string using %s\n"), "usart_xfprintf_P" ); //to print formated string from program memory using interrupts
}


/*************************************************************************************//*!
 * Closes USART0 and renables it.
 */
void testCase3()
{
	vTaskDelay( 100 / portTICK_PERIOD_MS );  // Allow transmission of buffer before closing USART0
	usartClose(USART0_ID);
	usartOpen( USART0_ID, 115200, portSERIAL_BUFFER_TX, portSERIAL_BUFFER_RX); //  serial port: WantedBaud, TxQueueLength, RxQueueLength (8n1)
	usart_xprint((uint8_t *) "\nTest Case 3\nClosed and opened USSART 0\n");
}

/*************************************************************************************//*!
 * Reads character from keyboard and echos to terminal (type S to stop) with polling routines.
 * It is expected that USART0 is already opened.  Use before interrupts are enabled.
 */
void testCase4a()
{
	uint8_t ch;
	usart_print((uint8_t *) "\nTest Case 4a\n");
	usart_fprint_P(USART0_ID,PSTR("Type characters - will be echoed.  Type S to stop\n")); //to print string from program memory using interrupts
	while( (ch = usartRead(USART0_ID)) != 'S')
	    usartWrite(USART0_ID, ch);
	usartWrite(USART0_ID, '\n');
}

/*************************************************************************************//*!
 * Reads character from keyboard and echos to terminal (type S to stop) with interrupt
 * driven routines. It is expected that USART0 is already opened.  Use after interrupts are enabled.
 */
void testCase4b()
{
	uint8_t ch;
	usart_xprint((uint8_t *) "\nTest Case 4b\n");
	usart_xfprint_P(USART0_ID,PSTR("Type characters - will be echoed.  Type S to stop\n")); //to print string from program memory using interrupts
	ch = ' ';
	while( ch != 'S')
		if(usart_xgetChar(USART0_ID, &ch)) usart_xputChar(USART0_ID, ch);
	usart_xputChar(USART0_ID, '\n');
}

/*************************************************************************************//*!
 * Waits until 20 characters are collected in the ring buffer (displays count).
 * Flushes the characters collected.
 * Waits until 5 characters are received - collect and print them.
 */
void testCase5()
{
	uint8_t count;
	int ix;
	usart_xprint((uint8_t *) "\nTest Case 5\n");
	usart_xfprint_P(USART0_ID,PSTR("Type in 20 characters, they will be counted and then flushed.\n"));
	count = 0;
	while(count < 20 )
	{
		usart_xfprintf_P(USART0_ID,PSTR("\rCount =  %d"),count);
		count = usart_AvailableCharRx(USART0_ID);
		vTaskDelay( 1000 / portTICK_PERIOD_MS );  // Allow transmission of buffer before closing USART0
	}
	usart_xfprint_P(USART0_ID,PSTR("Flushing characters\n"));
	usart_xflushRx(USART0_ID);
	usart_xfprintf_P(USART0_ID,PSTR("There are now %d chars in the buffer\n"), usart_AvailableCharRx(USART0_ID));
	usart_xfprint_P(USART0_ID,PSTR("Type in 5 characters (different from the 20 chars), they will be counted, read and printed.\n"));
	while( usart_AvailableCharRx(USART0_ID) < 5)  /* do nothing */;
	for(ix = 0; ix < 5; ix++) usart_xgetChar(USART0_ID, (uint8_t *) &buffer[ix]);
	buffer[ix] = '\0';
	usart_xfprintf_P(USART0_ID,PSTR("Five characters read are >%s<\n"), buffer);
}

// Test Data - long message
// 800 characters with buffer of 255 characters - use to test filling of Tx ring buffer.
uint8_t longMsg[] = "1111111111222222222233333333334444444444555555555566666666667777777777888888888899999999990000000000\n";
/*************************************************************************************//*!
 * Transmits very long message 20 times, 2000 characters, to fill transmit buffer (255 characters).
 */
void testCase6()
{
	int i;
	usart_xprint_P(PSTR("\nTest Case 6\n"));
	usart_xprint((uint8_t *) "There should be 20 lines that follow each with 100 characters\n");
	for(i=0; i<20; i++) usart_xprint(longMsg);
}



uint8_t shortMsg[] = "This is a short message\n";
/*************************************************************************************//*!
 * Transmission and reception between USART1 and USART2.
 */
void testCase7a()
{
	testing2USARTS(USART1_ID, USART2_ID, (uint8_t *) "\nTest Case 7a\n");
}
/*************************************************************************************//*!
 * Transmission and reception between USART1 and USART2.  USART1 is setup as the default
 * USART.
 */
void testCase7b()
{
	uint8_t ch;
	int uida, uidb;
	// Open usarts
	uida = usartOpen( USART1_ID, 19200, portSERIAL_BUFFER_TX, portSERIAL_BUFFER_RX); //  serial port: WantedBaud, TxQueueLength, RxQueueLength (8n1)
	uidb = usartOpen( USART2_ID, 19200, portSERIAL_BUFFER_TX, portSERIAL_BUFFER_RX); //  serial port: WantedBaud, TxQueueLength, RxQueueLength (8n1)
	setDefaultUSART(uida);

	usart_xprint((uint8_t *) "\nTest Case 7b\n");

	// From USART1 to USART2
	usart_xfprintf_P(USART0_ID,PSTR("Sending to usartA (as default): %s"),shortMsg);
	usart_xprint(shortMsg);
	usart_xfprintf(USART0_ID,"Receiving from usartB (%d): ", uidb);
	ch = ' ';
	while( ch != '\n')
		if(usart_xgetChar(uidb, &ch)) usart_xputChar(USART0_ID, ch);
	usart_xputChar(USART0_ID, '\n');

	// From USART2 to USART1
	usart_xfprintf_P(USART0_ID, PSTR("Sending to usartB (%d): %s"),uidb, shortMsg);
	usart_xfprint(uidb,shortMsg);
	usart_xfprintf(USART0_ID, "Receiving from usartA (%d): ", uida);
	ch = ' ';
	while( ch != '\n')
		if(usart_xgetChar(uida, &ch)) usart_xputChar(USART0_ID, ch);
	usart_xputChar(USART0_ID, '\n');

	// Close usarts
	usartClose(uida);
	usartClose(uidb);
	setDefaultUSART(USART0_ID);  // Assume original default was USART0
}

/*************************************************************************************//*!
 * Transmission and reception between USART2 and USART3.
 */
void testCase8()
{
	testing2USARTS(USART2_ID, USART3_ID, (uint8_t *) "\nTest Case 8\n");
}


/*************************************************************************************//*!
 * Transmission and reception between two USARTS.
 */
void testing2USARTS(int usartA, int usartB, uint8_t *caseName)
{
	uint8_t ch;
	int uida, uidb;
	// Open usarts
	uida = usartOpen( usartA, 19200, portSERIAL_BUFFER_TX, portSERIAL_BUFFER_RX); //  serial port: WantedBaud, TxQueueLength, RxQueueLength (8n1)
	uidb = usartOpen( usartB, 19200, portSERIAL_BUFFER_TX, portSERIAL_BUFFER_RX); //  serial port: WantedBaud, TxQueueLength, RxQueueLength (8n1)


	usart_xprint(caseName);

	// From USART1 to USART2
	usart_xprintf_P(PSTR("Sending to usartA (%d): %s"),usartA,shortMsg);
	usart_xfprint(uida,shortMsg);
	usart_xprintf("Receiving from usartB (%d): ", usartB);
	ch = ' ';
	while( ch != '\n')
		if(usart_xgetChar(uidb, &ch)) usart_xputChar(USART0_ID, ch);
	usart_xputChar(USART0_ID, '\n');

	// From USART2 to USART1
	usart_xprintf_P(PSTR("Sending to usartB (%d): %s"),usartB, shortMsg);
	usart_xfprint(uidb,shortMsg);
	usart_xprintf("Receiving from usartA (%d): ", usartA);
	ch = ' ';
	while( ch != '\n')
		if(usart_xgetChar(uida, &ch)) usart_xputChar(USART0_ID, ch);
	usart_xputChar(USART0_ID, '\n');

	// Close usarts
	usartClose(uida);
	usartClose(uidb);
}

/*!@}*/   // End of testLibModule Group
