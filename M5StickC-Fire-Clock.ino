/*
* M5StickC Fire Animation Clock
* By tuenhidiy - 2020.05.21
*/
#include <M5StickC.h>
#include "FireCharacter.c"
#include "FireNumber.c"
#include "Dot.c"

TFT_eSprite Disbuff = TFT_eSprite(&M5.Lcd);

RTC_TimeTypeDef RTC_Time;
RTC_DateTypeDef RTC_Date;

/*
* Month Fire Character Array
*/

char monthName[12][3] = {
  {'J', 'A', 'N'}, {'F', 'E', 'B'}, {'M', 'A', 'R'}, {'A', 'P', 'R'}, {'M', 'A', 'Y'}, {'J', 'U', 'N'},
  {'J', 'U', 'L'}, {'A', 'U', 'G'}, {'S', 'E', 'P'}, {'O', 'C', 'T'}, {'N', 'O', 'V'}, {'D', 'E', 'C'},
};

/*
* Weekday Fire Character Array
*/

char weekdayName[7][3] = {
  {'M', 'O', 'N'}, {'T', 'U', 'E'}, {'W', 'E', 'D'}, {'T', 'H', 'U'}, {'F', 'R', 'I'}, {'S', 'A', 'T'}, {'S', 'U', 'N'},
};

/*
* Fire Number Lookup Array - (0 ~ 9)
*/

const uint8_t *Fire_Number[10][3] = {
  {
    Fire_Zero_0,
    Fire_Zero_1,
    Fire_Zero_2,
  },
  {
    Fire_One_0,
    Fire_One_1,
    Fire_One_2,
  },
  {
    Fire_Two_0,
    Fire_Two_1,
    Fire_Two_2,
  },
  {
    Fire_Three_0,
    Fire_Three_1,
    Fire_Three_2,
  },
  {
    Fire_Four_0,
    Fire_Four_1,
    Fire_Four_2,
  },
  {
    Fire_Five_0,
    Fire_Five_1,
    Fire_Five_2,
  },
  {
    Fire_Six_0,
    Fire_Six_1,
    Fire_Six_2,
  },
  {
    Fire_Seven_0,
    Fire_Seven_1,
    Fire_Seven_2,
  },
  {
    Fire_Eight_0,
    Fire_Eight_1,
    Fire_Eight_2,
  },
  {
    Fire_Nine_0,
    Fire_Nine_1,
    Fire_Nine_2,
  }
  };
/*
* Fire Character Lookup Array - UPPER CASE (A ~ Z)
*/

const uint8_t *Fire_Character[26][3] = {
{
  Fire_A_0,
  Fire_A_1,
  Fire_A_2,
  },
  {
  Fire_B_0,
  Fire_B_1,
  Fire_B_2,
  },
  {
  Fire_C_0,
  Fire_C_1,
  Fire_C_2,
  },
  {
  Fire_D_0,
  Fire_D_1,
  Fire_D_2,
  },
  {
  Fire_E_0,
  Fire_E_1,
  Fire_E_2,
  },
  {
  Fire_F_0,
  Fire_F_1,
  Fire_F_2,
  },
  {
  Fire_G_0,
  Fire_G_1,
  Fire_G_2,
  },
  {
  Fire_H_0,
  Fire_H_1,
  Fire_H_2,
  },
  {
  Fire_I_0,
  Fire_I_1,
  Fire_I_2,
  },
  {
  Fire_J_0,
  Fire_J_1,
  Fire_J_2,
  },
  {
  Fire_K_0,
  Fire_K_1,
  Fire_K_2,
  },
  {
  Fire_L_0,
  Fire_L_1,
  Fire_L_2,
  },
  {
  Fire_M_0,
  Fire_M_1,
  Fire_M_2,
  },
  {
  Fire_N_0,
  Fire_N_1,
  Fire_N_2,
  },
  {
  Fire_O_0,
  Fire_O_1,
  Fire_O_2,
  },
  {
  Fire_P_0,
  Fire_P_1,
  Fire_P_2,
  },
  {
  Fire_Q_0,
  Fire_Q_1,
  Fire_Q_2,
  },
  {
  Fire_R_0,
  Fire_R_1,
  Fire_R_2,
  },
  {
  Fire_S_0,
  Fire_S_1,
  Fire_S_2,
  },
  {
  Fire_T_0,
  Fire_T_1,
  Fire_T_2,
  },
  {
  Fire_U_0,
  Fire_U_1,
  Fire_U_2,
  },
  {
  Fire_V_0,
  Fire_V_1,
  Fire_V_2,
  },
  {
  Fire_W_0,
  Fire_W_1,
  Fire_W_2,
  },
  {
  Fire_X_0,
  Fire_X_1,
  Fire_X_2,
  },
  {
  Fire_Y_0,
  Fire_Y_1,
  Fire_Y_2,
  },
  {
  Fire_Z_0,
  Fire_Z_1,
  Fire_Z_2,
  }
};

