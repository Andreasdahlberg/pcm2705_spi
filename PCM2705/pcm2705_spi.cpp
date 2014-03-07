/*
  pcm2705_spi.cpp - Library for interfacing with the PCM2705C USB DAC.
  Created by Andreas Dahlberg, 2014
*/

#include "Arduino.h"
#include "pcm2705_spi.h"


PCM2705_SPI::PCM2705_SPI(byte MD, byte MC, byte MS)
{
	_spi_reg = 0x00;
	_MD = MD;
	_MC = MC;
	_MS = MS;
	
	//Set SPI pins as outputs
	pinMode (_MD, OUTPUT);
	pinMode (_MC, OUTPUT);
	pinMode (_MS, OUTPUT);
	
	//Set all SPI pins high
	digitalWrite(_MS, HIGH);
	digitalWrite(_MD, HIGH);
	digitalWrite(_MC, HIGH);
	
	//Remove any junk in the SPI register caused by the start/restart sequence
	PCM2705_SPI::_clear_spi_reg();	
}



void PCM2705_SPI::mute()
{
	_spi_reg |= (1<<MUTE);
	PCM2705_SPI::_send_spi_reg();
	PCM2705_SPI::_clear_spi_reg();	
}


void PCM2705_SPI::volume_up()
{
	_spi_reg |= (1<<VOLU);
	PCM2705_SPI::_send_spi_reg();
	PCM2705_SPI::_clear_spi_reg();	
}


void PCM2705_SPI::volume_down()
{
	_spi_reg |= (1<<VOLD);
	PCM2705_SPI::_send_spi_reg();
	PCM2705_SPI::_clear_spi_reg();	
}


void PCM2705_SPI::next()
{
	_spi_reg |= (1<<NEXT);
	PCM2705_SPI::_send_spi_reg();
	PCM2705_SPI::_clear_spi_reg();	
}


void PCM2705_SPI::previous()
{
	_spi_reg |= (1<<PREV);
	PCM2705_SPI::_send_spi_reg();
	PCM2705_SPI::_clear_spi_reg();	
}


void PCM2705_SPI::stop()
{
	_spi_reg |= (1<<STOP);
	PCM2705_SPI::_send_spi_reg();
	PCM2705_SPI::_clear_spi_reg();	
}


void PCM2705_SPI::play_pause()
{
	_spi_reg |= (1<<PLAY);
	PCM2705_SPI::_send_spi_reg();
	PCM2705_SPI::_clear_spi_reg();	
}


//1=HID status write
//0=ROM data write
void PCM2705_SPI::_set_mode(byte mode)
{
	if (mode == 1)
	{
		//Set ST(B11) high
		_spi_reg |= (1 << ST); 	
	}
	else
	{
		//Set ST(B11) low
		_spi_reg &= ~(1 < ST);
	}
}


void PCM2705_SPI::_clear_spi_reg()
{
	_spi_reg = 0x00;
	PCM2705_SPI::_send_spi_reg();
}


void PCM2705_SPI::_send_spi_reg()
{
	byte cnt;
	
	//Pull _MC and _MS low to prepare for data stream
	digitalWrite(_MC, LOW);
	digitalWrite(_MS, LOW);
	
	for(cnt=0;cnt<16;++cnt)
	{
		if ((_spi_reg & (1 << (15-cnt))) > 1)
		{
			digitalWrite(_MD, HIGH);
		}
		else
		{
			digitalWrite(_MD, LOW);
		}
		//Pull clock high and then low to send bit
		PCM2705_SPI::_tick();
	}
	//Return _MC and _MS to normal state
	digitalWrite(_MS, HIGH);
	digitalWrite(_MC, HIGH);
}


//Take CLK low and then high again.
void PCM2705_SPI::_tick()
{
	digitalWrite(_MC, HIGH);
	digitalWrite(_MC, LOW);
}



