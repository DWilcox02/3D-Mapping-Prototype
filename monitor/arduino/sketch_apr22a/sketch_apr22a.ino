 
/* Reads 3 analog input pin, maps the result to a range from 0 to 255
 and uses the result is sent in an 8 byte buffer to the computer.
 
 */

// These constants won't change.  They're used to give names
// Analog input pins that the potentiometer is attached to

int trigger_pin = 2;

int echo_pin = 3;

int buzzer_pin = 11; 

int time;

int distance; 

const int analogInPin = A0; 
const int analogInPin1 = A1;
const int analogInPin2 = A2;

int sensorvalue = 0;// values read from each pot at 12-bits each
int sensorvalue1 = 0;
int sensorvalue2 = 0;

int outputvalue = 0;// Scaled output to 8-bits ready to be sent to computer
int outputvalue1 = 0;
int outputvalue2 = 0;


unsigned char writevalue [8] = {52, 53, 54, 55, 56, 57, 58, 59};

void setup() 
{
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  pinMode (trigger_pin, OUTPUT); 
  pinMode (echo_pin, INPUT);
  pinMode (buzzer_pin, OUTPUT);
}

void loop() 
{
  // read the analog in value:
  sensorvalue = analogRead(analogInPin);            
//  sensorvalue1 = analogRead(analogInPin1);
//  sensorvalue2 = analogRead(analogInPin2);
//  
  // map it to the range of the analog out:
  outputvalue = map(sensorvalue, 0, 1023, 0, 255);
//  outputvalue1 = map(sensorvalue1, 0, 1023, 0, 255);
//  outputvalue2 = map(sensorvalue2, 0, 1023, 0, 255);
  
  writevalue[0] = outputvalue;
//  writevalue[2] = outputvalue;
       

  // print the results to the serial monitor:
//  Serial.print("sensor = " );                       
//  Serial.print(writevalue[0]);
  
  //Serial.print("\t");
  // wait 10 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  digitalWrite (trigger_pin, HIGH);

    delayMicroseconds (10);

    digitalWrite (trigger_pin, LOW);

    time = pulseIn (echo_pin, HIGH);

    distance = (time * 0.034) / 2;

    writevalue[1] = distance;

    Serial.write(writevalue[0]);
    delay(10);
    Serial.write(writevalue[1]);
}
