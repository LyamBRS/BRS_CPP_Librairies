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
** BRS_LCD.C --- By Shawn Couture *****************************************************************
***************************************************************************************************/

//================================================================================================//
//	Includes
//================================================================================================//

#include "BRS_LCD.h"

//================================================================================================//
//	CONSTRUCTOR
//================================================================================================//
BRS_LCD_Class::BRS_LCD_Class(void)
 {
   vConfigLCD();
   clear_Screen();
 }

//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Class::write_Char(unsigned char X,unsigned char Y, unsigned char ucSpot)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| Thursday Semptember 23 2021, 8:56 
//__________________________________________________________________________________________________
//	Function:	| Writes a single char at the specified coordinates
//			| 
//__________________________________________________________________________________________________
//	Entry:		| X,Y coordinates
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  unsigned char ucSlot;
  unsigned char  __xdata *PtrLCDConfig = (unsigned char*) 0x8000; //config the screen and place de cursor 
  unsigned char  __xdata *PtrLCDChar = (unsigned char*) 0x8002;		// Used to show a character at the cursor position  
  
  if((X>19)||(Y>3)) {vErrorCode(X,Y);}
  else
  {
    //Determine which Collumn is selected
    if(Y == 0) {ucSlot = LINE1;}
    if(Y == 1) {ucSlot = LINE2;}
    if(Y == 2) {ucSlot = LINE3;}
    if(Y == 3) {ucSlot = LINE4;}
    //Add the X value
    ucSlot = ucSlot + X;
    
    // Write the char
    vWaitBusyLcd();
    *PtrLCDConfig = ucSlot;
    vWaitBusyLcd();
    *PtrLCDChar = ucSpot;
    vWaitBusyLcd();
  }
}
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Class::write_CharTable(unsigned char X,unsigned char Y, unsigned char *ucTABLE)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 21/03/2021
//__________________________________________________________________________________________________
//	Function:	| Writes a table variable on a single line, no wrap around.
//			| 
//__________________________________________________________________________________________________
//	Entry:		| X,Y coordinates
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  unsigned char  __xdata *PtrLCDConfig = (unsigned char*) 0x8000; //config the screen and place de cursor 
  unsigned char  __xdata *PtrLCDChar = (unsigned char*) 0x8002;		// Used to show a character at the cursor position 
  unsigned char i;
  unsigned char ucWrite;
  unsigned char ucSlot;
  
  if((X>19)||(Y>3)) {vErrorCode(X,Y);}
  else
  {
    
    //Determine which Collumn is selected
    if(Y == 0) {ucSlot = LINE1;}
    if(Y == 1) {ucSlot = LINE2;}
    if(Y == 2) {ucSlot = LINE3;}
    if(Y == 3) {ucSlot = LINE4;}
    //Add the X value
    ucSlot = ucSlot + X;
    
    /////////Write on LCD///////
    for (i=0; i<80; i++)
    {
      ucWrite = ucTABLE[i];
      if(ucWrite==0){i=81; ucWrite=' ';}
      else
      {
        *PtrLCDConfig = ucSlot;
        vWaitBusyLcd();
        *PtrLCDChar = ucWrite;
        vWaitBusyLcd();
        ucSlot++;
      }
    }
  }
}
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Class::write_Sentence(unsigned char X,unsigned char Y,char const *ucTABLE)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 9:42, thursday september 2021
//__________________________________________________________________________________________________
//	Function:	| Writes a sentence with no wrap around on a single line. However
//			| the sentence is written inside the function entries unlike WriteTable
//__________________________________________________________________________________________________
//	Entry:		| X,Y coordinates
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  unsigned char i;
  unsigned char ucWrite;
  unsigned char ucSlot;
  unsigned char  __xdata *PtrLCDConfig = (unsigned char*) 0x8000; //config the screen and place de cursor 
  unsigned char  __xdata *PtrLCDChar = (unsigned char*) 0x8002;		// Used to show a character at the cursor position
  
  if((X>19)||(Y>3)) {vErrorCode(X,Y);}
  else
  {
    
    //Determine which Collumn is selected
    if(Y == 0) {ucSlot = LINE1;}
    if(Y == 1) {ucSlot = LINE2;}
    if(Y == 2) {ucSlot = LINE3;}
    if(Y == 3) {ucSlot = LINE4;}
    //Add the X value
    ucSlot = ucSlot + X;
    
    /////////Write on LCD///////
    for (i=0; i<80; i++)
    {
      ucWrite = ucTABLE[i];
      if(ucWrite==0){i=81; ucWrite=' ';}
      else
      {
        *PtrLCDConfig = ucSlot;
        vWaitBusyLcd();
        *PtrLCDChar = ucWrite;
        vWaitBusyLcd();
        ucSlot++;
      }
    }
  }
}
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Class::write_Int(unsigned char X,  unsigned char Y,unsigned int ucChar)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 14:55, thursday september 2021
//__________________________________________________________________________________________________
//	Function:	| Writes a 4 digit integer which is always left on the LCD
//__________________________________________________________________________________________________
//	Entry:		| X,Y coordinates
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  unsigned char  __xdata *PtrLCDConfig = (unsigned char*) 0x8000; //config the screen and place de cursor 
  unsigned char  __xdata *PtrLCDChar = (unsigned char*) 0x8002;		// Used to show a character at the cursor position  
  unsigned char ucSlot;
  unsigned char uc1;
  unsigned char uc2;
  unsigned char uc3;
  
  if((X>19)||(Y>3)) {vErrorCode(X,Y);}
  else
  {
    
    //Determine which Collumn is selected
    if(Y == 0) {ucSlot = LINE1;}
    if(Y == 1) {ucSlot = LINE2;}
    if(Y == 2) {ucSlot = LINE3;}
    if(Y == 3) {ucSlot = LINE4;}
    //Add the X value
    ucSlot = ucSlot + X;
    ///////////////MODULOS////////////////////
    if (ucChar < 10)
    {
      uc3 = ' ';
      uc2 = ' ';
      uc1 = ucChar;
      
      uc1 = uc1 + 0x30;
    }
    
    if ((ucChar > 9) && (ucChar < 100))
    {
      uc3 = ' ';
      uc1 = (ucChar - (ucChar%10))/10;
      uc2 = (ucChar%10);
      
      uc1 = uc1 + 0x30;
      uc2 = uc2 + 0x30;
    }
    
    if (ucChar > 99)
    {
      uc1 = (ucChar - ucChar%100)/100;
      uc2 = ((ucChar%100)-(ucChar%10))/10;
      uc3 = (ucChar%10);
      
      uc1 = uc1 + 0x30;
      uc2 = uc2 + 0x30;
      uc3 = uc3 + 0x30;
    }
    
    
    
    vWaitBusyLcd();
    *PtrLCDConfig = ucSlot;
    vWaitBusyLcd();
    *PtrLCDChar = uc1;
    vWaitBusyLcd();
    
    *PtrLCDConfig = ucSlot+1;
    vWaitBusyLcd();
    *PtrLCDChar = uc2;
    vWaitBusyLcd();
    
    *PtrLCDConfig = ucSlot+2;
    vWaitBusyLcd();
    *PtrLCDChar = uc3;
    vWaitBusyLcd();	
  }
}
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Class::write_CustomChar(unsigned char X,unsigned char Y,unsigned char  slot) 
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 29/03/2022
//__________________________________________________________________________________________________
//	Function:	| Writes one of the custom characters on the screen
//__________________________________________________________________________________________________
//	Entry:		| X,Y coordinates, 0-7
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  if((X>19)||(Y>3)) {vErrorCode(X,Y);}
  else
  {
   write_Char(X,Y,slot);
  }
}




