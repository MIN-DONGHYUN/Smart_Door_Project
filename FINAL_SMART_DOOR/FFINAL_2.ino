#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>
#define LCD_CS A3 
#define LCD_CD A2 
#define LCD_WR A1 
#define LCD_RD A0 
#define LCD_RESET A4

#define BLACK   0x0000
#define RED     0x001F 
#define BLUE    0xF800 
#define GREEN   0x07E0 
#define CYAN    0x07FF
#define MAGENTA 0xF81F 
#define YELLOW  0xFFE0 
#define WHITE   0xFFFF

unsigned long time_previous, time_current;

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

void setup() {

  
  // put your setup code here, to run once:
  Serial.begin(2000000);
  tft.reset();
  tft.begin(0x9341);

  //까만색으로 배경 초기화
  tft.fillScreen(BLACK);

  //세로모드
  Serial.print(tft.width());
  Serial.print("/");
  Serial.println(tft.height());
  //가로모드
  tft.setRotation(1); //0,1,2,3
  Serial.print(tft.width());
  Serial.print("/");
  Serial.println(tft.height());
 

  float value =0.3;
  int bar_x=70;
  int bar_y=50;
  int bar_width = 30;
  int bar_height = 100;
  //문열림
  tft.fillRect(bar_x,bar_y,30,30,BLACK);
  tft.fillRect(bar_x,bar_y+30,30,70,RED);
  tft.drawRect(bar_x,bar_y,bar_width,bar_height,RED);


  tft.drawFastVLine(140, 30, 180, WHITE);
  
  // 문콕
  tft.drawRect(170,40,140,150,WHITE);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.setCursor(185,50);
  tft.println("DOOR DING");
  tft.setTextSize(2);
  tft.setCursor(180,80);
  tft.print("PREVENTION");

  
  /*tft.setTextColor(GREEN);
  tft.setTextSize(3);
  tft.setCursor(205,150);
  tft.print("SAFE");*/

  

  /*tft.setTextColor(CYAN);
  tft.setTextSize(2);
  tft.setCursor(180,150);
  tft.print("Be Careful");*/
  

  /*tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.setCursor(187,150);
  tft.print("Dangerous");*/

  
  
  
  
}
// 스위치 버튼 접근
void loop() {

    
    while(Serial.available()){
    char data = Serial.read();
    Serial.print(data);
  
    tft.fillScreen(BLACK);
    if(data == 0x30) //000
 {
   float value =0.3;
  int bar_x=70;
  int bar_y=50;
  int bar_width = 30;
  int bar_height = 100;
  //문열림
  tft.fillRect(bar_x,bar_y,30,30,BLACK);
  tft.fillRect(bar_x,bar_y+30,30,70,RED);
  tft.drawRect(bar_x,bar_y,bar_width,bar_height,RED);


  tft.drawFastVLine(140, 30, 180, WHITE);
  
  // 문콕
  tft.drawRect(170,40,140,150,WHITE);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.setCursor(185,50);
  tft.println("DOOR DING");
  tft.setTextSize(2);
  tft.setCursor(180,80);
  tft.print("PREVENTION");


  delay(100);
  
  
  for(int i=0 ; i < 2 ; i++)
  {tft.setTextColor(RED);
  tft.setTextSize(5);
  tft.setCursor(45,75);
  tft.println("/");
  
  delay(250);

  tft.fillRect(45, 80, 25, 25, BLACK);

  delay(250);

  }
    

  
  }

  else if(data == 0x31)    //001
  {
    
  float value =0.3;
  int bar_x=70;
  int bar_y=50;
  int bar_width = 30;
  int bar_height = 100;
  //문열림
  tft.fillRect(bar_x,bar_y,30,30,BLACK);
  tft.fillRect(bar_x,bar_y+30,30,70,RED);
  tft.drawRect(bar_x,bar_y,bar_width,bar_height,RED);


  tft.drawFastVLine(140, 30, 180, WHITE);
  
  // 문콕
  tft.drawRect(170,40,140,150,WHITE);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.setCursor(185,50);
  tft.println("DOOR DING");
  tft.setTextSize(2);
  tft.setCursor(180,80);
  tft.print("PREVENTION");

    
  tft.setTextSize(2);
  tft.setCursor(30,210);
  tft.print("BS");

  delay(800);
  
     
  }

  else if(data == 0x32)    //010
  {
     float value =0.3;
  int bar_x=70;
  int bar_y=50;
  int bar_width = 30;
  int bar_height = 100;
  //문열림
  tft.fillRect(bar_x,bar_y,30,30,BLACK);
  tft.fillRect(bar_x,bar_y+30,30,70,RED);
  tft.drawRect(bar_x,bar_y,bar_width,bar_height,RED);


  tft.drawFastVLine(140, 30, 180, WHITE);
  
  // 문콕
  tft.drawRect(170,40,140,150,WHITE);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.setCursor(185,50);
  tft.println("DOOR DING");
  tft.setTextSize(2);
  tft.setCursor(180,80);
  tft.print("PREVENTION");

  tft.setTextSize(2);
  tft.setCursor(60,210);
  tft.print("AS");

  delay(800);
  }

  else if(data == 0x33)    //011
  {
       float value =0.3;
  int bar_x=70;
  int bar_y=50;
  int bar_width = 30;
  int bar_height = 100;
  //문열림
  tft.fillRect(bar_x,bar_y,30,30,BLACK);
  tft.fillRect(bar_x,bar_y+30,30,70,RED);
  tft.drawRect(bar_x,bar_y,bar_width,bar_height,RED);


  tft.drawFastVLine(140, 30, 180, WHITE);
  
  // 문콕
  tft.drawRect(170,40,140,150,WHITE);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.setCursor(185,50);
  tft.println("DOOR DING");
  tft.setTextSize(2);
  tft.setCursor(180,80);
  tft.print("PREVENTION");

  delay(800);
  }

  else if(data == 0x34)    //100
  {
     float value =0.3;
  int bar_x=70;
  int bar_y=50;
  int bar_width = 30;
  int bar_height = 100;
  //문열림
  tft.fillRect(bar_x,bar_y,30,30,BLACK);
  tft.fillRect(bar_x,bar_y+30,30,70,RED);
  tft.drawRect(bar_x,bar_y,bar_width,bar_height,RED);


  tft.drawFastVLine(140, 30, 180, WHITE);
  
  // 문콕
  tft.drawRect(170,40,140,150,WHITE);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.setCursor(185,50);
  tft.println("DOOR DING");
  tft.setTextSize(2);
  tft.setCursor(180,80);
  tft.print("PREVENTION");


  for(int i=0 ; i < 2; i++)
  {
  tft.setTextColor(RED);
  tft.setTextSize(5);
  tft.setCursor(45,75);
  tft.println("/");
  delay(250);

  tft.fillRect(45, 80, 25, 25, BLACK);

  delay(250);

  
  } 
  }

  else if(data == 0x35)    //101(dan)
  {
       float value =0.3;
  int bar_x=70;
  int bar_y=50;
  int bar_width = 30;
  int bar_height = 100;
  //문열림
  tft.fillRect(bar_x,bar_y,30,30,BLACK);
  tft.fillRect(bar_x,bar_y+30,30,70,RED);
  tft.drawRect(bar_x,bar_y,bar_width,bar_height,RED);


  tft.drawFastVLine(140, 30, 180, WHITE);
  
  // 문콕
  tft.drawRect(170,40,140,150,WHITE);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.setCursor(185,50);
  tft.println("DOOR DING");
  tft.setTextSize(2);
  tft.setCursor(180,80);
  tft.print("PREVENTION");


  tft.setTextSize(2);
  tft.setCursor(30,210);
  tft.print("BS"); 

  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.setCursor(187,150);
  tft.print("Dangerous");

  delay(800);
  }
   
  else if(data == 0x36)    //101(be)
  {
         float value =0.3;
  int bar_x=70;
  int bar_y=50;
  int bar_width = 30;
  int bar_height = 100;
  //문열림
  tft.fillRect(bar_x,bar_y,30,30,BLACK);
  tft.fillRect(bar_x,bar_y+30,30,70,RED);
  tft.drawRect(bar_x,bar_y,bar_width,bar_height,RED);


  tft.drawFastVLine(140, 30, 180, WHITE);
  
  // 문콕
  tft.drawRect(170,40,140,150,WHITE);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.setCursor(185,50);
  tft.println("DOOR DING");
  tft.setTextSize(2);
  tft.setCursor(180,80);
  tft.print("PREVENTION");


  tft.setTextSize(2);
  tft.setCursor(30,210);
  tft.print("BS"); 

  tft.setTextColor(CYAN);
  tft.setTextSize(2);
  tft.setCursor(180,150);
  tft.print("Be Careful");

  delay(800);
  }
  
  else if(data == 0x37)    //101(safe)
  {
         float value =0.3;
  int bar_x=70;
  int bar_y=50;
  int bar_width = 30;
  int bar_height = 100;
  //문열림
  tft.fillRect(bar_x,bar_y,30,30,BLACK);
  tft.fillRect(bar_x,bar_y+30,30,70,RED);
  tft.drawRect(bar_x,bar_y,bar_width,bar_height,RED);


  tft.drawFastVLine(140, 30, 180, WHITE);
  
  // 문콕
  tft.drawRect(170,40,140,150,WHITE);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.setCursor(185,50);
  tft.println("DOOR DING");
  tft.setTextSize(2);
  tft.setCursor(180,80);
  tft.print("PREVENTION");


  tft.setTextSize(2);
  tft.setCursor(30,210);
  tft.print("BS"); 

  tft.setTextColor(GREEN);
  tft.setTextSize(3);
  tft.setCursor(205,150);
  tft.print("SAFE");

  delay(800);
  }
  
  else if(data == 0x38)    //110(dan)
  {
         float value =0.3;
  int bar_x=70;
  int bar_y=50;
  int bar_width = 30;
  int bar_height = 100;
  //문열림
  tft.fillRect(bar_x,bar_y,30,30,BLACK);
  tft.fillRect(bar_x,bar_y+30,30,70,RED);
  tft.drawRect(bar_x,bar_y,bar_width,bar_height,RED);


  tft.drawFastVLine(140, 30, 180, WHITE);
  
  // 문콕
  tft.drawRect(170,40,140,150,WHITE);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.setCursor(185,50);
  tft.println("DOOR DING");
  tft.setTextSize(2);
  tft.setCursor(180,80);
  tft.print("PREVENTION");


  tft.setTextSize(2);
  tft.setCursor(60,210);
  tft.print("AS");

  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.setCursor(187,150);
  tft.print("Dangerous");

  delay(800);
  }
  
  else if(data == 0x39)    //110(be)
  {
         float value =0.3;
  int bar_x=70;
  int bar_y=50;
  int bar_width = 30;
  int bar_height = 100;
  //문열림
  tft.fillRect(bar_x,bar_y,30,30,BLACK);
  tft.fillRect(bar_x,bar_y+30,30,70,RED);
  tft.drawRect(bar_x,bar_y,bar_width,bar_height,RED);


  tft.drawFastVLine(140, 30, 180, WHITE);
  
  // 문콕
  tft.drawRect(170,40,140,150,WHITE);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.setCursor(185,50);
  tft.println("DOOR DING");
  tft.setTextSize(2);
  tft.setCursor(180,80);
  tft.print("PREVENTION");


  tft.setTextSize(2);
  tft.setCursor(60,210);
  tft.print("AS"); 

  tft.setTextColor(CYAN);
  tft.setTextSize(2);
  tft.setCursor(180,150);
  tft.print("Be Careful");

  delay(800);
  }
  
  else if(data == 0x41)    //110(safe)
  {
        float value =0.3;
  int bar_x=70;
  int bar_y=50;
  int bar_width = 30;
  int bar_height = 100;
  //문열림
  tft.fillRect(bar_x,bar_y,30,30,BLACK);
  tft.fillRect(bar_x,bar_y+30,30,70,RED);
  tft.drawRect(bar_x,bar_y,bar_width,bar_height,RED);


  tft.drawFastVLine(140, 30, 180, WHITE);
  
  // 문콕
  tft.drawRect(170,40,140,150,WHITE);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.setCursor(185,50);
  tft.println("DOOR DING");
  tft.setTextSize(2);
  tft.setCursor(180,80);
  tft.print("PREVENTION");


  tft.setTextSize(2);
  tft.setCursor(60,210);
  tft.print("AS"); 

  tft.setTextColor(GREEN);
  tft.setTextSize(3);
  tft.setCursor(205,150);
  tft.print("SAFE");

  delay(800);
  }
  
  else if(data == 0x42)    //111(dan)
  {
      float value =0.3;
  int bar_x=70;
  int bar_y=50;
  int bar_width = 30;
  int bar_height = 100;
  //문열림
  tft.fillRect(bar_x,bar_y,30,30,BLACK);
  tft.fillRect(bar_x,bar_y+30,30,70,RED);
  tft.drawRect(bar_x,bar_y,bar_width,bar_height,RED);


  tft.drawFastVLine(140, 30, 180, WHITE);
  
  // 문콕
  tft.drawRect(170,40,140,150,WHITE);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.setCursor(185,50);
  tft.println("DOOR DING");
  tft.setTextSize(2);
  tft.setCursor(180,80);
  tft.print("PREVENTION");


  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.setCursor(187,150);
  tft.print("Dangerous"); 

  delay(800);
  }
  
  else if(data == 0x43)    //111(be)
  {
        float value =0.3;
  int bar_x=70;
  int bar_y=50;
  int bar_width = 30;
  int bar_height = 100;
  //문열림
  tft.fillRect(bar_x,bar_y,30,30,BLACK);
  tft.fillRect(bar_x,bar_y+30,30,70,RED);
  tft.drawRect(bar_x,bar_y,bar_width,bar_height,RED);


  tft.drawFastVLine(140, 30, 180, WHITE);
  
  // 문콕
  tft.drawRect(170,40,140,150,WHITE);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.setCursor(185,50);
  tft.println("DOOR DING");
  tft.setTextSize(2);
  tft.setCursor(180,80);
  tft.print("PREVENTION");


  tft.setTextColor(CYAN);
  tft.setTextSize(2);
  tft.setCursor(180,150);
  tft.print("Be Careful"); 
  delay(800);
  }
  
  else if(data == 0x44)    //111(safe)
  {
         float value =0.3;
  int bar_x=70;
  int bar_y=50;
  int bar_width = 30;
  int bar_height = 100;
  //문열림
  tft.fillRect(bar_x,bar_y,30,30,BLACK);
  tft.fillRect(bar_x,bar_y+30,30,70,RED);
  tft.drawRect(bar_x,bar_y,bar_width,bar_height,RED);


  tft.drawFastVLine(140, 30, 180, WHITE);
  
  // 문콕
  tft.drawRect(170,40,140,150,WHITE);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.setCursor(185,50);
  tft.println("DOOR DING");
  tft.setTextSize(2);
  tft.setCursor(180,80);
  tft.print("PREVENTION");


  tft.setTextColor(GREEN);
  tft.setTextSize(3);
  tft.setCursor(205,150);
  tft.print("SAFE"); 
  delay(800);
  }
            
}
}
