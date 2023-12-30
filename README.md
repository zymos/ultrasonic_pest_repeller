# Ultrasonic (super annoying) Pest Repeller
Beeps dual ultrasonic frequencies with random durration and pauses. Also flashes LEDs.  It activates when motion is detected and at random times.

## MCU
I had a bunch of ATtiny26L, so I used them.  The code is so simple, you can easily convert it to any MCU.
- Vcc = 5V
- internal oscilator, 1MHz

## Oscilator
I used an NE556(dual 555) as two astable multivibrator. They drove two ultrasonic piezo speakers, at two different frequencies. Rodents can hear up to 80kHz (In their youth). Humans hear up to 20kHz. I chose 30kHz and 40kHz for the ultrasonic frequencies.
- Vcc = 12V
- freq-1 = 30kHz
- freq-2 = 40kHz
- Reset pin is controlled by the MCU 
- Output to drive ultrasonic speakers

## PIR
I used two cheap PIR, HC-SR501
- Vcc = 5V
- V-pir-output-high = 3.3-3.5V
- V-pir-output-low = 0.4-0.8V
- Output to a diode OR-gate

## Ultrasonic speakers
- two cheap piezo ultrasonic speakers
- Driven = 12V square wave
- freq-1 = 30kHz
- freq-2 = 40kHz

## Power
- Vpower-in = 12V
- Vcc-osc(555) = 12V
- Vcc-pir and Vcc-mcu = 5V via a 7805
- V-led = 3.3V via cheap DC-DC converter

## References
- Hearing ranges:  https://en.wikipedia.org/wiki/Hearing_range#/media/File:Animal_hearing_frequency_range.svg