/*
* For TIME
*/

int ss1, ss2, mm1, mm2, hh1, hh2, dd1, dd2, jj1, jj2, yy1, yy2, yy3, yy4, wd1, wd2;
int hours, minutes, seconds, years, months, dates, weekdays;

/*
* For HOME BUTTON
*/

unsigned long samplingtime  = 0;
int buttonPushCounter = 0;   
int buttonState = 0;         
int lastButtonState = 0; 

void setup(void)
{ 
  M5.begin();
  pinMode(M5_BUTTON_HOME, INPUT);
  M5.Lcd.fillScreen(WHITE);
  M5.Lcd.setRotation(3);
  Disbuff.createSprite(160, 80);
  Disbuff.setSwapBytes(true);
  
/*
 * RTC Setup
 */  
  
  RTC_TimeTypeDef TimeStruct;
  TimeStruct.Hours   = 19;
  TimeStruct.Minutes = 57;
  TimeStruct.Seconds = 25;
  M5.Rtc.SetTime(&TimeStruct);
  
  RTC_DateTypeDef DateStruct;
  DateStruct.WeekDay = 3;
  DateStruct.Month = 5;
  DateStruct.Date = 21;
  DateStruct.Year = 2020;
  M5.Rtc.SetData(&DateStruct);
}
 
