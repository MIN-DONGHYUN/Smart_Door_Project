#include <Wire.h>
#include <LiquidCrystal_I2C.h>    // 버튼 코드(첫번째 계속)
#include <SoftwareSerial.h>       //블루투스 코드 (두번째 계속)
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

LiquidCrystal_I2C lcd(0x27,16,2); // LCD 연결
int sensorVal;    //전역변수 설정
int Button20 = 14;    // 버튼 핀 번호 설정  ------------------------------------------------------------------
//int Button10 = 15;   // 버튼 첫번째 옵션 사용하기 위한 설정
int SOUND = 0;

int medlody[] = {987,987,987,987,987,987,1244,987,987,880,783,880,987
,987,987,987,987,987,987,987,880,783,880,783,659,659}; //32, 36, 41, 44, 49, 55, 62
int beat[] = {1,1,4,1,1,4,1,1,1,1,1,1,4,1,1,4,1,1,4,1,1,1,1,1,1,4}; // 맬로디   
int medlodyNum = 26; 

SoftwareSerial btSerial = SoftwareSerial(10,11);    //블루투스 사용하기 위해 
//hd44780_I2Cexp lcd;
const int activeB = 12;   // 부저 12번 
const int trigPin = 3;    //  3,4번 초음파 
const int echoPin = 4; 
int sw1=5;                 // 스위치 
int p = 0;   // 부저 적게 울리기 위해 
int num[10] = {0,1,2,3,4,5,6,7,8,9} ;  //보내는것 
char num2[4] = {0x41,0x42,0x43,0x44};  //int  
int message; 

void setup(){
  
  Serial.begin(2000000);    //통신속도9600으로 설정 
  btSerial.begin(2000000);     ///통신속도 
  pinMode(2, INPUT_PULLUP);  // 핀 2가 항상 프로세서 내부에 있는 pull-up저항 사용
  pinMode(13, OUTPUT);
  pinMode(Button20, INPUT);
  //pinMode(Button10, INPUT);
  pinMode(activeB, OUTPUT);    // 부저 등 설정 // 초음파코드
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(sw1, INPUT_PULLUP);    //버튼 사용위해 
  pinMode(6,OUTPUT);

  lcd.init(); // LCD 초기화
  lcd.backlight();
}

