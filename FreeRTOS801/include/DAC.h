// DAC.h

#ifndef DAC_h // include guard
#define DAC_h

#include <avr/pgmspace.h>
#include "FreeRTOS.h"
#include "spi.h"

#if defined(portANALOGUE)
/*--------------------------------------------------*/
/*------------------Definitions---------------------*/
/*--------------------------------------------------*/

#define CH_A_OUT	0x10
#define CH_B_OUT	0x90

#define CH_A_OFF	0x00
#define CH_B_OFF	0x80

/*--------------------------------------------------*/
/*--------------------Typedefs----------------------*/
/*--------------------------------------------------*/

typedef union DAC_command {
  uint16_t u16;
  uint8_t  u8[2];
} DAC_command_t;


/*--------------------------------------------------*/
/*--------------------Globals-----------------------*/
/*--------------------------------------------------*/

uint16_t ch_A_out; // storage for the values to be written to MCP4822
uint16_t ch_B_out;

#endif // #if defined(portANALOGUE)

/*--------------------------------------------------*/
/*---------------Public Functions-------------------*/
/*--------------------------------------------------*/

void AudioCodec_Timer1_init(uint16_t samplesSecond) // set up the sampling Timer1, runs at audio sampling rate in Hz.
{
	portENTER_CRITICAL(); // turn off interrupts

//	DDRD |= _BV(DDD6);            // xxx set the debugging ping
//	PORTD &= ~_BV(PORTD6);

	// setup Timer1 for codec clock division
	TCCR1A = 0x00; // set to  CTC Mode.
	TCCR1B = _BV(WGM12) | _BV(CS10); // CTC Mode. TOP = OCR1A. No prescaling. Clock on rising edge.
	TCCR1C = 0x00; // not used
	TCNT1 =  0x0000; // clear the counter, high byte first for 16bit writes. gcc compiler knows how to handle this.

	OCR1A = (uint16_t)(F_CPU/samplesSecond -1);

	TIMSK1 = _BV(OCIE1A); // turn on compare match interrupt

	portEXIT_CRITICAL(); // turn on interrupts
}


inline void audioCodec_dsp( uint16_t * ch_A, uint16_t * ch_B) __attribute__ ((hot, flatten));
	// prototype for the DSP function to be implemented.
	// needs to at least provide *ch_A and *ch_B
	// within Timer1 interrupt routine - time critical I/O. Keep it short and punchy!

/*--------------------------------------------------------*/

inline void DAC_out(const uint16_t * ch_A, const uint16_t * ch_B) __attribute__ ((hot, flatten));
// Assumes that the DAC SPI has already been selected, as the selection process is quite time consuming.

//	if (spiSelect (Analogue))
//	{
//		uint16_t j = 0x1234;
//		uint16_t k = 0x5678;
//		DAC_out(NULL, NULL); 	// the ch_A and ch_B are turned off by NULL, or
//		DAC_out(&j, &k);		// output the j and k values by reference
//		spiDeselect (Analogue);
//	}

inline void DAC_out_P(const uint16_t * ch_A, const uint16_t * ch_B) __attribute__ ((hot, flatten));
// Assumes that the DAC SPU has already been selected, as the selection process is quite time consuming.

//	if (spiSelect (Analogue))
//	{
//		DAC_out_P( (const uint16_t *)&sinewave[i], (const uint16_t*)&sinewave[i]); // for PROGMEM stored arrays of samples
//		spiDeselect (Analogue);
//	}

/*--------------------------------------------------*/
/*-----------Time Critical Functions----------------*/
/*--------------------------------------------------*/

#if defined(portANALOGUE)

