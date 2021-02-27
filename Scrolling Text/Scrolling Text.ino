/***************************************************************************************************************************************************************************************
  Title:       Scrolling text

  Version:     04(edited from : Scrolling Text for Animated Mask)
  History:     Change from version 03: only edit speed scrolling and text
  Goal:        
  Hardware:    Arduino Pro Mini (3.3 V, 8 Mhz) ATMEGA328 
  LCD:         LCD Display SSD1306 Driver 3.3V 0.91 Inch 128x32 IIC I2C White
  Sensors:     n.a. 
  Software:    IDE Arduino 1.8.13; Adafruit_BusIO 1.7.2; Adafruit_GFX 1.10.4; Adafruit_SSD1306 2.4.3!!!!; Adafruit_VEML6075 2.1.0;
  Energy:      Powered by rechargeable Li-Ion Battery 3.7V 3400mAh with charger module (FC-75) with protection
  Storage:     No data storage
  Remarks:     Code taken from https://www.youtube.com/watch?v=sTYPuDMPva8 - engineered by the scientist formerly known as Naegeli
  Remarks:     https://www.instructables.com/Animated-Mask/             
**************************************************************************************************************************************************************************************/  
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_VEML6075.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>

Adafruit_SSD1306 myScreen(-1);            //Create the object myScreen 

char message[]="Untirta Robotic Club";                   //Initiate an array for the scrolling text, change it to text you want
char setupscreen1[]="Setup";     //Initiate an array for the text1 of the setup screen
char setupscreen2[]=".......";         //Initiate an array for the text2 of the setup screen
char setupscreen3[]="27/02/2021";         //Initiate an array for the text3 of the setup screen

int x;                                    //Variable used as a coordinate which is recalculated each "round" to make the illusion of a scrolling text 
int minX;                                 //Variable: Length of "message" in pixels

void setup(){
    myScreen.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    x=myScreen.width();                  //Function to find the with of the screen, and set it to x for the first round - text starts scrolling from right to left 
    minX=-20* strlen(message);           //Normal fond size is 5x8 (x*y), with TexSize(4)one character is 20 pixels (x)- so length of the string multiplied with -20 should display the entire text before starting again 
    myScreen.setTextSize(1);             //Set the fond size;
    myScreen.setTextColor(WHITE);        //Set to text color
    myScreen.setRotation(2);             //As the screen is mounted on the mask the text orientation has to be set accordingly
    myScreen.clearDisplay();             //All pixels are off
    myScreen.setCursor(0,1);             //Set the cursor for the setup up screen
    myScreen.println(setupscreen1);      //Print the characters in the setupscreen1 array and jump to the next line
    myScreen.println(setupscreen2);      //Print the characters in the setupscreen2 array and jump to the next line
    myScreen.print(setupscreen3);        //Print the characters in the setupscreen3 array
    myScreen.display();                  //Call this method for the changes to make effect
    delay(5000);                         //Wait for 5 seconds so one can read the setup screen
}

void loop(){
  myScreen.clearDisplay();              //All pixels are off
  myScreen.setTextSize(4);              //Set the fond size; 4 is biggest text size for this display; 5x8 is the standard according to the library with a factor 4 is y=32 equal to hight of screen (128x32)
  myScreen.setCursor(x,1);              //Set the coordinates to start the scrolling text - only x is varied due to scrolling text 
  myScreen.print(message);              //Print the characters from array called message at location x,1
  myScreen.display();                   //Call this method for the changes to make effect
  x=x-7;                                //Calculate the x-value for the next round - sort of speed control for scrolling text
  if(x < minX)x = myScreen.width();     //Loops so long as x is smaller than the pixel length of the message
}
