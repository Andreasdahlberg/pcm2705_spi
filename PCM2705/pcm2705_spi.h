/*
  pcm2705_spi.h - Library for interfacing with the PCM2705C USB DAC.
  Created by Andreas Dahlberg, 2014
*/

#ifndef pcm2705_spi_h
#define pcm2705_spi_h

#include "Arduino.h"

const int VENDOR_ID = 0x08BB;  //Texas Instruments
const int PRODUCT_ID = 0x2705; // PCM2705 Audio Codec
//byte DEVICE_STRING[16];
//byte VENDOR_STRING[32];
const byte BM_ATTRIBUTE = 0x80; // Bus-powered
const byte MAX_PWR = 0xFA; // 500 mA
const byte HID_USAGE_ID[3] = {0x01, 0x93, 0x0A}; //AL A/V capture

const byte ADDR = 9;
const byte ST = 11;

const byte D7 = 0;
const byte D6 = 1;
const byte D5 = 2;
const byte D4 = 3;
const byte D3 = 4;
const byte D2 = 5;
const byte D1 = 6;
const byte D0 = 7;

const byte MUTE = D7;
const byte VOLU = D6;
const byte VOLD = D5;
const byte NEXT = D4;
const byte PREV = D3;
const byte STOP = D2;
const byte PLAY = D1;
const byte EXT = D0;

class PCM2705_SPI
{
	public:
		PCM2705_SPI(byte MD, byte MC, byte MS);
		
		void mute();
		void volume_up();
		void volume_down();
		void next();
		void previous();
		void stop();
		void play_pause();
		void send_descriptor_data();
		void extended();
	private:
		void _tick();
		void _send_spi_reg();
		void _send_spi_reg_c();
		void _clear_spi_reg();
		void _set_mode(byte);
		void _send_array(unsigned char*, byte);
		void _send_int(int);
		int _spi_reg;
		byte _MD;
		byte _MC;
		byte _MS;
};

#endif