void DAC_out(const uint16_t * ch_A, const uint16_t * ch_B)
{
	DAC_command_t command;

	// If the SPI module has not been enabled yet, then return with nothing.
	if( !(SPCR & _BV(SPE)) ) return;

	// The SPI module is enabled, but it is in slave mode, so we can not
	// transmit the byte.  This can happen if SSbar is an input and it went low.
	// We will try to recover by setting the MSTR bit.
	// Check this once only at the start. Assume that things don't change.
	if( !(SPCR & _BV(MSTR)) )
		{
			SPCR |= _BV(MSTR);
			if( !(SPCR & _BV(MSTR)) ) return;
		}

	if (ch_A != NULL)
	{
		command.u16 = (*ch_A) >> 4;
		command.u8[1] |= CH_A_OUT;
	}
	else								// ch_A is NULL so we turn off the DAC
	{
		command.u8[1] = CH_A_OFF;
	}

	SPI_PORT_SS_DAC &= ~SPI_BIT_SS_DAC;	// Pull SS low to select the Goldilocks Analogue DAC
										// (because this might not be the first time through).
	SPDR = command.u8[1];				// Begin transmission ch_A.
	while ( !(SPSR & _BV(SPIF)) );
	SPDR = command.u8[0];				// Continue transmission ch_A.

	if (ch_B != NULL)					// start processing ch_B while we're doing the ch_A transmission
	{
		command.u16 = (*ch_B) >> 4;
		command.u8[1] |= CH_B_OUT;
	}
	else								// ch_B is NULL so we turn off the DAC
	{
		command.u8[1] = CH_B_OFF;
	}

	while ( !(SPSR & _BV(SPIF)) );		// check we've finished ch_A.
	SPI_PORT_SS_DAC |= SPI_BIT_SS_DAC;	// Pull SS high to deselect the Goldilocks Analogue DAC, and latch value into DAC.

	SPI_PORT_SS_DAC &= ~SPI_BIT_SS_DAC; // Pull SS low to select the Goldilocks Analogue DAC.
	SPDR = command.u8[1];				// Begin transmission ch_B.
	while ( !(SPSR & _BV(SPIF)) );
	SPDR = command.u8[0];				// Continue transmission ch_B.
	while ( !(SPSR & _BV(SPIF)) );		// check we've finished ch_B.
	SPI_PORT_SS_DAC |= SPI_BIT_SS_DAC;	// Pull SS high to deselect the Goldilocks Analogue DAC, and latch value into DAC.
}

void DAC_out_P(const uint16_t * ch_A, const uint16_t * ch_B)
{
	DAC_command_t command;

	// If the SPI module has not been enabled yet, then return with nothing.
	if( !(SPCR & _BV(SPE)) ) return;

	// The SPI module is enabled, but it is in slave mode, so we can not
	// transmit the byte.  This can happen if SSbar is an input and it went low.
	// We will try to recover by setting the MSTR bit.
	// Check this once only at the start. Assume that things don't change.
	if( !(SPCR & _BV(MSTR)) )
		{
			SPCR |= _BV(MSTR);
			if( !(SPCR & _BV(MSTR)) ) return;
		}

	if (ch_A != NULL)
	{
		command.u16 = pgm_read_word(ch_A) >> 4;
		command.u8[1] |= CH_A_OUT;
	}
	else								// ch_A is NULL so we turn off the DAC
	{
		command.u8[1] = CH_A_OFF;
	}

	SPI_PORT_SS_DAC &= ~SPI_BIT_SS_DAC;	// Pull SS low to select the Goldilocks Analogue DAC
										// (because this might not be the first time through).
	SPDR = command.u8[1];				// Begin transmission
	while ( !(SPSR & _BV(SPIF)) );
	SPDR = command.u8[0];				// Continue transmission

	if (ch_B != NULL)					// start ch_B while we're doing the transmission
	{
		command.u16 = pgm_read_word(ch_B) >> 4;
		command.u8[1] |= CH_B_OUT;
	}
	else								// ch_B is NULL so we turn off the DAC
	{
		command.u8[1] = CH_B_OFF;
	}

	while ( !(SPSR & _BV(SPIF)) );		// check we've finished ch_A.
	SPI_PORT_SS_DAC |= SPI_BIT_SS_DAC;	// Pull SS high to deselect the Goldilocks Analogue DAC, and latch value into DAC.

	SPI_PORT_SS_DAC &= ~SPI_BIT_SS_DAC;	// Pull SS low to select the Goldilocks Analogue DAC.
	SPDR = command.u8[1];				// Begin transmission
	while ( !(SPSR & _BV(SPIF)) );
	SPDR = command.u8[0];				// Continue transmission
	while ( !(SPSR & _BV(SPIF)) );		// check we've finished ch_B.
	SPI_PORT_SS_DAC |= SPI_BIT_SS_DAC;	// Pull SS high to deselect the Goldilocks Analogue DAC, and latch value into DAC.
}

#endif // #if defined(portANALOGUE)

/*--------------------------------------------------*/
/*-------Interrupt (Loop at Sample Rate)------------*/
/*--------------------------------------------------*/

// this is an example interrupt process that will output values at the sample rate defined.
// other processes may use the DAC_out_P to increment across a PROGMEM stored set of samples

#if defined(portANALOGUE)
ISR(TIMER1_COMPA_vect)
{
	// xxx start mark - check for start of interrupt - for debugging only - delete when not wanted
//	PORTD |=  _BV(PORTD6);				// Ping IO line.

	// MCP4822 data transfer routine
	// move data from and to the MCP4822 - done first for regularity (reduced jitter).
	// &'s are necessary on data_in variables
	DAC_out(&ch_A_out, &ch_B_out);

	// audio processing routine - do whatever processing on input is required - prepare output
	audioCodec_dsp(&ch_A_out, &ch_B_out);

	// xxx end mark - check for end of interrupt - for debugging only - delete when not wanted
//	PORTD &= ~_BV(PORTD6);
}
#endif // defined(portANALOGUE)

#endif // DAC_h end include guard