void loop(void)
{
  M5.Rtc.GetTime(&RTC_Time);
  M5.Rtc.GetData(&RTC_Date);
  
  years = int(RTC_Date.Year);
  
  yy1 = (years / 1000);
  yy2 = (years - yy1*1000 ) / 100;
  yy3 = (years - yy1*1000 - yy2*100 ) / 10;
  yy4 = (years - yy1*1000 - yy2*100 - yy3*10);

  months = int(RTC_Date.Month);
  jj1 = months / 10;
  jj2 = months - jj1*10;

  dates = int(RTC_Date.Date);
  dd1 = dates/ 10;
  dd2 = dates - dd1*10;
  
  weekdays = int(RTC_Date.WeekDay);
  wd1 = weekdays/ 10;
  wd2 = weekdays - wd1*10;
  
  hours = int(RTC_Time.Hours);
  hh1 = hours / 10 ;
  hh2 = hours - hh1*10;
  
  minutes = int(RTC_Time.Minutes);
  mm1 = minutes / 10 ;
  mm2 = minutes - mm1*10;
  
  seconds = int(RTC_Time.Seconds);
  ss1 = seconds / 10 ;
  ss2 = seconds - ss1*10;
  
  if ( (unsigned long) (millis() - samplingtime) > 50  )
  {
    buttonState = digitalRead(M5_BUTTON_HOME);
   
    if (buttonState != lastButtonState) 
    {
      if (buttonState == LOW) {
        buttonPushCounter++;
      }
      else 
      {  
      }
    }
    lastButtonState = buttonState;
  
    switch (buttonPushCounter % 4) 
    {
    case 0:
        /*
         * "FIRE TIME" on the startup screen
         */  
          for (int current_animation = 0; current_animation < 3; current_animation++)
          { 
            printFireChar(0, 0, 40, 40, 'F', current_animation);
            printFireChar(40, 0, 40, 40, 'I', current_animation);
            printFireChar(80, 0, 40, 40, 'R', current_animation);
            printFireChar(120, 0, 40, 40, 'E', current_animation);   
            
            printFireChar(0, 40, 40, 40, 'T', current_animation);
            printFireChar(40, 40, 40, 40, 'I', current_animation);
            printFireChar(80, 40, 40, 40, 'M', current_animation);
            printFireChar(120, 40, 40, 40, 'E', current_animation);
                
            Disbuff.pushSprite(0, 0, 0);
            delay(75);
            
            // If BUTTON_HOME is pressed
            if (buttonState == LOW)
            {
              Disbuff.fillSprite(WHITE);
              Disbuff.pushSprite(0, 0, 0);
              break;
            }
          }
      break;
    case 1:
        /*
         * Hour : Minute : Second - Number Animations
         */ 
         
          for (int current_animation = 0; current_animation < 3; current_animation++)
          { 
            Disbuff.pushImage(0, 0, 40, 40, (uint16_t *)Fire_Number[hh1][current_animation]);
            Disbuff.pushImage(0, 40, 40, 40, (uint16_t *)Fire_Number[hh2][current_animation]);
            Disbuff.pushImage(59, 0, 40, 40, (uint16_t *)Fire_Number[mm1][current_animation]);
            Disbuff.pushImage(59, 40, 40, 40, (uint16_t *)Fire_Number[mm2][current_animation]);
            Disbuff.pushImage(119, 0, 40, 40, (uint16_t *)Fire_Number[ss1][current_animation]);
            Disbuff.pushImage(119, 40, 40, 40, (uint16_t *)Fire_Number[ss2][current_animation]);                     
            Disbuff.pushSprite(0, 0, 0);
            delay(75);
            // If BUTTON_HOME is pressed
            if (buttonState == LOW)
              {
              Disbuff.fillSprite(WHITE);
              Disbuff.pushSprite(0, 0, 0);
              break;
              } 
          }        
          
        /*
         * Hour : Minute : Second - Seperated dots
         */
        
          Disbuff.pushImage(44, 20, 11, 17, (uint16_t *)Dot1);  
          Disbuff.pushImage(44, 43, 11, 17, (uint16_t *)Dot2);
          Disbuff.pushImage(103, 20, 11, 17, (uint16_t *)Dot1);  
          Disbuff.pushImage(103, 43, 11, 17, (uint16_t *)Dot2);          
        /*
         * Show Buffer
         */          
          Disbuff.pushSprite(0, 0, 0);
          
          // If BUTTON_HOME is pressed
          if (buttonState == LOW)
            {
              Disbuff.fillSprite(WHITE);
              Disbuff.pushSprite(0, 0, 0);
              break;
            }            
      break;
    case 2:
      /*
       * Weekday & Date Animations
       */        
        for (int current_animation = 0; current_animation < 3; current_animation++)
        {              
          printFireChar(20, 0, 40, 40, weekdayName[weekdays][0], current_animation);
          printFireChar(60, 0, 40, 40, weekdayName[weekdays][1], current_animation);
          printFireChar(100, 0, 40, 40, weekdayName[weekdays][2], current_animation);      
          
          Disbuff.pushImage(40, 40, 40, 40, (uint16_t *)Fire_Number[dd1][current_animation]);
          Disbuff.pushImage(80, 40, 40, 40, (uint16_t *)Fire_Number[dd2][current_animation]);
          
          Disbuff.pushSprite(0, 0, 0);
          delay(75);

          // If BUTTON_HOME is pressed
          if (buttonState == LOW)
            {
              Disbuff.fillSprite(WHITE);
              Disbuff.pushSprite(0, 0, 0);
              break;
            }           
        } 
      break;
    case 3:
      /*
       * Month & Year Animations
       */ 
      
        for (int current_animation = 0; current_animation < 3; current_animation++)
        {          
          printFireChar(20, 0, 40, 40, monthName[months-1][0], current_animation);
          printFireChar(60, 0, 40, 40, monthName[months-1][1], current_animation);
          printFireChar(100, 0, 40, 40, monthName[months-1][2], current_animation);      
          
          Disbuff.pushImage(0, 40, 40, 40, (uint16_t *)Fire_Number[yy1][current_animation]);
          Disbuff.pushImage(40, 40, 40, 40, (uint16_t *)Fire_Number[yy2][current_animation]);
          Disbuff.pushImage(80, 40, 40, 40, (uint16_t *)Fire_Number[yy3][current_animation]);
          Disbuff.pushImage(120, 40, 40, 40, (uint16_t *)Fire_Number[yy4][current_animation]);
          
          Disbuff.pushSprite(0, 0, 0);
          delay(75);
          
          // If BUTTON_HOME is pressed
          if (buttonState == LOW)
            {
              Disbuff.fillSprite(WHITE);
              Disbuff.pushSprite(0, 0, 0);
              break;
            }           
        }
    break;       
    }
  samplingtime = millis();
  }  
}
/*
* For print Fire Character - UPPER CASE
*/

void printFireChar(int32_t x0, int32_t y0, int32_t w, int32_t h, char ch, int32_t current_animation)
  { 
    Disbuff.pushImage(x0, y0, w, h, (uint16_t *)Fire_Character[ch-65][current_animation]);
  }
   
  
