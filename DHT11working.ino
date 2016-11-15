#include <SimpleDHT.h>
#include <LedControl.h>

int pinDHT11 = 2;
SimpleDHT11 dht11;
int DIN = 12;
int CS =  11;
int CLK = 10;
LedControl lc=LedControl(DIN,CLK,CS,0);  
  
void setup() {
  Serial.begin(115200); //sets the data rate to 115200 bits per second
  lc.shutdown(0,false);// turn off power saving, enables display
  lc.setIntensity(0,8);// sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
}

void loop() {
  
  // if output is NULL or if sensor does not work
  byte temperature = 0; 
  byte humidity = 0;
  if (dht11.read(pinDHT11, &temperature, &humidity, NULL)) {
    Serial.print("Read DHT11 failed."); // if the sensor does not work/ does not give any output i.e. = NULL, displays error on the serial port
    return;
  }
  int temperature_fahrenheit=int(temperature*1.8)+32; //calculates the temperature in degree fahrenheit, is optional and temperature variable can be used to use temperature in degree celcius
  Serial.print(temperature_fahrenheit); Serial.print(" *F, "); // returns temperature in Fahrenheit
  Serial.print((int)humidity); Serial.println(" %"); // returns Relative Humidity (R.H.) in %
  if(temperature_fahrenheit<75 && temperature_fahrenheit>65) //optimum condition, can be changed
  {
  //light up the temp column with 5 rows
   for(int row=0;row<5;row++)
    lc.setLed(0,0,row,true); 
  }
  else if (temperature_fahrenheit>=75) //above optimum condition
  {
    //light up the temp column with more than 5 rows
    for(int row=0;row<7;row++)
    lc.setLed(0,0,row,true);
  }
  else if (temperature_fahrenheit<=65) //below optimum condition
  {
    //light up the temp column with less than 5 rows
    for(int row=0;row<3;row++)
    lc.setLed(0,0,row,true);
  }
  if((int)humidity<55 && (int)humidity>45) //optimum condition, can be changed
  {
  //light up the humidity column with 5 rows
   for(int row=0;row<5;row++)
    lc.setLed(0,2,row,true); 
  }
  else if((int)humidity>=55) //above optimum condition
  {
    //light up the humidity column with more than 5 rows
    for(int row=0;row<7;row++)
    lc.setLed(0,2,row,true);
  }
  else if ((int)humidity<=45) //below optimum condition
  {
    //light up the humidity column with less than 5 rows
    for(int row=0;row<3;row++)
    lc.setLed(0,2,row,true);
  }
  delay(2000); //wait for 2 seconds before switching the LED off
  for (int row=0; row<8; row++)
  {
    for (int col=0; col<8; col++)
    {
      lc.setLed(0,col,row,false); // turns off LED at col, row
    }
  }
  // DHT11 sampling rate is 1HZ.
  delay(1000); // After 1 sec run the loop again
}

