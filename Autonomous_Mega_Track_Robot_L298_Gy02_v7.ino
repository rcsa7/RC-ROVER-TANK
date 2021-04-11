/*** 
 *  Autonomous Arduino Mega Track Robot
 *  Track Robot w/ Arduino Mega 2560, motor shield v3, OLED, and Sharp IR sensors
 *  https://create.arduino.cc/projecthub/MyPartsChest/autonomous-arduino-mega-track-robot-10699d
 *  1-19-2020
 *  by My Parts Chest
 *  https://mypartschest.com
 *  https://mypartschest.blogspot.com/
 *  https://github.com/guillaume-rico/SharpIR_Roberto
 *  
 *  USANDO DRIVER MOTOR L298 KEYSTUDIO
*/
#include <SharpIR_Roberto.h>  // biblioteca específica para o sensor GY21SHARP
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BUZZER_PIN  49   // AX-1205-2 5V
#define LED1 7
#define LED2 8
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SHARP_MODEL 1080 
///#define SHARP_MODEL 100500

/* Model :
  GP2Y0A02YK0F --> 20150
  GP2Y0A21YK0F --> 1080
  GP2Y0A710K0F --> 100500
  GP2YA41SK0F --> 430
--  OBS: PODE SER USADO COM SENSOR:
    SHRP GP2Y0A02---1080 ou  100500
*/

//global vars
bool startup = false;
bool firstLoop = false;
bool motorsOn = false;
int stopTimer = 0;
String heading = "Nao iniciado";

//declar OLED pins
const int SDA_PIN = 20;
const int SDC_PIN = 21;

//Declare pins for motor control
const int dirA = 12;// motor-1
const int dirB = 13;// motor-2
const int speedA = 3;//pin-pwm- motor-1
const int speedB = 11;//pin-pwm- motor-2
const int brakeA = 7;// motor-1
const int brakeB = 8;// motor-2
const int highSpeed = 255;
const int lowSpeed = 240;

// Analog pins for distance sensors
const byte frontSensorPin = A4; // sensor frontal
const byte driverSensorPin = A5; // sensor lateral--esquerdo
const byte passengerSensorPin = A2;// sensor lateral passageiro---direito
const byte rearSensorPin = A3; // sensor ré



// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Create an object instance of the SharpDistSensor class
SharpIR_Roberto frontSensor = SharpIR_Roberto(frontSensorPin, SHARP_MODEL);
SharpIR_Roberto driverSensor = SharpIR_Roberto(driverSensorPin, SHARP_MODEL);
SharpIR_Roberto passengerSensor = SharpIR_Roberto(passengerSensorPin, SHARP_MODEL);
SharpIR_Roberto rearSensor = SharpIR_Roberto(rearSensorPin, SHARP_MODEL);

void setup() {
 // Begin serial communication at a baudrate of 9600:
  Serial.begin(9600);
  //--------------------------------------
  pinMode(LED1, OUTPUT);
   pinMode(LED2, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT); 
  tone(BUZZER_PIN, 200, 200); delay(200); 
  tone(BUZZER_PIN, 500, 400); delay(500); 
  //-------- Setup Channel A & B
  pinMode(dirA, OUTPUT); //Init Motor A (rear-driver's side)
  pinMode(dirB, OUTPUT); //Init Motor B (front-passenger's side)
  pinMode(brakeA, OUTPUT); //Init Brake A
  pinMode(brakeB, OUTPUT); //Init Brake B

  // Init display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.println("Inicializando...");
  display.display(); 
  
  delay(1000);
  startup = false;
  firstLoop = true;
  motorsOn = true;
}

