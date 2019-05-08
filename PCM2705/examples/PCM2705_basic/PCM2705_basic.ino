#include "pcm2705_spi.h"

//Buttons connected to the following pins:
const byte BUTTON1 = 9;
const byte BUTTON2 = 8;
const byte BUTTON3 = 7;
const byte BUTTON4 = 6;

//Init with standard SPI pins (11, 13, 10)
//Connect these to the corresponding pins on the PCM2705 chip. See the datasheet
//for pin placement.
PCM2705_SPI pcm2705(MOSI, SCK, SS);

void setup()
{
	//Set button pins as inputs
	pinMode (BUTTON1, INPUT);
	pinMode (BUTTON2, INPUT);
	pinMode (BUTTON3, INPUT);
	pinMode (BUTTON4, INPUT);
}

void loop()
{
	if (digitalRead(BUTTON1) == HIGH)
	{
		pcm2705.previous();
		delay(250);
	}
	
	else if (digitalRead(BUTTON2) == HIGH)
	{
		pcm2705.next();
		delay(250);
	}
	
	if (digitalRead(BUTTON3) == HIGH)
	{
		pcm2705.volume_down();
		delay(250);
	}
	
	else if (digitalRead(BUTTON4) == HIGH)
	{
		pcm2705.volume_up();
		delay(250);
	}
}




