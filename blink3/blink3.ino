#define LED1 D1 //Led in NodeMCU at pin D1
#define LED2 D5 //Led in NodeMCU at pin D2 
#define LED3 D4 

void setup() 
{
 pinMode(LED1, OUTPUT);   //LED1 D1 pin as output 
 pinMode(LED2, OUTPUT);   //LED2 D5 pin as output 
 pinMode(LED3, OUTPUT);   
}
 void loop() // runs/loops below code infinitely
{
 digitalWrite(LED1, HIGH); //turn on LED
 delay(400); 
 digitalWrite(LED1, LOW); //turn off LED
 delay(400);
 digitalWrite(LED2, HIGH); //turn on LED
 delay(400);            
 digitalWrite(LED2, LOW); //turn off LED
 delay(400); 
  digitalWrite(LED3, HIGH); //turn on LED
 delay(400);            
 digitalWrite(LED3, LOW); //turn off LED
 delay(400); 
//delay defines duration in ms for which LED is on/off or in actual way, its //the duration for which program waits here on this line of code 
}