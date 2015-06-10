#Ghost Radio
## is a Bakelite rebuild using an Arduino Uno and SparkFun MP3 Player Shield.

I've hooked mine upto a motion sensor and added number stations and radio days to the MP3 selection. Hence the spooky.

## Requirements
Potentiometer.h
SPI.h
SdFat.h
SdFatUtil.h
SFEMP3Shield.h

## Instructions

1. Test the radio's tuner and volume pots as well as its speaker. If they all work wire these to leads and pin to the Arduino. If they don't work, remove the elements and replace with off the shelf speakers and pots of your choosing. Be careful of the gross insulation (often asbestos!!).
2. Close the radio back up.
3. Load up your mini SD card.
4. Flash the Uno with the provided script.