//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Class::clear_Screen(void)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 10:04, thursday 16 september 2021
//__________________________________________________________________________________________________
//	Function:	| Instantaniously clears LCD
//__________________________________________________________________________________________________
//	Entry:		| X,Y coordinates
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  
 unsigned char  __xdata *PtrLCDConfig = (unsigned char*) 0x8000; //config the screen and place de cursor 
  vWaitBusyLcd();
  *PtrLCDConfig = 1;
  vWaitBusyLcd();
}

//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Class::clear_Row(unsigned char Y)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 29-03-2022
//__________________________________________________________________________________________________
//	Function:	| Clears a line of the LCD
//__________________________________________________________________________________________________
//	Entry:		| y coordinate
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
 unsigned char ucSlot;
 unsigned char  __xdata *PtrLCDConfig = (unsigned char*) 0x8000; //config the screen and place de cursor 
 unsigned char  __xdata *PtrLCDChar = (unsigned char*) 0x8002;		// Used to show a character at the cursor position
 
  if((Y>3)) {vErrorCode(0,Y);}
  else
  { 
    //Determine which Collumn is selected
    if(Y == 0) {ucSlot = LINE1;}
    if(Y == 1) {ucSlot = LINE2;}
    if(Y == 2) {ucSlot = LINE3;}
    if(Y == 3) {ucSlot = LINE4;}
    
    
    /////////Clear on LCD///////
    for (unsigned char i=0; i<20; i++)
    {
      *PtrLCDConfig = ucSlot;
      vWaitBusyLcd();
      *PtrLCDChar = ' ';
      vWaitBusyLcd();
      ucSlot++;
    }    
  }
}

