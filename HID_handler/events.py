#!/usr/bin/python
# -*- coding: utf-8 -*

#Based on code written by Masaaki Shibata (http://www.emptypage.jp/notes/pyevent.en.html)


__author__ = 'andreas.dahlberg90@gmail.com (Andreas Dahlberg)'
__version__ = '0.1.0'


class Event(object):
    
	def __init__(self, doc=None):
		self.__doc__ = doc
    
	def __get__(self, obj, objtype=None):
		if obj is None:
			return self
		return EventHandler(self, obj)
    
	def __set__(self, obj, value):
		pass


class EventHandler(object):
	def __init__(self, event, obj):
		self.event = event
		self.obj = obj
		
		
	def _getfunctionlist(self):
		try:
			eventhandler = self.obj.__eventhandler__
		except AttributeError:
			eventhandler = self.obj.__eventhandler__ = {}
		return eventhandler.setdefault(self.event, [])
 

	def add(self, handler_func):
		self._getfunctionlist().append(handler_func)
		return self


	def remove(self, handler_func):
		self._getfunctionlist().remove(handler_func)
		return self
		
		
	def notify(self, earg=None):
		for func in self._getfunctionlist():
			func(self.obj, earg)