void loop(){

  RESTART:               // goto 위한 설정 
  int bmi;
  int bmidis;
  p = 0;   
  sensorVal = digitalRead(2);     // sensorVal 에 2번 핀 현재 상황 대입 
  boolean Button20_state = digitalRead(Button20);   // 버튼2 상태 설정 
  //boolean Button10_state = digitalRead(Button10);  // 버튼1 읽어 들어오기 위한 설정
  lcd.init(); // LCD 초기화
  lcd.backlight();

  if (SOUND == 100)     // SOUND 100 이면 소리를 울리지 마라 
  {
    noTone(activeB);
    noTone(12);           
  }
                     
  while(digitalRead(sw1) == LOW)    //Button20_state == false)
  {     
     if(digitalRead(2) == HIGH && digitalRead(Button20) == LOW)  // 2번 핀이 high라면 센서 OFF상태 즉 스위치 0 버튼 0 접근센서 0일때   
     {
          lcd.init(); // LCD 초기화
          lcd.backlight(); 
                
          digitalWrite(trigPin, LOW);  // 초기화
          delayMicroseconds(2);
          digitalWrite(trigPin, HIGH);  //초음파 보냄
          delayMicroseconds(10);
          digitalWrite(trigPin, LOW);  // 초음파 끊음

          long timeDistance = pulseIn(echoPin, HIGH);  // 파일 유지시간 반환
          long distance = (timeDistance/2) / 29.1;  //cm로 반환  

          lcd.clear (); //LCD 출력내용 지우기
          lcd.setCursor (0, 0); //LCD 내용 출력 위치 커서 설정 (첫번째줄, 왼쪽 첫번째 칸)
          lcd.print ("distance:");
          lcd.print (distance);
          lcd.print ("cm");
          lcd.setCursor(1, 1); //LCD 내용 출력 위치 커서 설정 (두번째줄, 왼쪽에서 두번째 칸)
                                  //거리마다 소리 차이 내길 바란다!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
          lcd.print("DOOR OPEN !!");                        
          if(distance < 5)
          {
            tone(activeB , 1000);          
          }
          else if (distance >= 5 && distance < 10)
          {
            for(int i=0 ;i<3;i++)
            {
               tone(activeB, 1000);
               delay(200);
               noTone(activeB);
               delay(200);
            }
          }
          else if(distance >= 10 && distance < 15)
          {
             tone(activeB, 1000);
             delay(400);
             noTone(activeB);
             delay(400);
          }
             
          if(distance >= 5)
          {
            noTone(activeB);     
          }
          message = num[0];  // 메세지 보내는것
          Serial.println(num[0]);   // 메세지 보내기 위해
     }
            
  else if(digitalRead(2) == LOW && digitalRead(Button20) == LOW) // 2번 핀이 LOW라면 센서 ON 즉 스위치 0 버튼 0 접근센서 1일때
  {
    /*message = num[1];  // 메세지 보내는것
    Serial.println(num[1]);   // 메세지 보내기 위해*/
     for( int i=0; i<3; i++)        
     {
         message = num[1];  // 메세지 보내는것
         Serial.println(num[1]);   // 메세지 보내기 위해
         lcd.init(); // LCD 초기화
         lcd.backlight();
         lcd.print("Switch sensor"); // 문자열 출력
         lcd.setCursor(0,1);
         lcd.print("error"); // 문자열 출력
         //lcd.print(i); // 문자열 출력
         delay(1000);
         sensorVal = digitalRead(2);
              if(sensorVal== HIGH || digitalRead(Button20) == HIGH) //  2번 핀 현재 상황 대입 (
              {
                 goto RESTART;
              }          
              /*Button10_state = digitalRead(Button10);  // 버튼1 읽어 들어오기 위한 설정
              if(Button10_state == 1)           // 1번 버튼을 누르면 소리 정지하게 만듬
              {
                 noTone(13);
                 goto RESTART;
              } */  
                  
            }
            p++;
            if(p == 1 || p == 2)  
            {
              tone(12,1000);
              delay(1000);
              noTone(12); 
            }
            
           }
           
           else if(digitalRead(2) == HIGH && digitalRead(Button20) == HIGH) // 2번 핀이 LOW라면 센서 ON 즉 스위치 0 버튼 1 접근센서 0일때
           {              
              for( int i=0; i<3; i++)        
              {
              message = num[2];  // 메세지 보내는것
              Serial.println(num[2]);   // 메세지 보내기 위해  
              lcd.init(); // LCD 초기화
              lcd.backlight();
              lcd.print("access sensor"); // 문자열 출력 
              lcd.setCursor(0,1);
              lcd.print("error"); // 문자열 출력
              //lcd.print(i); // 문자열 출력
              delay(1000);
              sensorVal = digitalRead(2);
              if(sensorVal== LOW || digitalRead(Button20) == LOW) //  2번 핀 현재 상황 대입 (
              {
                 goto RESTART;
              }          
              /*Button10_state = digitalRead(Button10);  // 버튼1 읽어 들어오기 위한 설정
              if(Button10_state == 1)           // 1번 버튼을 누르면 소리 정지하게 만듬
              {
                 noTone(13);
                 goto RESTART;
              }  */ 
                  
            }
            p++;
            if(p == 1 || p == 2)
            {
              tone(12,1000);
              delay(1000);
              noTone(12);
            }
            
           }
           
           else  // 즉 스위치 0 버튼 1 접근센서 1일때
           {
              lcd.init(); // LCD 초기화
              lcd.backlight();
              lcd.print("Door close "); // 문자열 출력 
              delay(1000);
              message = num[3];  // 메세지 보내는것
            Serial.println(num[3]);   // 메세지 보내기 위해                               
           }
       }
              
    while(digitalRead(sw1) == HIGH)    //Button20_state == false) // 스위치 1 
    {  
      if(digitalRead(2) == HIGH && digitalRead(Button20) == LOW) // 2번 핀이 LOW라면 센서 ON 즉 스위치 1 버튼 0 접근센서 0일때
           { 
             message = num[4];  // 메세지 보내는것
             Serial.println(num[4]);   // 메세지 보내기 위해             
             lcd.init(); // LCD 초기화
             lcd.backlight();   
             digitalWrite(trigPin, LOW);  // 초기화
             delayMicroseconds(2);
             digitalWrite(trigPin, HIGH);  //초음파 보냄
             delayMicroseconds(10);
             digitalWrite(trigPin, LOW);  // 초음파 끊음

             long timeDistance = pulseIn(echoPin, HIGH);  // 파일 유지시간 반환
             long distance = (timeDistance/2) / 29.1;  //cm로 반환  

             lcd.clear (); //LCD 출력내용 지우기  
             lcd.setCursor (0, 0); //LCD 내용 출력 위치 커서 설정 (첫번째줄, 왼쪽 첫번째 칸)
             lcd.print ("distance:");
             lcd.print (distance);
             lcd.print ("cm");
             lcd.setCursor(1, 1); //LCD 내용 출력 위치 커서 설정 (두번째줄, 왼쪽에서 두번째 칸)
                                  //거리마다 소리 차이 내길 바란다!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
             lcd.print("DOOR OPEN !!");                     
             if(distance < 5)
             {
               tone(activeB , 1000);            
             }
             else if (distance >= 5 && distance < 10)
             {
               for(int i=0 ;i<3;i++)
               {
                  tone(activeB , 1000);
                  delay(200);
                  noTone(activeB);
                  delay(200);
               }
             }
             else if(distance >= 10 && distance < 15)
             {
                tone(activeB , 1000);
                delay(400);
                noTone(activeB);
                delay(400);
             }
             if(distance >= 5)
             {
               noTone(activeB);     
             }
             
           }
                  
      if(digitalRead(Button20) == HIGH || (digitalRead(2) == LOW && digitalRead(Button20) == LOW))  // 2번 핀이 high라면 센서 OFF상태 즉 스위치 1 버튼 1 일때,    
      {                                                                                                                         // 스위치 1 버튼 0 접근센서 1일때
        
          if(btSerial.available())     // 만약 블루투스 송신이 감지되면 
          {             
             bmi = btSerial.parseInt();          //수신 받은 데이터 저장 (parseInt틑 문자를 숫자로 바로 변환하여 받아볼수 있음)
             //Serial.print("bmi 값은 : ");
             //Serial.println(bmi);
          }
 
          digitalWrite(trigPin, LOW);
          delayMicroseconds(2);
          digitalWrite(trigPin, HIGH);
          delayMicroseconds(10);
          digitalWrite(trigPin, LOW);

          long timeDistance = pulseIn(echoPin, HIGH);
          long distance = (timeDistance/2) / 29.1;      

          if (bmi == 0) {
            bmidis=30;
          }
          else if (bmi<=1 && bmi>0){
            bmidis=35;
          }
          else if (bmi<=2 && bmi>1){
            bmidis=40;   
          }
          else if (bmi<=3 && bmi>2){
            bmidis=45;
          }
          else if (bmi>3){
            bmidis=50;
          }

          //Serial.println(bmidis);  // bmidis 확인용 출력 코드
        
          /*if(Button10_state == 1)
          {
            noTone(13);
            goto RESTART;
          }    */                
            
            lcd.clear (); //LCD 출력내용 지우기
            /*lcd.setCursor (0, 0); //LCD 내용 출력 위치 커서 설정 (첫번째줄, 왼쪽 첫번째 칸)
            lcd.print ("distance:");
            lcd.print (distance);
            lcd.print ("cm");
            lcd.setCursor(1, 1); //LCD 내용 출력 위치 커서 설정 (두번째줄, 왼쪽에서 두번째 칸)*/
            if(bmi == 0)       // bmi가 0일때 
            {
              if(distance<10){                
                delay(500);                  
                if(SOUND == 0)
                {
                  tone(12, 1000, 3000);
                  delay(500);
                  noTone(12); 
                  delay(500);
                  SOUND = 100; 
                                                  
                }
              }  
              else if(distance >= 10 && distance < bmidis){                
                delay(500);
                if(SOUND == 0)
                {
                  tone(12, 1000, 3000);
                  delay(500);
                  noTone(12); 
                  delay(500);
                  SOUND = 100;                                                   
                }
              }
              
              else if(distance >= bmidis){
                 delay(500);
                 if(SOUND == 0)
                 {
                    for(int i=0; i< medlodyNum ; i++){
                    tone(12,medlody[i]);
                    delay(125*beat[i]);       //부저 나중에 추가내용 
                    noTone(12);
                    delay(200);
                    SOUND = 100;
                 }                 
                }
                
              }
            } 
            else if(bmi == 1)
            {
              if(distance < 10){
                delay(500);  
                if(SOUND == 0)
                {
                  tone(12, 1000, 3000);
                  delay(500);
                  noTone(12); 
                  delay(500);
                  SOUND = 100;                                 
                }
              }                       
                 
              
  
              else if(distance >= 10 && distance < bmidis){
                delay(500);     
                if(SOUND == 0)
                {
                  tone(12, 1000, 3000);
                  delay(500);
                  noTone(12); 
                  delay(500);
                  SOUND = 100;                                 
                } 
               }
              
              else if(distance >= bmidis){                           
                 delay(500);
                 if(SOUND == 0)
                 {
                    for(int i=0; i< medlodyNum ; i++){
                    tone(12,medlody[i]);
                    delay(125*beat[i]);       //부저 나중에 추가내용 
                    noTone(12);
                    delay(200);
                    SOUND = 100;
                    }                 
                  }
                 
                 }
              }
       
            else if(bmi == 2)
            {
              if(distance<10){
                delay(500);  
                if(SOUND == 0)
                {
                  tone(12, 1000, 3000);
                  delay(500);
                  noTone(12); 
                  delay(500);
                  SOUND = 100;                                 
                }    
               }
                
              else if(distance >= 10 && distance < bmidis){
                delay(500);  
                if(SOUND == 0)
                {
                  tone(12, 1000, 3000);
                  delay(500);
                  noTone(12); 
                  delay(500);
                  SOUND = 100;                                 
                }     
              }
              
              else if(distance >= bmidis){                          
                 delay(500);
                 if(SOUND == 0)
                 {                    
                    for(int i=0; i< medlodyNum ; i++){
                    tone(12,medlody[i]);
                    delay(125*beat[i]);       //부저 나중에 추가내용 
                    noTone(12);
                    delay(200);
                    SOUND = 100;
                    }                 
                  }
                  
               }
              }
            
            else if(bmi == 3)
            {
              if(distance<10){
                delay(500);  
                if(SOUND == 0)
                {
                  tone(12, 1000, 3000);
                  delay(500);
                  noTone(12); 
                  delay(500);
                  SOUND = 100;                                 
                }    
              }
              
  
              else if(distance >= 10 && distance < bmidis){
                delay(500);  
                if(SOUND == 0)
                {
                  tone(12, 1000, 3000);
                  delay(500);
                  noTone(12); 
                  delay(500);
                  SOUND = 100;                                 
                }     
              }
              
              else if(distance >= bmidis){
                 delay(500);
                 if(SOUND == 0)
                 {                    
                    for(int i=0; i< medlodyNum ; i++){
                    tone(12,medlody[i]);
                    delay(125*beat[i]);       //부저 나중에 추가내용 
                    noTone(12);
                    delay(200);
                    SOUND = 100;
                    }                 
                  }
                  
              }

            }
            else
            {
              if(distance<10){
                delay(500);  
                if(SOUND == 0)
                {
                  tone(12, 1000, 3000);
                  delay(500);
                  noTone(12); 
                  delay(500);
                  SOUND = 100;                                 
                }
              }
              
  
              else if(distance >= 10 && distance < bmidis){
                delay(500);  
                if(SOUND == 0)
                {
                  tone(12, 1000, 3000);
                  delay(500);
                  noTone(12); 
                  delay(500);
                  SOUND = 100;                                 
                }
              }
              
              else if(distance >= bmidis){
                 delay(500);
                 if(SOUND == 0)
                 {                    
                    for(int i=0; i< medlodyNum ; i++){
                    tone(12,medlody[i]);
                    delay(125*beat[i]);       //부저 나중에 추가내용 
                    noTone(12);
                    delay(200);
                    SOUND = 100;
                    }                 
                  }
                  
              }
           }
           if(digitalRead(Button20) == LOW && digitalRead(2) == LOW) // 스위치 1, 버튼 0, 접근 1일때 
           {             
              for( int i=0; i<3; i++)        
              {
                if(distance<10)
                {
                  message = num[5];  // 메세지 보내는것
                  Serial.println(num[5]);   // 메세지 보내기 위해
                }
                else if(distance >= 10 && distance < bmidis)
                {
                  message = num[6];  // 메세지 보내는것
                  Serial.println(num[6]);   // 메세지 보내기 위해
                }
                else if(distance >= bmidis) 
                {
                   message = num[7];  // 메세지 보내는것
                   Serial.println(num[7]);   // 메세지 보내기 위해
                }
              lcd.init(); // LCD 초기화
              lcd.backlight();
         
              lcd.print("Switch sensor"); // 문자열 출력
              lcd.setCursor(0,1);
              lcd.print("error"); // 문자열 출력
              //lcd.print(i); // 문자열 출력
              delay(1000);
              
              sensorVal = digitalRead(2);
              if(sensorVal== HIGH || (digitalRead(Button20) == HIGH && sensorVal== LOW)) //  2번 핀 현재 상황 대입 (
              {
                 SOUND = 0;                 
                 goto RESTART;
              }          
              /*Button10_state = digitalRead(Button10);  // 버튼1 읽어 들어오기 위한 설정
              if(Button10_state == 1)           // 1번 버튼을 누르면 소리 정지하게 만듬
              {
                 noTone(13);
                 SOUND = 0;
                 goto RESTART;
              }*/   
                  
            }
            p++;            
            if(p == 1 || p == 2)
            {
              tone(13,1000);
              delay(500);
              noTone(13);
              delay(100);
            }            
           }
           
           else if(digitalRead(Button20) == HIGH && digitalRead(2) == HIGH) // 스위치 1, 버튼 1, 접근 0일때 
           {             
              for( int i=0; i<3; i++)        
              {
                if(distance<10)
                 {
                   message = num[8];  // 메세지 보내는것
                   Serial.println(num[8]);   // 메세지 보내기 위해
                 }
                 else if(distance >= 10 && distance < bmidis)
                 {
                   message = num[9];  // 메세지 보내는것
                      Serial.println(num[9]);   // 메세지 보내기 위해
                 }
                    else if(distance >= bmidis) 
                 {
                   message = num2[0];  // 메세지 보내는것
                   Serial.println(num2[0]);   // 메세지 보내기 위해
                 }
              lcd.init(); // LCD 초기화
              lcd.backlight();
         
              lcd.print("access sensor"); // 문자열 출력 
              lcd.setCursor(0,1);
              lcd.print("error"); // 문자열 출력
              //lcd.print(i); // 문자열 출력
              delay(1000);
              SOUND = 100;
              sensorVal = digitalRead(2);
              if(sensorVal== LOW || (digitalRead(Button20) == LOW && sensorVal== HIGH) ) //  2번 핀 현재 상황 대입 (
              {
                 SOUND = 0;
                 goto RESTART;
              }          
              /*Button10_state = digitalRead(Button10);  // 버튼1 읽어 들어오기 위한 설정
              if(Button10_state == 1)           // 1번 버튼을 누르면 소리 정지하게 만듬
              {
                 noTone(13);
                 SOUND = 0;
                 goto RESTART;
              }*/
           }
           p++;            
            if(p == 1 || p == 2)
            {
              tone(13,1000);
              delay(500);
              noTone(13);
              delay(100);
            }
         }          
         
           else if(digitalRead(2) == LOW && digitalRead(Button20) == HIGH )   //  111 일때
           {   
            if(distance<10)
            {
              message = num2[1];  // 메세지 보내는것
              Serial.println(num2[1]);   // 메세지 보내기 위해
            }
            else if(distance >= 10 && distance < bmidis)
            {
              message = num2[2];  // 메세지 보내는것
              Serial.println(num2[2]);   // 메세지 보내기 위해
            }
            else if(distance >= bmidis) 
            {
              message = num2[3];  // 메세지 보내는것
              Serial.println(num2[3]);   // 메세지 보내기 위해
            }       
            if(SOUND == 0)
            {
               tone(12, 1000, 3000);
               delay(500);
               noTone(12); 
               delay(500);
               SOUND = 100;
             }
             lcd.setCursor (0, 0); //LCD 내용 출력 위치 커서 설정 (첫번째줄, 왼쪽 첫번째 칸)
             lcd.print ("distance:");
             lcd.print (distance);
             lcd.print ("cm");
             lcd.setCursor(1, 1); //LCD 내용 출력 위치 커서 설정 (두번째줄, 왼쪽에서 두번째 칸) 
            
             lcd.print("Door close "); // 문자열 출력 
             delay(1000);
             
           }
                             
      }      
    }
    
}  
 