//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Class::clear_Slot(unsigned char X,unsigned char Y)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 29-03-2022
//__________________________________________________________________________________________________
//	Function:	| Clears a line of the LCD
//__________________________________________________________________________________________________
//	Entry:		| y coordinate
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
 {
  write_Char(X,Y,' ');
 }

//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Class::clear_Column(unsigned char X)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 29-03-2022
//__________________________________________________________________________________________________
//	Function:	| Clears a line of the LCD
//__________________________________________________________________________________________________
//	Entry:		| y coordinate
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
 {
  write_Char(X,0,' ');
  write_Char(X,1,' ');
  write_Char(X,2,' ');
  write_Char(X,3,' ');  
 }





//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Class::vWaitBusyLcd(void)
//__________________________________________________________________________________________________
//  	Creator:	|Stéphane Deschênes 
//	Date made:	| 25/08/2019
//__________________________________________________________________________________________________
//	Function:	| Waits for the LCD flag to lower itself
//			| 
//__________________________________________________________________________________________________
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{

  unsigned char  __xdata *PtrLCDBusy = (unsigned char*) 0x8001;		// Used to read the busy flag

  unsigned char i;
  while ( *PtrLCDBusy & 0x80 );
  for(i=0; i<10; i++);	
}

//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Class::vConfigLCD(void)
//__________________________________________________________________________________________________
//  	Creator:	|Stéphane Deschênes 
//	Date made:	| 25/08/2019
//__________________________________________________________________________________________________
//	Function:	| Configures the LCD to be used.
//			| 
//__________________________________________________________________________________________________
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  unsigned char  __xdata *PtrLCDConfig = (unsigned char*) 0x8000; //config the screen and place de cursor 
  unsigned char  __xdata *PtrLCDBusy = (unsigned char*) 0x8001;		// Used to read the busy flag

  unsigned int i; 
  for(i = 0; i < 12000; i++);	//Activating delay
  while ( *PtrLCDBusy & 0x80 );
  *PtrLCDConfig = 0x38;
  while ( *PtrLCDBusy & 0x80 );
  *PtrLCDConfig = 0x0C;
  while ( *PtrLCDBusy & 0x80 );
  *PtrLCDConfig = 0x06;
  while ( *PtrLCDBusy & 0x80 );	
  *PtrLCDConfig = 0x01;
  while ( *PtrLCDBusy & 0x80 );
  while ( *PtrLCDBusy & 0x80 );  
  *PtrLCDConfig = 1;
  while ( *PtrLCDBusy & 0x80 );  
}









//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Class::vErrorCode(unsigned char X,  unsigned char Y)
//__________________________________________________________________________________________________
//  	Creator:	| Shawn Couture 
//	Date made:	| 16 september 14:55
//__________________________________________________________________________________________________
//	Function:	| Custom LCD Error cod
//			| 
//__________________________________________________________________________________________________
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  unsigned char ucWrite;
  unsigned int i;
  unsigned char erX1;
  unsigned char erX2;
  unsigned char erY1;
  unsigned char erY2;
  unsigned char ucTABLE_ERROR[29] = {' ', 'E', 'R', 'R', 'O', 'R', ' ', 'W', 'R', 'O', 'N', 'G', ' ', 'C', 'O', 'O', 'R','D', 'S', ' ', 'X', '=', '0', '0', 'Y', '=', '0', '0', '\0'};
  unsigned char ucSlot;
  unsigned char  __xdata *PtrLCDConfig = (unsigned char*) 0x8000; //config the screen and place de cursor 
  unsigned char  __xdata *PtrLCDChar = (unsigned char*) 0x8002;		// Used to show a character at the cursor position  
  /////////ERROR CONDITION///////
  if (( Y>3 )||( X>19 ))
  {
   //Clear the LCD
    vWaitBusyLcd();
    *PtrLCDConfig = 1;
    vWaitBusyLcd();
    //Check which one (X or Y) is wrong and write it's value in the table
    if(X>19)
    {
      erX2 = X%10;
      erX1 = ((X  - erX2) / 10);
      //transform into ascii
      erX2 = erX2 + 0x30;
      erX1 = erX1 + 0x30;
    }
    else {erX2='G'; erX1='G';}
    
    if(Y>3) 
    { 
      if (Y>9)
      {
        erY2 = Y%10;
        erY1 = ((Y  - erY2) / 10);
      }
      
      if (Y<10) {erY2=Y; erY1=0;}
      
      //transform into ascii
      erY2 = erY2 + 0x30;
      erY1 = erY1 + 0x30;
      
    }
    else {erY1 = 'G'; erY2 = 'G';}
    /////////STORE ERRORS IN ERROR TABLE
    ucTABLE_ERROR[22] = erX1;
    ucTABLE_ERROR[23] = erX2;
    ucTABLE_ERROR[26] = erY1;
    ucTABLE_ERROR[27] = erY2;
    
    ucSlot = LINE1;
  }
  
  /////////Write on LCD///////
  for (i=0; i<80; i++)
  {
    ucWrite = ucTABLE_ERROR[i];
    if(ucWrite==0){i=81; ucWrite=' ';}
    else
    {
      *PtrLCDConfig = ucSlot;
      vWaitBusyLcd();
      *PtrLCDChar = ucWrite;
      vWaitBusyLcd();
      ucSlot++;
    }
  }
  //WHILE LOOP TO GET STUCK IN  
  while(1)
  {
    P3_5 = 0;
    write_Char(0,0,'!');
    write_Char(19,0,0xff);    
    for(i=0;i<30000;i++);
    for(i=0;i<30000;i++);
    P3_5 = 1;
    write_Char(0,0,0xff);
    write_Char(19,0,'!'); 
    for(i=0;i<30000;i++);
    for(i=0;i<30000;i++);

  }
}

