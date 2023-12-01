/*
 * Animal Deturent Ultrasonic Beeper and Flasher
 *
 *    Description: really annoy (hopfully) for pests,
 *       random ultrasonic beeps, 2-tone, and flashes
 *       Code is for Attiny26, but should be easly modified to any AVR
 *    
 *    Credits: Zef the Tinker, 2023/11
 *
 */ 

// define the frequency
#define	F_CPU	1000000
#define 	XTAL   1000000
#define __AVR_ATtiny26__ 1 // to use other MCU you need to change this


// #include <stdlib.h>
#include <avr/io.h>
// #include <avr/pgmspace.h>
#include <util/delay.h>
#include <avr/interrupt.h>



/////////////////////////////////////////////////////////////////////////////
// PINS
//    if you use other MCU you need to change this
#define PIN_SPEAK0 PA6 // ultra-sonic speaker0
#define PIN_SPEAK1 PA7 // ultra-sonic speaker1
#define PIN_LED0 PA5 // flashing LED
#define PIN_LED_PWR_ON PA4 // LED to indicate MCU is up and running

// PB6 is set to INT0 interrupt







//////////////////////////////////////////////////////////////////////////////
// Global vars
//
const int beep_length[10] = {1,7,3,4,6,2,4,8,2,5}; // list of random duration
#define delay_multi 50 // multiplier for the 1ms delay
#define sleep_delay_multi 500 // multiplier for delay between auto-activate

#define NUM_OF_LOOPS 20 // number of times to loop array




//////////////////////////////////////////////////////////////////////////////
// Code
//


// make sure the freq isnt redefine
#ifdef F_CPU
   #undef F_CPU
#endif
#define F_CPU	1000000

#ifdef XTAL
   #undef XTAL
#endif
#define XTAL   1000000



//////////////////////////////
// Animal Deturent function
//    beeps and flashes, 
//    psuedo random durration and pauses
//    
void animal_det(void){
   int pointer1 = 5; // used for speaker1 as random num list offset

   // repeat loops of array
   for(int q=0; q<NUM_OF_LOOPS; q++){
      // loop the psuedo-radom array
      //  this beep for each number in array
      for(int x=0; x < sizeof(beep_length)/sizeof(beep_length[0]); x++){ //loop the array
     
         // Speakers
         PORTA &= ~(1 << PIN_SPEAK0); //speaker 0 off
         PORTA &= ~(1 << PIN_SPEAK1); //speaker 1 off
         for(int n=0; n<10; n++){ //on/off period
            if(pointer1 == 10){ // for ponter1 offset
               pointer1 = 0;
            }
            if(n > beep_length[x]){
               PORTA |= (1 << PIN_SPEAK0); //speaker 0 on
            }
            if(n > beep_length[pointer1]){
               PORTA |= (1 << PIN_SPEAK1); //speaker 1 on
            }
            _delay_ms(1 * delay_multi); 
         }   

         //LED
         if(x % 5 == 0){ // activate LED every 5 beeps
            PORTA |= (1 << PIN_LED0); //led on
            _delay_ms(10 * delay_multi); 
            PORTA &= ~(1 << PIN_LED0); //led off
            // _delay_ms(1 * delay_multi);
         }

         // inc pointer for speaker1
         pointer1++;
      }
      
      // LED flashes
      PORTA &= ~(1 << PIN_LED0); //led 0 off
      PORTA &= ~(1 << PIN_SPEAK0); //speaker 0 off
      PORTA &= ~(1 << PIN_SPEAK1); //speaker 1 off

      _delay_ms(3 * delay_multi);
   }
}

////////////////////////////
// Interrupt on INT0
//  to use other MCU you need to change this

ISR(INT0_vect){ // to use other MCU you need to change this
   // See:
   // https://onlinedocs.microchip.com/pr/GUID-317042D4-BCCE-4065-BB05-AC4312DBC2C4-en-US-2/index.html?GUID-F889605B-692F-493A-8BE7-F0FBACF1715B
   animal_det();
}




/////////////////
// Initalize
void initialize(void){
   // enable PORTA to output
   DDRA = 0xFF; // set PORTA to all outputs // to use other MCU you need to change this


	
   // ATtiny26
   //    MCUCR: MCU Control Register
   //       ISC01=1 ISC00=1 The rising edge of INT0 generates an interrupt request.
   //    GIMSK: General Interrupt Mask Register
   //    GIFR: General Interrupt Flag Register
   //    INTF0: 6

   MCUCR |= (1<<ISC00); //rising edge // to use other MCU you need to change this
   MCUCR |= (1<<ISC01); //rising edge // to use other MCU you need to change this
   GIMSK |= (1<<INT0); // enable INT0 // to use other MCU you need to change this

   sei();     // Enable global interrupts by setting global interrupt enable bit in SREG

   // turn on LED indicator for power on
   PORTA |= (1<<PIN_LED_PWR_ON); // to use other MCU you need to change this

}


///////////
// Main
int main(void)
{
   initialize();

	while(1) {
      // animal_det();
      _delay_us(10);
   } // infinite loop


} //main
