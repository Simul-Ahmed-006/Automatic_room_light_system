

const int pirPin = 2;
const int relayPin = 3;
const int buzzerPin = 4;
const int ldrPin = 5; 
const int ledPin = 6;

int blutoothState = 0;  // state 0 means system off
int pirState = 0; // add reset button to reset pir state
int ldrData =0;  // Declare ldrData as a global variable
int pirData = 0;
const int bluetoothTx = 10;
const int bluetoothRx = 11;


void ReadSensor() {
  pirData = digitalRead(pirPin);
  ldrData = digitalRead(ldrPin);
  readSerial();

  if (pirData == HIGH && blutoothState == 1 && ldrData == 1) 
  {
      delay(10);
      pirData = digitalRead(pirPin);
      ldrData = digitalRead(ldrPin);
      readSerial();

      if (pirData == HIGH && blutoothState == 1 && ldrData == 1) 
      {
        pirState = 1;  // Fix: Use assignment instead of comparison
      }
  }
  else
  {
    pirState = 0;
  }
}


void readSerial()
{
  if(Serial.available()> 0)
  {
   char terminalRead = Serial.read();

   if(terminalRead == 'A')
   {
    blutoothState = 1;
   }
   else if (terminalRead == 'B')
   {
     blutoothState = 0;
   }
   if (terminalRead == 'A' || terminalRead == 'B'|| terminalRead == 'C'|| terminalRead == 'D')
   {
    pirState = 0;
   }
    Serial.println(terminalRead);

  }
}


void SequrityControl() {
 
   if (blutoothState == 0 ) 
  {
    digitalWrite(ledPin, LOW);
  }
  else
  {
    digitalWrite(ledPin, HIGH);
  }
  if (blutoothState == 1 && ldrData == 1 && pirData == 1)  // ldr 1 mean night
  {  // 1 means night
    digitalWrite(relayPin, LOW);
    digitalWrite(buzzerPin, HIGH);
    delay(1000);
    digitalWrite(buzzerPin, LOW);
  }
  else if(blutoothState == 0 || ldrData == 0 || pirData == 0)
  {  
    delay(5000);
    if(blutoothState == 0 || ldrData == 0 || pirData == 0)
    {  
     digitalWrite(relayPin, HIGH);
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ldrPin, INPUT);  // Fix: Set ldrPin as INPUT
  pinMode(ledPin, OUTPUT);

  digitalWrite(relayPin, HIGH);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);
}

void loop() {


    ReadSensor();

    SequrityControl();

  

  Serial.print("pirData ");
  Serial.println(pirData);
  Serial.print("ldrData ");
  Serial.println(ldrData);
  Serial.print("blutoothState ");
  Serial.println(blutoothState);
  Serial.print("pirState ");
  Serial.println(pirState);

  // SequrityControl();
}