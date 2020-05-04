 // These constants won't change.  
 // They're used to give names to the inputs they're attached to

int trigger_pin = 2;

int echo_pin = 3;

int buzzer_pin = 11; 

int time;

int distance; 

const int analogInPin = A0; 
const int analogInPin1 = A1;
const int analogInPin2 = A2;

int sensorvalue = 0;// values read from each pot at 12-bits each

int outputvalue = 0;// Scaled output to 8-bits ready to be sent to computer

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

  // map it to the range of the analog out:
  outputvalue = map(sensorvalue, 0, 1023, 0, 255);
  
  writevalue[0] = outputvalue;   

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
