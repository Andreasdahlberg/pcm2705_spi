#include "pcm2705_spi.h"
//This example will write to the internal descriptor data when the button on pin
// 9 is pressed.


int VENDOR_ID = 0x08BB;  //Texas Instruments
int PRODUCT_ID = 0x2706; // PCM2705 Audio Codec
byte DEVICE_STRING[16] = "My device name ";
byte VENDOR_STRING[32] = "My vendor string               ";
byte BM_ATTRIBUTE = 0x80; // Bus-powered
byte MAX_PWR = 0xFA; // 500 mA
byte HID_USAGE_ID[3] = {0x01, 0x93, 0x0A}; //AL A/V capture


//Buttons connected to the folowing pins:
const byte BUTTON1 = 9;


//Init with standard SPI pins (11, 13, 10)
//Connect these to the corresponding pins on the PCM2705 chip. See the datasheet
//for pin placement.
PCM2705_SPI pcm2705(MOSI, SCK, SS);


void setup()
{
	//Set button pins as inputs
	pinMode (BUTTON1, INPUT);

}


void loop()
{
	if (digitalRead(BUTTON1) == HIGH)
	{
		pcm2705.send_descriptor_data(VENDOR_ID, PRODUCT_ID, DEVICE_STRING, 
									 VENDOR_STRING, BM_ATTRIBUTE, MAX_PWR,
									 HID_USAGE_ID);
		delay(500);
	}
}




