PCM2705 SPI Library
===========


PCM2705 SPI library is a bitbang SPI implementation which makes it possible to interface with the PCM2705 USB DAC from Texas Instruments. The library should also work with PCM2705C, PCM2707 and PCM2707C but this has not been tested.

##### FEATURES
The library provides an easy to use interface to PCM2705 USB DACs. Playback on the computer that is  connected to the PCM2705 can be controlled by eight different HID-states. All available HID-states are supported and are listed below. 

* mute
* volume_up
* volume_down
* next
* previous
* stop
* play_pause
* extended

See the PCM2705 datasheet for more information about the HID-states.

If you want custom actions on the computer for HID-commands you can use the supplied python module "hid_catch".


##### USAGE
Connect your three selected digital pins (ex. 10,12,13) to the MD, MS and MC pin one the PCM2705 chip. See pin placement in the datashet. Check out the supplied example for usage instructions.


##### INSTALLATION
1. Move the PCM2705 directory to the libraries directory in your sketchbook. Create this directory if it does not exist. 
2. Start/Restart Arduino IDE. The library should now be ready to use.


##### UNINSTALLATION
1. Delete the PCM2705 directory from your libraries directory.


##### DEVELOPMENT
Support for serial programming of the internal descriptor data is planned for an future release.
See the PCM2705 datasheet for more information about the internal descriptor data.


##### LINKS
[GitHub page](https://github.com/Andreasdahlberg/pcm2705_spi)

[PCM2705 datasheet](http://www.ti.com/lit/ds/symlink/pcm2705.pdf)


