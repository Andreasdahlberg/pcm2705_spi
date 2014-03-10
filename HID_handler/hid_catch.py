#!/usr/bin/python
# -*- coding: utf-8 -*


__author__ = 'andreas.dahlberg90@gmail.com (Andreas Dahlberg)'
__version__ = '0.1.0'


import usb.core
import usb.util
import sys
import events
import threading
import time


class NoDeviceError(Exception):
	"""Exception raised when device is not found"""    
	
	def __init__(self, msg):
		pass
		#print 'Device %s:%s does not exist' % (msg[0], msg[1])



class ListenHID(threading.Thread):
	HID_event = events.Event()
	def __init__(self, vendor_id, product_id, intf_nr, conf_nr):
		super(ListenHID, self).__init__()
		self.stop_flagg = False
		self.intf_nr = intf_nr
		#Get the correct USB device
		self._dev = usb.core.find(idVendor=vendor_id, idProduct=product_id)
		if self._dev == None:
			raise NoDeviceError([vendor_id, product_id])
		
		#Detach interface from kernel driver 
		if self._dev.is_kernel_driver_active(self.intf_nr) == True:
			self._dev.detach_kernel_driver(self.intf_nr)
		
		#Get interface with the selected configuration
		conf = self._dev.get_active_configuration()
		intf = conf[(self.intf_nr, conf_nr)]
		
		#Get endpoint
		self._endp = usb.util.find_descriptor(intf, custom_match = lambda e:  usb.util.endpoint_direction(e.bEndpointAddress) == usb.util.ENDPOINT_IN)
		
	
	def run(self):
		"""Start to listen for HID commands"""
		while not self.stop_flagg:
			try:
				#TODO: Find how many bytes to read automagical or 
				#      take size as a parameter
				data = self._endp.read(2, None)
				self.HID_event.notify(data[0])

			except usb.core.USBError as err:
				#Ignore timeout errors(110)
				if err.errno != 110:
					print(err)
					sys.exit(err.errno)
					
		#TODO: Get this to work!
		#if self._dev.is_kernel_driver_active(2) == False:
		#	self._dev.attach_kernel_driver(2)

