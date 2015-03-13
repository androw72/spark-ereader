/*
  SD card test 
   
 This example shows how use the utility libraries on which the'
 SD library is based in order to get info about your SD card.
 Very useful for testing a card when you're not sure whether its working or not.
  
 The circuit:
  * SD card attached to SPI bus as follows:
  Refer to "libraries/SdFat/Sd2Card_config.h" 

 created  28 Mar 2011
 by Limor Fried 
 modified 16 Mar 2011
 by Tom Igoe
 modified for Maple(STM32 micros)/libmaple
 17 Mar 2012
 by dinau
 */
 // include the SD library:

#include "application.h"
#include "sd-card-library.h"
#include "ereader.h"
#include "picture.h"
#define IMAGEFILE   image_270

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

//EReader ereader;

// SOFTWARE SPI pin configuration - modify as required
// The default pins are the same as HARDWARE SPI
const uint8_t chipSelect = A2;    // Also used for HARDWARE SPI setup
const uint8_t mosiPin = A5;
const uint8_t misoPin = A4;
const uint8_t clockPin = A3;

uint16_t UNICODE_MSG[11] = {25105, 20204, 29233, 30717, 36882, 31185, 25216, 0};

SYSTEM_MODE(AUTOMATIC);

void setup()
{
  Serial.begin(115200);
  while (!Serial.available());
  
  //Serial.print("\nEreader...\n");
  ereader.setup(EPD_2_7);

  
   //for(int ii=0; ii < 4; ii++){
  
    //ereader.sleep(4000);
    ereader.clear();
    delay(1000);
    ereader.image_flash(IMAGEFILE);
    delay(1000);
    //ereader.display_wif("/IMAGES/LENA.WIF", 0, 0);
    //ereader.display_wif("/IMAGES/WYOLUM.WIF", 0, 0);
    //ereader.show();
    //delay(1000);
   
    ereader.EPD.end();
    //} 
  
   
  
  
  Serial.print("\nmy_test: nInitializing SD card...");
  
  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  // Initialize HARDWARE SPI with user defined chipSelect
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {

  // Initialize SOFTWARE SPI (uncomment and comment out above line to use)
//  if (!card.init(mosiPin, misoPin, clockPin, chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card is inserted?");
    Serial.println("* Is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    return;
  } else {
   Serial.println("Wiring is correct and a card is present."); 
  }

  // print the type of card
  Serial.print("\nCard type: ");
  switch(card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    return;
  }

  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("\nVolume type is FAT");
  Serial.println(volume.fatType(), DEC);
  Serial.println();
  
  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize *= 512;                         // SD card blocks are always 512 bytes
  Serial.print("Volume size (bytes): ");
  Serial.println(volumesize);
  Serial.print("Volume size (Kbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Mbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);

  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);
  
  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
}


// main loop
unsigned long int loop_count = 0;

void loop() {
  Serial.println("start of loop()");
  if(loop_count % 4 == 0){
    for(int i=0; i < 264; i+=8){
      for(int j=0; j < 176; j+=8){
	ereader.setpix(i, j, true);
      }
    }
    // ereader.draw_box(0, 0, 7, 7, true, true);
    ereader.draw_line(0, 0, 4, 4, true);
    
    ereader.setpix(10, 10, true);
    int x = 0, y = 0;
    for(int i=0; i < 20; i++){

      //               0  0           8         8  // first run
      ereader.draw_box(x    ,     x, x + 8 + i    , x + 8 + i    , true, true);
      //                   1      1              7              7  // first run
      ereader.draw_box(x + 1, x + 1, x + 8 + i - 1, x + 8 + i - 1, false, true);
      x += 8 + i;
    }
    x = 20;
    for(int y=0; y < 176;){
      ereader.draw_box(x, y, x + 8, y + 8, true, true);
      ereader.draw_box(x + 1, y + 1, x + 8 - 1, y + 8 - 1, false, true);
      x += 8;
      y += 8;
    }
    x = 39;
    for(int y=0; y < 176;){
      ereader.draw_box(    x,     y, x + 8    , y + 8    , true, true);
      ereader.draw_box(x + 1, y + 1, x + 8 - 1, y + 8 - 1, false, true);
      x += 9;
      y += 9;
    }
    x = 48;
    for(int y=0; y < 176;){
      ereader.draw_box(    x,     y, x + 8    , y + 8    , true, true);
      ereader.draw_box(x + 1, y + 1, x + 8 - 1, y + 8 - 1, false, true);
      x += 10;
      y += 10;
    }
    x = 59;
    for(int y=0; y < 176;){
      ereader.draw_box(    x,     y, x + 9    , y + 9    , true, true);
      // ereader.draw_box(x + 1, y + 1, x + 8 - 1, y + 8 - 1, false, true);
      x += 11;
      y += 11;
    }
 }
  else if(loop_count % 4 == 1){
    ereader.display_wif("/IMAGES/WYOLUM.WIF", 0, 0);
    ereader.put_unicode(30, 40, UNICODE_MSG, true);
  }
  else if(loop_count % 4 == 2){
    ereader.display_wif("/IMAGES/LENA.WIF", 0, 0);
  }
  else{
    ereader.display_wif("/IMAGES/AANDJ.WIF", -264 / 2,  176 / 2);
    ereader.display_wif("/IMAGES/AANDJ.WIF",  264 / 2, -176 / 2);
    ereader.display_wif("/IMAGES/CAT_SM.WIF", 264 / 2, 176 / 2);
    ereader.display_wif("/IMAGES/APHRODIT.WIF", 0, 0);
    ereader.toggle_ellipse(random(0, 264), random(0, 176), 20, 20, false);
    ereader.put_ascii(random(0, 200), random(16, 150), "WyoLum ROCKS!!", true);
    //ereader.put_bigascii(random(0, 200), random(16, 16), "WyoLum ROCKS!!", true);
    for(uint8_t yy=0; yy < 6; yy++){
      ereader.setpix(128, yy, true); // draw some pixels
    }
    ereader.put_unicode(10, 140, UNICODE_MSG, true);
    ereader.toggle_line(70, 0, 120, 50);
  }

  loop_count++;
  ereader.show();
  // while(1)
  ereader.EPD.end();
  delay(4000);
  //ereader.sleep(4000); // allows EPD to power off gracefully
  //ereader.wake();
}