void loop() {

    //------
  Serial.println("-------------");
  Serial.print("-------------");
  float tensao_A2 = analogRead(passengerSensorPin)*5.0/1023.0;
  Serial.print("Tensao do pino A2 em Volts: ");
  Serial.println(tensao_A2);
  //------
  Serial.print("-------------");
  float tensao_A3 = analogRead(rearSensorPin)*5.0/1023.0;
  Serial.print("Tensao do pino A3 em Volts: ");
  Serial.println(tensao_A3);
 //----
  Serial.print("-------------");
  float tensao_A4 = analogRead(frontSensorPin)*5.0/1023.0;
  Serial.print("Tensao do pino A4 em Volts: ");
  Serial.println(tensao_A4);
  //---------
  Serial.print("-------------");
  float tensao_A5 = analogRead(driverSensorPin)*5.0/1023.0;
  Serial.print("Tensao do pino A5 em Volts: ");
  Serial.println(tensao_A5);
  //-----local vars  
  int frontDistance;
  int driverDistance;
  int passengerDistance;
  int rearDistance;
   
  // Obtenha distância dos sensores
  frontDistance = frontSensor.distance();
  driverDistance = driverSensor.distance();
  passengerDistance = passengerSensor.distance();
  rearDistance = rearSensor.distance();


  //update OLED

updateDisplay(frontDistance, driverDistance, passengerDistance, rearDistance,tensao_A2,tensao_A3,tensao_A4,tensao_A5, "Stopped!");

  if (startup)
  {      
    if (frontSensor.distance() > 30)
    {
      firstLoop = false;
      heading = "Forward";

      //--forward B (front motor)
      //--frente B (motor dianteiro)
      move("B", "FWD", highSpeed);            
      //forward A (rear motor)
      move("A", "FWD", lowSpeed); //rear motor is running a little faster than the front motor; so slow it down
                                  // o motor traseiro está funcionando um pouco mais rápido que o motor dianteiro; então diminua a velocidade
      delay(100);
      stopTimer = 0;
    }
             // menos de 30cm; Algo está no caminho
    else    //less than 30cm; something is in the way
    {
      if (heading == "Forward" && !firstLoop) //make sure this isn't at startup and I'm not already turning
                                             // certifique-se de que isso não esteja na inicialização e eu já não esteja girando 
      {
        fullStop(100); //stop during testing to read sensors
                      // pare durante o teste para ler os sensores
      
        //---back up if too close to something
        // --- backup se estiver muito perto de algo
        if (frontSensor.distance() < 10)
        {
          //--forward B (front motor)
          //-- forward B (motor dianteiro)
          move("B", "REV", highSpeed);                
          //--forward A (rear motor)
          //-- forward A (motor traseiro)
          move("A", "REV", lowSpeed); 
          delay(100);          
        }
                  
        if (passengerSensor.distance() > driverSensor.distance()) //what has more distance, left or right?
                                                                 // o que tem mais distância, esquerda ou direita?
        {
          heading = "Turning Right";
          int lastFront = frontSensor.distance();
          
          while (driverSensor.distance() != lastFront)
          {
         
         updateDisplay(frontDistance, driverDistance, passengerDistance, rearDistance,tensao_A2,tensao_A3,tensao_A4,tensao_A5, "Stopped!");
            turnRight(500);
            if (frontSensor.distance() > 30)
            {
              break;      
            }         
          }
        }
        else
        {
          heading = "Turning Left";
          int lastFront = frontSensor.distance();
          
          while (passengerSensor.distance() != lastFront)
          {
           
           updateDisplay(frontDistance, driverDistance, passengerDistance, rearDistance,tensao_A2,tensao_A3,tensao_A4,tensao_A5, "Stopped!");
            turnLeft(500);
            if (frontSensor.distance() > 30)
            {
              break;      
            }              
          }
        }                      
      }
      else
      {
        stopTimer++;
        if (stopTimer > 100)
        {
          heading = "Stopped";
          fullStop(100);
          //display stopped
        
         updateDisplay(frontDistance, driverDistance, passengerDistance, rearDistance,tensao_A2,tensao_A3,tensao_A4,tensao_A5, "Stopped!");
          exit(0);
        }        
      }
    }
  }
  else //loop forever until I put my hand in front of the forward sensor
      // loop para sempre até que eu coloque minha mão na frente do sensor de avanço
  {
    if (frontDistance < 11)
      {
        delay(1000);
        startup = true;
    }
    else
    {
      delay(20);
    }
  }
}

void fullStop(int duration)
{
    move("A", "FWD", 0);
    move("B", "FWD", 0);   
    delay(duration);
}

void turnRight(int duration)
{
    move("A", "FWD", highSpeed);
    move("B", "REV", highSpeed);
    delay(duration);
}

void turnLeft(int duration)
{
    move("A", "REV", highSpeed);
    move("B", "FWD", highSpeed);
    delay(duration);
}

void move(String channel, String direction, int speed )
{
  int motor = dirA;
  int pwm = speedA;
  int brake = brakeA;
  bool highLow = HIGH;

  if (motorsOn)
  {
    if (direction == "REV")
      highLow = LOW;
      
    if (channel == "B")
    {
      motor = dirB;
      pwm = speedB;
      brake = brakeB;
      //reverse directions for motor B
      // direção reversa para motor B
      highLow = !highLow;
    }
  
    if (speed == 0) //brake
    {
      digitalWrite(brake, HIGH);
    }
    else
    {
      digitalWrite(motor, highLow);
      digitalWrite(brake, LOW);
      analogWrite(pwm, speed);
    }    
  }
}




void updateDisplay(int fd, int dd, int pd, int rd, float tensao_A2, float tensao_A3,float tensao_A4, float tensao_A5, String hd)
{
  //write to OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Lib Roberto -V6       Leitura dos Sensores");
  display.setCursor(0, 5);
  display.print("...............");  
  
  // Display sensor readings
  //-----sensor---frente
  display.setCursor(0, 16);
  display.print("Front: ");
  display.setCursor(45, 16);
  display.print(fd);
  display.print(" cm-");
  display.setCursor(84, 16);
  display.print(tensao_A4);
  display.print(" v");
  //--------sensor esquerdo
  display.setCursor(0, 26);  
  display.print("Left: ");
  display.setCursor(45, 26);  
  display.print(dd);
  display.print(" cm-");
  display.setCursor(84, 26);
  display.print(tensao_A5);
  display.print(" v");
  //----------sensor direito
  display.setCursor(0, 36);  
  display.print("Right: ");
  display.setCursor(45, 36);  
  display.print(pd);
  display.print(" cm-");
  display.setCursor(84, 36);
  display.print(tensao_A2);
  display.print(" v");
 //-------sensor re 
  display.setCursor(0, 46);  
  display.print("Rear: ");
  display.setCursor(45, 46);  
  display.print(rd);
  display.print(" cm-");
  display.setCursor(84, 46);
  display.print(tensao_A3);
  display.print(" v");
//------------------
  display.setCursor(0, 56);  
  display.print("Moving: ");
  display.setCursor(45, 56);  
  display.print(hd);  
  
  display.display(); 
}
