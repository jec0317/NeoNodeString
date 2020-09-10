
/*
 ******************************************************************************
 *Neopixel Multi-Ring Trial by djcrawford
 *For use with Arduino UNO, Nano or compatible device
 *
 *Version 0.1 - orginal design 20200828
 *
 *Free for personal use only, any commerciial use is strictly prohibited by 
 *copyright law.
 *Please attach this header to your design
 *
 *contact: djcrawford@gmail.com
 *******************************************************************************
 */

#include <Adafruit_NeoPixel.h>
#define PWM_PIN    6     //Sets borad PWM pin for data

 int PixNode = 12;        //Total pix per node
 
 int TotalNodes;          //Total number of nodes in string
 int TotalPix;            //Total number of pix in the system
 int brightness;          //Sets initial brightness of each node from 1 (min) to 255 (max)
 int nodeDelay;           //Delay in mS
       

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(TotalPix, PWM_PIN, NEO_GRB + NEO_KHZ800); // grb

void setup() {
RunOnce();
PrintArray();
}

void loop(){ 
// (Will add in the main body once I figure out)
}

void RunOnce( ){
  Serial.begin(9600);

  Serial.println("How many nodes in the string?");    //Asks user for input
  while(Serial.available() == 0){}
  if (Serial.available()>0) {
    TotalNodes = Serial.parseInt();               //checks for incoming data 
    //Clear serial input buffer
    while (Serial.available()>0) {
    Serial.read();
    }     
    if (TotalNodes>=1) {                        //Checks the vailidity of the input
      Serial.print("The total number of nodes is: ");   //Prints string to display
      Serial.println(TotalNodes);   //Display the variable input from user
      }  
    else{
      Serial.println("This is not a known value, please try a value greater than '0'");
      RunOnce();
      }
      Serial.flush();
  }
   
  TotalPix = (TotalNodes*PixNode);  //Total out the number of pixels
  Serial.print("Your total pixel count is: "); //Prints string to display
  Serial.println(TotalPix);  // Displays the total pixels on the string
  Serial.flush();

  Serial.println("Select your brightness from 1 to 255");  //Prints string to display
  while(Serial.available()==0){}
  brightness = 0;    
  if(Serial.available()>0){
    brightness = Serial.parseInt();
    while (Serial.available()>0) {
    Serial.read();
    }       
    if (brightness >=1 && brightness <=255) {             //Defines if user input is valid
      Serial.print("Your brightness will start at: ");
      Serial.println(brightness);     //Shows user variable input
      }
   
  else {                                                    //If not a valid brightness input
    Serial.println("Please select a brightness from 1 to 255");   //Tells user to input the correct number
    Serial.println("Starting over");    //Notifies user that they will be starting over
    RunOnce();
    }
  Serial.flush();
  }
}  
void PrintArray(){
 char buffer[200];        //Sets up buffer size
 uint8_t const arraySize = TotalNodes; //Sets array size
 int LED[arraySize][2];   //Variable array for each node
 uint16_t pin1 = 0;       
 uint16_t pin2 = (PixNode - 1);

   for(uint8_t i =0;i<TotalNodes;i++){
    LED[i][0] = pin1;
    LED[i][1] = pin2;
    pin1=pin1+PixNode;pin2=pin2+PixNode;
    }
   
   for(uint8_t i=0;i<TotalNodes;i++){
    sprintf(buffer,"ledPos[%d][0]= %d\r\nledPos[%d][1]= %d\r\n\r\n",i,LED[i][0],i,LED[i][1]);
    Serial.println(buffer);
    }
}
