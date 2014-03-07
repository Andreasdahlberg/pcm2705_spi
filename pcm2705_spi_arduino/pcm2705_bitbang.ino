/*
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
       
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
       
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 MA 02110-1301, USA.
*/

#include "pcm2705_bitbang.h"


int spi_reg = 0x00;


void setup()
{
	//Set SPI pins as outputs
	pinMode (MOSI, OUTPUT); // pin 11
	pinMode (SCK, OUTPUT);  // pin 13
	pinMode (SS, OUTPUT);   // pin 10
	
	//Only for testing
	pinMode (BUTTON1, INPUT);
	pinMode (BUTTON2, INPUT);
	pinMode (BUTTON3, INPUT);
	pinMode (BUTTON4, INPUT);
	
	//Set all SPI pins high
	digitalWrite(SS, HIGH);
	digitalWrite(MOSI, HIGH);
	digitalWrite(SCK, HIGH);
	
	//Remove any junk in the SPI register caused by the start/restart sequence
	clear_spi_reg();
}


void loop()
{
	if (digitalRead(BUTTON1) == HIGH)
	{
		previous();
		delay(200);
	}
	if (digitalRead(BUTTON2) == HIGH)
	{
		next();
		delay(200);
	}
}


void mute()
{
	spi_reg |= (1<<MUTE);
	send_spi_reg();
	clear_spi_reg();
}


void volume_up()
{
	spi_reg |= (1<<VOLU);
	send_spi_reg();
	clear_spi_reg();
}


void volume_down()
{
	spi_reg |= (1<<VOLD);
	send_spi_reg();
	clear_spi_reg();
}


void next()
{
	spi_reg |= (1<<NEXT);
	send_spi_reg();
	clear_spi_reg();
}


void previous()
{
	spi_reg |= (1<<PREV);
	send_spi_reg();
	clear_spi_reg();
}


void stop()
{
	spi_reg |= (1<<STOP);
	send_spi_reg();
	clear_spi_reg();
}


void play_pause()
{
	spi_reg |= (1<<PLAY);
	send_spi_reg();
	clear_spi_reg();
}


void clear_spi_reg()
{
	spi_reg = 0x00;
	send_spi_reg();
}


//1=HID status write
//0=ROM data write
void set_mode(byte mode)
{
	if (mode == 1)
	{
		//Set ST(B11) high
		spi_reg |= (1 << ST); 	
	}
	else
	{
		//Set ST(B11) low
		spi_reg &= ~(1 < ST);
	}
}


void send_spi_reg()
{
	byte cnt;
	
	//Pull SCK and SS low to prepare for data stream
	digitalWrite(SCK, LOW);
	digitalWrite(SS, LOW);
	
	for(cnt=0;cnt<16;++cnt)
	{
		if ((spi_reg & (1 << (15-cnt))) > 1)
		{
			digitalWrite(MOSI, HIGH);
		}
		else
		{
			digitalWrite(MOSI, LOW);
		}
		//Pull clock high and then low to send bit
		tick();
	}
	//Return SCK and SS to normal state
	digitalWrite(SS, HIGH);
	digitalWrite(SCK, HIGH);
}


//Take CLK low and then high again.
void tick()
{
	digitalWrite(SCK, HIGH);
	digitalWrite(SCK, LOW);
}


