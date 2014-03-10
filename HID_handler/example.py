#!/usr/bin/python
# -*- coding: utf-8 -*

#This script will listen to the selected device and print HID-states

__author__ = 'andreas.dahlberg90@gmail.com (Andreas Dahlberg)'
__version__ = '0.1.0'


from hid_catch import ListenHID
	
def handle_HID_event(sender, earg):
	try:
		print(COMMANDS[earg])
	except KeyError:
		print('<Error> Unknown command')




def run_example():
	#Vendor id and product id can be found with lsusb
	VENDOR_ID = 0x08BB   #Texas Instruments
	PRODUCT_ID = 0x2705  # PCM2705 Audio Codec
	#Look in the datasheet for interface and configuration number
	INTERFACE = 2
	CONFIGURATION = 0
	
	COMMANDS = {1: 'mute', 2: 'volume up', 4: 'volume down', 8: 'next',
				16: 'previous', 32: 'stop', 64: 'play/pause', 128: 'extended'}
	
	try:
		l = ListenHID(VENDOR_ID, PRODUCT_ID, 2, 0)
		l.HID_event.add(handle_HID_event)
		l.start()
		
		while 1:
			#Do work here
			time.sleep(40)
			
	except KeyboardInterrupt:
		#Enable stop_flagg to kill ListenHID thread
		l.stop_flagg = True
		
		
if __name__ == "__main__":
	run_example()

