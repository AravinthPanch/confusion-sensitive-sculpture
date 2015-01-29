/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 19/04/14.
 * Project: Confusion
 */


#include <SPI.h>           // SPI library
#include <SdFat.h>         // SDFat Library
#include <SdFatUtil.h>     // SDFat Util Library
#include <SFEMP3Shield.h>  // Mp3 Shield Library

SdFat sd; // Create object to handle SD functions
SFEMP3Shield MP3player; // Create Mp3 library object

const uint8_t volume = 0; // MP3 Player volume 0=max, 255=lowest (off)
const uint16_t monoMode = 1;  // Mono setting 0=off, 3=max
const int TouchPin=5;

void setup()
{ 
  pinMode(TouchPin, INPUT);
  Serial.begin(9600);
  initSD();  // Initialize the SD card
  initMP3Player(); // Initialize the MP3 Shield
}


void loop()
{  
  int sensorValue = digitalRead(TouchPin);
  if(sensorValue==1){
      Serial.println("ON");
      MP3player.playMP3("track001.mp3");
  }
  else {      
    Serial.println("OFF");
    if (MP3player.isPlaying())
      MP3player.stopTrack();
    }
}



// initSD() initializes the SD card and checks for an error.
void initSD()
{
  //Initialize the SdCard.
  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) 
    sd.initErrorHalt();
  if(!sd.chdir("/")) 
    sd.errorHalt("sd.chdir");
}

// initMP3Player() sets up all of the initialization for the
// MP3 Player Shield. It runs the begin() function, checks
// for errors, applies a patch if found, and sets the volume/
// stero mode.
void initMP3Player()
{
  uint8_t result = MP3player.begin(); // init the mp3 player shield
  if(result != 0) // check result, see readme for error codes.
  {
    // Error checking can go here!
  }
  MP3player.setVolume(volume, volume);
  MP3player.setMonoMode(monoMode);
}

