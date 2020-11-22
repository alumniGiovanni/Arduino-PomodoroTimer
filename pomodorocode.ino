
int message = 0;
unsigned long TASK_TIME = 10000; 
unsigned long BREAK_TIME = 5000;
//unsigned long TASK_TIME = 2400000; // 40 mins
//unsigned long BREAK_TIME = 600000; // 10 mins
unsigned long taskDelayStart = 0; 
unsigned long breakDelayStart = 0; 
bool taskDelayRunning = false; 
bool breakDelayRunning = false; 
bool taskLightOn = false; 

#define taskLampPin 13
#define breakLampPin 12
#define triggerPin 4

void setup() {
  pinMode(triggerPin, INPUT_PULLUP); 
  pinMode(taskLampPin, OUTPUT);        
  digitalWrite(taskLampPin, LOW);
  pinMode(breakLampPin, OUTPUT);        
  digitalWrite(breakLampPin, LOW);


  Serial.begin(9600);
}

void loop() {
  message = digitalRead(triggerPin);
  if (message == 0){ 
    if (!taskLightOn && !taskDelayRunning & !breakDelayRunning){ 
      taskDelayStart = millis(); 
      taskDelayRunning = true;   
      digitalWrite(taskLampPin, HIGH);       
      taskLightOn = true;
      Serial.println("New task! Start working NOW!!!!!!");
    }
      
    if (taskLightOn && taskDelayRunning && ((millis() - taskDelayStart) >= TASK_TIME)) { 
      taskDelayStart += TASK_TIME; 
      taskDelayRunning = false;
      Serial.println("A little break for good employee");
      digitalWrite(breakLampPin, HIGH);         
      digitalWrite(taskLampPin, LOW);         
      taskLightOn = false;

       breakDelayStart = millis(); 
       breakDelayRunning = true;
     }
    
    if (!taskLightOn && breakDelayRunning && ((millis() - breakDelayStart) >= BREAK_TIME)) { 
      breakDelayStart += BREAK_TIME; 
      breakDelayRunning = false;
      Serial.println("break time is over, back to work");
      taskDelayRunning = true;
      taskDelayStart = millis(); 
    digitalWrite(breakLampPin, LOW);       
      digitalWrite(taskLampPin, HIGH);       
      taskLightOn = true;
    }
  }
      
    if (message == 1){ 
      breakDelayRunning = false;
      taskDelayRunning = false;
      if (taskLightOn){
      Serial.println("task complete");
      digitalWrite(taskLampPin, LOW);         
      digitalWrite(breakLampPin, LOW);  
      taskLightOn = false;
          
      }
     Serial.println(" waiting for task"); 
     }
}