//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Class::misc_SaveCustomChar(unsigned char *ucTAB, unsigned char ucSavedSpot)
//__________________________________________________________________________________________________
//  	Creator:	| Shawn Couture 
//	Date made:	| 23 september 8:56
//__________________________________________________________________________________________________
//	Function:	| Saves a custom character in LCD memory
//			| 
//__________________________________________________________________________________________________
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  unsigned char  __xdata *PtrLCDConfig = (unsigned char*) 0x8000; //config the screen and place de cursor 
  unsigned char  __xdata *PtrLCDChar = (unsigned char*) 0x8002;		// Used to show a character at the cursor position 
 
  unsigned char i;
  
  // determines which is the first char to save it at
  if(ucSavedSpot == 1) {ucSavedSpot = 0x40;}
  if(ucSavedSpot == 2) {ucSavedSpot = 0x48;}
  if(ucSavedSpot == 3) {ucSavedSpot = 0x50;}
  if(ucSavedSpot == 4) {ucSavedSpot = 0x58;}
  if(ucSavedSpot == 5) {ucSavedSpot = 0x60;}
  if(ucSavedSpot == 6) {ucSavedSpot = 0x68;}
  if(ucSavedSpot == 7) {ucSavedSpot = 0x70;}
  if(ucSavedSpot == 8) {ucSavedSpot = 0x78;}
  
  //Loop to save characters one by one
  for(i=0;i<8;i++)
  {
    vWaitBusyLcd();
    *PtrLCDConfig = ucSavedSpot + i;
    vWaitBusyLcd();
    *PtrLCDChar		= ucTAB[i];
  }
  
}
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
void BRS_LCD_Class::misc_LoadingWheel(unsigned char X,unsigned char Y, unsigned char ucCurrent)
//__________________________________________________________________________________________________
//  	Creator:	| Shawn Couture 
//	Date made:	| 27 september 13:30 2021
//__________________________________________________________________________________________________
//	Function:	| Loading wheel function. Input parameter consist of the current location
//			| of the loading wheel
//__________________________________________________________________________________________________
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
{
  //Backup in case number inputed doesnt make sense, without this it would simply not get declared and potentially cause issues
  unsigned char ucDotTable[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  // Determine which frame of the animation we want to show
  if(ucCurrent == 1)  {ucDotTable[1] = 0x04;}
  if(ucCurrent == 2)  {ucDotTable[1] = 0x02;}
  if(ucCurrent == 3)  {ucDotTable[2] = 0x01;}
  if(ucCurrent == 4)  {ucDotTable[3] = 0x01;}
  if(ucCurrent == 5)  {ucDotTable[4] = 0x01;}
  if(ucCurrent == 6)  {ucDotTable[5] = 0x02;}
  if(ucCurrent == 7)  {ucDotTable[5] = 0x04;}
  if(ucCurrent == 8)  {ucDotTable[5] = 0x08;}
  if(ucCurrent == 9)  {ucDotTable[4] = 0x10;}
  if(ucCurrent == 10) {ucDotTable[3] = 0x10;}
  if(ucCurrent == 11) {ucDotTable[2] = 0x10;}
  if(ucCurrent == 12) {ucDotTable[1] = 0x08;}
  
  
  //error code condition
  if((X>19)||(Y>3)) {vErrorCode(X,Y);}
  else
  {
    // Save the character
    misc_SaveCustomChar(ucDotTable,8);
    // Write the custom character
    write_Char(X, Y, 0x07);
    vWaitBusyLcd();
  }
}
