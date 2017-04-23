# README file

# WRITTEN BY NGUYEN HONG MINH QUAN

## This application is written for Linux OS. 

## https://github.com/QuanVAMK/AppDev2017

### Raspberry Pi acoustic sensor project

### This project will turn a raspberry Pi 3 into an acoustic sensor.

1. Configuration

1.1 Hardware configuration

A raspberry Pi 3 is recommended. If an older version of Pi is used,
corresponding configuration might be changed.<br />
The Pi is mounted with a USB sound card, and a plugged in microphone.
It is recommended to have Ethernet connection for your Pi.


1.2 Software configuration

The USB sound card has to be set as default audio device. To do so, you need
to modify two files with following contents:

Use **“sudo nano /etc/asound.conf”** command and put following content to the file:
```
pcm.!default {
  type plug
  slave {
    pcm "hw:1,0"
  }
}
ctl.!default {
    type hw
    card 1
}
```
Go to your home directory. Use **“nano .asoundrc”** command and put the same content to the file.<br />
Run **“alsamixer”** and you should be able to see that USB sound card is the default audio device.

If you are using Raspbian Jessie, you have to roll back alsa-utils to an
early version.

a. Use **“sudo nano /etc/apt/sources.list”** command and add the last line:
```
deb http://mirrordirector.raspbian.org/raspbian/ jessie main contrib non-free rpi
# Uncomment line below then 'apt-get update' to enable 'apt-get source'
#deb-src http://archive.raspbian.org/raspbian/ jessie main contrib non-free rpi
deb http://mirrordirector.raspbian.org/raspbian/ wheezy main contrib non-free rpi
```
b. Run **“sudo apt-get update”**

c. Run **“sudo aptitude versions alsa-utils”** to check if version 1.0.25 of alsa-util is available:
```
pi@raspberrypi:~ $ sudo aptitude versions alsa-utils
Package alsa-utils:
i   1.0.25-4                                                     oldstable                                 500
p   1.0.28-1                                                     stable                                    500
```
d. Run **“sudo apt-get install alsa-utils=1.0.25-4”** to downgrade.

e. Reboot (if necessary)

f. Run **“arecord -r44100 -c1 -f S16_LE -d5 test.wav”** to test that your microphone is working.<br />
You should see a “test.wav” file in the current folder.

g. Put earphone on. Run **“aplay test.wav”** to check that your recording is okay.


2. Installation configuration

a. Download files from the source: https://github.com/QuanVAMK/AppDev2017 then store them in ONE file<br />
b. Open the Linux terminal and change directory to the folder that contains the source files.<br />
c. Type "make" to compile all the file.<br />
d. Remember to change the language settings into UTF-8 to display the bars.

3. Operating instruction:

a. Run the command "./sound.a" to run the application. You will see a screen displaying the data<br /> 
with bars and information of duration, bits per sample and sample rate.

b. View in DEBUG mode to see the WAV header information by going to "wave.h" file and erase "//" <br />
from "// #define DEBUG".

c. You can send the record information to the server by going to "comm.h" and erase "//" from <br />
"// #define COMM" to enable COMM mode.

d. You can view the past recorded data through this link: http://www.cc.puv.fi/~e1601120/PHP/recordedSound.php
<br />or view it live through this link: http://www.cc.puv.fi/~e1601120/PHP/recordLive.html

e.To stop the program, press Ctrl+C

4. Known bugs:<br/>
The last values of the samples encountered some kind of errors, thus resulting in the last value <br />
being shown may not be correct.

Another problem is that somehow, the date and time taken from the program is 3 hours earlier then <br />
the original time.

5. Files included in this project: main.c wave.h wave.c screen.c screen.h comm.c comm.h makefile 
README.md sound_1.php

Additional files for visualization: sound.php recordLive.html recordedSound.php

6. Copyright and licensing information: This is an open-source project so the user has the freedom
to use the work as he/she wish. No copyright and licensing.

7. Contact information for the distributor or programmer: Name: Nguyen Hong Minh Quan 
<br />Phone number: +358 959 3428 Email:nguyenquan261098@gmail.com

8. Credits and acknowledgements: This project is made through the guidance of Doctor Gao Chao, 
supervisor of Application Development course, Vaasa University of Applied Sciences.



