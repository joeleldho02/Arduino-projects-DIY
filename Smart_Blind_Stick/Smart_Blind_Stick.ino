const int trigger = 3; //Trigger pin of 1st Sesnor
const int echo = 2; //Echo pin of 1st Sesnor
const int Buzz = 13; //Echo pin of 1st Sesnor
const int Remote = A0; //Echo pin of 1st Sesnor
const int Light = A1; //Echo pin of 1st Sesnor

long time_taken;
int dist;
int Signal;
int Intens;
int similar_count;

void setup() {
Serial.begin(9600); 
pinMode(Buzz,OUTPUT);
digitalWrite(Buzz,LOW);
pinMode(trigger, OUTPUT); 
pinMode(echo, INPUT); 

}

/*###Function to calculate distance###*/
void calculate_distance(int trigger, int echo)
{
digitalWrite(trigger, LOW);
delayMicroseconds(2);
digitalWrite(trigger, HIGH);
delayMicroseconds(10);
digitalWrite(trigger, LOW);

time_taken = pulseIn(echo, HIGH);
dist= time_taken*0.034/2;
if (dist>300)
dist=300;
}

void loop() {
//infinite loopy
calculate_distance(trigger,echo);
Signal = analogRead(Remote);
Intens = analogRead(Light);

//Check if Remote is pressed
int temp = analogRead(Remote);
similar_count=0;
while (Signal==temp)
{
 Signal = analogRead(Remote);
 similar_count++;
}

//If remote pressed
if (similar_count<100)
{
  Serial.print(similar_count); Serial.println("Remote Pressed");
  digitalWrite(Buzz,HIGH);delay(3000);digitalWrite(Buzz,LOW);
}

//If very dark
if (Intens<200)
{
  Serial.print(Intens); Serial.println("Bright Light");
  digitalWrite(Buzz,HIGH);delay(200);digitalWrite(Buzz,LOW);delay(200);digitalWrite(Buzz,HIGH);delay(200);

  digitalWrite(Buzz,LOW);delay(200);
  delay(500);
}

//If very bright
if (Intens>800)
{
  Serial.print(Intens); Serial.println("Low Light");
  digitalWrite(Buzz,HIGH);delay(500);digitalWrite(Buzz,LOW);delay(500);digitalWrite(Buzz,HIGH);delay(500);

  digitalWrite(Buzz,LOW);delay(500);
}

if (dist<75)
{
  Serial.print(dist); Serial.println("Object Alert");
  
  digitalWrite(Buzz,HIGH);
  for (int i=dist; i>0; i--)
    delay(10);

  digitalWrite(Buzz,LOW);
  for (int i=dist; i>0; i--)
    delay(10);
    
}

Serial.print("dist=");
Serial.println(dist);
Serial.print("Similar_count=");
Serial.println(similar_count);
Serial.print("Intens=");
Serial.println(Intens);
}
