int led_Pin = 13;                                      // initializing the led pin

int output_Pin = A0;                                // initializing the sensor output pin

//initializng other variables

double alpha = 0.75;

int period = 200;
int k = 0;

double change = 0.0;
double time1 = 0.0;
double time2 = 0.0;
double rate = 0.0;


void setup ( )                           // Code written in it will only run once.

{

  pinMode (led_Pin, OUTPUT);                   // declaring led pin as output

  Serial.begin (115200);                                   // setting baud rate at 115200

}




void loop ()
{

     k=0;
     Serial.println("Please wait..........");    
     while(k<10)                                     // applying another condition
     {
      int rawValue = analogRead (led_Pin);
      //Serial.print("rawValue " ); //Debug Prints. Open Serial Monitor with Baud set to 115200
      //Serial.println(rawValue);   // Debug Prints
      if(rawValue)                         // reading from the sensor
      {
       if(k==0) {
          time1=millis();
          //Serial.print("Time1 is "); // Debug Prints
          //Serial.println(time1);   // Debug Prints
       }
       k++;
       
       while(rawValue);
       delay (800);
      }
     }
     
     // applying the formula for calculating the heart beat

      time2=millis();
      //Serial.print("Time2 is "); // Debug Prints
      //Serial.println(time2);   //Debug Prints. 
      
      rate=time2-time1;

      //Serial.print("Initial rate: "); //Debug Prints
      //Serial.println(rate);   //Debug Prints
      
      rate=rate/10;

      //Serial.print("average rate : "); // Debug Prints
      //Serial.println(rate);  //Debug Prints
      
      rate=60000.0/rate;

      Serial.print("Heart beat rate: "); 
      Serial.println(rate);    
       k=0;
       rate=0;

    
    delay (period);

} 
