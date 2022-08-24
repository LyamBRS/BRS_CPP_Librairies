/**************************************************************************************************
**************************************************************************************************
**************************************************************************************************
    ############    ############     ##########
    ############    ############     ##########
              ##              ##   ## 
    ####    ##      ####    ##     ############
    ####    ##      ####    ##     ############
              ##              ##             ##
    ############    ####      ##   ##########
    ############    ####      ##   ##########
***************************************************************************************************
** BRS_LCD.H --- By Shawn Couture *****************************************************************
***************************************************************************************************/

#ifndef BRS_LCD_420
  #define BRS_LCD_420
//================================================================================================//
//	Include
//================================================================================================//
#include <stdio.h>          // Prototype de declarations des fonctions I/O	
#include <ioDS89C450.h>	    // Définition des bits et des registres du microcontrôleur
#include <string.h>
//================================================================================================//
//	Define
//================================================================================================//
#define VERSION_MAJEUR  		0
#define VERSION_MINEUR  		1

#define LINE1 0x80
#define LINE2 0xC0
#define LINE3 0x94
#define LINE4 0xD4

#define P3_2 P3_bit.P32_INT0
#define P3_3 P3_bit.P32_INT0
#define P3_4 P3_bit.P34_T0
#define P3_5 P3_bit.P35_T1


  
class BRS_LCD_Class
 {
//##########################################################################################################################################################//
//##########################################################################################################################################################//              
  private:
//##########################################################################################################################################################//
//##########################################################################################################################################################//
  void vConfigLCD(void);                             // Configures the LCD at 20 chars lenght and 4 rows
  void vErrorCode(unsigned char X, unsigned char Y); // While(1) which the program gets stuck in when wrong coordinates are input.
  void vWaitBusyLcd(void);                           // Waits for the LCD flag to lower.   
  
//##########################################################################################################################################################//
//##########################################################################################################################################################//              
  public:
//##########################################################################################################################################################//
//##########################################################################################################################################################//
  BRS_LCD_Class(void);

//-DRAWING-/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// - [DRAWING]
    void write_Char      (unsigned char X,unsigned char Y,unsigned char  ucSpot);  
    void write_CustomChar(unsigned char X,unsigned char Y,unsigned char  slot);   
    void write_Sentence  (unsigned char X,unsigned char Y,char const     *ucTABLE);
    void write_CharTable (unsigned char X,unsigned char Y,unsigned char  *ucTABLE);
    void write_Int       (unsigned char X,unsigned char Y,unsigned int   ucChar);
  
//-CLEARING-////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// - [CLEARING] 
    void clear_Screen(void);  //clear entire LCD
    void clear_Slot(unsigned char X,unsigned char Y);  //clear a single slot
    void clear_Row(unsigned char Y);   //clear a row of the LCD
    void clear_Column(unsigned char X);   //clear a row of the LCD
 
//-ANIMATED-////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// - [ANIMATED]   
    void clear_SwipeUp   (void);  //clear entire LCD in a swipe  
    void clear_SwipeDown (void);  //clear entire LCD in a swipe  
    void clear_SwipeLeft (void);  //clear entire LCD in a swipe  
    void clear_SwipeRight(void);  //clear entire LCD in a swipe   
    
//-MISCELANIOUS-////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// - [MISCELANIOUS]   
    void misc_LoadingWheel(unsigned char X,unsigned char Y, unsigned char ucCurrent);
    void misc_SaveCustomChar(unsigned char *ucTAB, unsigned char ucSavedSpot);
 };

#endif