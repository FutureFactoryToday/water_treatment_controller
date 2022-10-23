
/* Includes ------------------------------------------------------------------*/
#include "lcd.h"
#include "stm32_adafruit_lcd.h"
#include "Fonts/wtc_fonts.h"
#include "main.h"

#define POLY_X(Z)             ((int32_t)((Points + (Z))->X))
#define POLY_Y(Z)             ((int32_t)((Points + (Z))->Y))

#define MAX_HEIGHT_FONT       35
#define MAX_WIDTH_FONT        35


#define ABS(X) ((X) > 0 ? (X) : -(X))
#define SWAP16(a, b) {uint16_t t = a; a = b; b = t;}


LCD_DrawPropTypeDef DrawProp;

extern LCD_DrvTypeDef  *lcd_drv;

/* Max size of bitmap will based on a font24 (17x24) */
static uint8_t bitmap[MAX_HEIGHT_FONT * MAX_WIDTH_FONT * 2 + OFFSET_BITMAP] = {0};

/* @defgroup STM32_ADAFRUIT_LCD_Private_FunctionPrototypes */ 
static void DrawChar(uint16_t Xpos, uint16_t Ypos, uint8_t *c);
static void SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
  
uint32_t getStringWidth (uint8_t* str);
uint8_t getCharIndex(uint8_t ch);

/**
  * @brief  Initializes the LCD.
  * @param  None
  * @retval LCD state
  */
uint8_t BSP_LCD_Init(void)
{ 
  uint8_t ret = LCD_ERROR;

  /* LCD Init */   
  lcd_drv->Init();
  
  /* Default value for draw propriety */
  DrawProp.BackColor = LCD_DEFAULT_BACKCOLOR;
  DrawProp.TextColor = LCD_DEFAULT_TEXTCOLOR;
  DrawProp.pFont     = (WTC_FONT_t*)&LCD_DEFAULT_FONT;
  
  /* Clear the LCD screen */
  #if LCD_INIT_CLEAR == 1
  BSP_LCD_Clear(LCD_DEFAULT_BACKCOLOR);
  #endif
  
  ret = LCD_OK;
  return ret;
}

/**
  * @brief  Gets the LCD X size.
  * @param  None    
  * @retval Used LCD X size
  */
uint16_t BSP_LCD_GetXSize(void)
{
  return(lcd_drv->GetLcdPixelWidth());
}

/**
  * @brief  Gets the LCD Y size.
  * @param  None   
  * @retval Used LCD Y size
  */
uint16_t BSP_LCD_GetYSize(void)
{
  return(lcd_drv->GetLcdPixelHeight());
}

/**
  * @brief  Gets the LCD text color.
  * @param  None 
  * @retval Used text color.
  */
uint16_t BSP_LCD_GetTextColor(void)
{
  return DrawProp.TextColor;
}

/**
  * @brief  Gets the LCD background color.
  * @param  None
  * @retval Used background color
  */
uint16_t BSP_LCD_GetBackColor(void)
{
  return DrawProp.BackColor;
}

/**
  * @brief  Sets the LCD text color.
  * @param  Color: Text color code RGB(5-6-5)
  * @retval None
  */
void BSP_LCD_SetTextColor(uint16_t Color)
{
  DrawProp.TextColor = Color;
}

/**
  * @brief  Sets the LCD background color.
  * @param  Color: Background color code RGB(5-6-5)
  * @retval None
  */
void BSP_LCD_SetBackColor(uint16_t Color)
{
  DrawProp.BackColor = Color;
}

/**
  * @brief  Sets the LCD text font.
  * @param  fonts: Font to be used
  * @retval None
  */
void BSP_LCD_SetFont(WTC_FONT_t *pFonts)
{
  DrawProp.pFont = pFonts;
}

/**
  * @brief  Gets the LCD text font.
  * @param  None
  * @retval Used font
  */
WTC_FONT_t *BSP_LCD_GetFont(void)
{
  return DrawProp.pFont;
}

/**
  * @brief  Clears the hole LCD.
  * @param  Color: Color of the background
  * @retval None
  */
void BSP_LCD_Clear(uint16_t Color)
{
  lcd_drv->FillRect(0, 0, BSP_LCD_GetXSize(), BSP_LCD_GetYSize(), Color);
}

/**
  * @brief  Clears the selected line.
  * @param  Line: Line to be cleared
  *          This parameter can be one of the following values:
  *            @arg  0..9: if the Current fonts is Font16x24
  *            @arg  0..19: if the Current fonts is Font12x12 or Font8x12
  *            @arg  0..29: if the Current fonts is Font8x8
  * @retval None
  */
void BSP_LCD_ClearStringLine(uint16_t Line)
{ 
  uint32_t color_backup = DrawProp.TextColor; 
  DrawProp.TextColor = DrawProp.BackColor;;
    
  /* Draw a rectangle with background color */
  BSP_LCD_FillRect(0, (Line * DrawProp.pFont->height), BSP_LCD_GetXSize(), DrawProp.pFont->height);
  
  DrawProp.TextColor = color_backup;
  BSP_LCD_SetTextColor(DrawProp.TextColor);
}

/**
  * @brief  Displays one character.
  * @param  Xpos: Start column address
  * @param  Ypos: Line where to display the character shape.
  * @param  Ascii: Character ascii code
  *           This parameter must be a number between Min_Data = 0x20 and Max_Data = 0x7E 
  * @retval None
  */
void BSP_LCD_DisplayChar(uint16_t Xpos, uint16_t Ypos, uint32_t Ascii)
{
	DrawChar(Xpos, Ypos, (uint8_t*)DrawProp.pFont->glyph[getCharIndex(Ascii)]);
}

/**
  * @brief  Displays characters on the LCD.
  * @param  Xpos: X position (in pixel)
  * @param  Ypos: Y position (in pixel)   
  * @param  Text: Pointer to string to display on LCD
  * @param  Mode: Display mode
  *          This parameter can be one of the following values:
  *            @arg  CENTER_MODE
  *            @arg  RIGHT_MODE
  *            @arg  LEFT_MODE   
  * @retval None
  */
uint32_t BSP_LCD_DisplayStringAt(uint16_t Xpos, uint16_t Ypos, uint8_t *Text, Line_ModeTypdef Mode)
{
	uint16_t refcolumn = 1, i = 0;
	uint32_t chCnt = 0, xsize = 0, size = 0; 
	uint8_t  *ptr = Text;
	uint16_t chWidth;
	
	size = getStringWidth(ptr);
	/* Get the text size */
	while (*ptr++) chCnt ++ ;


	/* Characters number per line */
	xsize = (BSP_LCD_GetXSize()/size/chCnt);

	switch (Mode)
	{
	case CENTER_MODE:
	{
	  refcolumn = Xpos - size/ 2;
	  break;
	}
	case LEFT_MODE:
	{
	  refcolumn = Xpos;
	  break;
	}
	case RIGHT_MODE:
	{
	  refcolumn =  - Xpos + size;
	  break;
	}    
	default:
	{
	  refcolumn = Xpos;
	  break;
	}
	}
	chWidth = DrawProp.pFont->glyph[getCharIndex(*Text)]->width;
	/* Send the string character by character on lCD */
	while ((*Text != 0) & ((BSP_LCD_GetXSize() - refcolumn - chWidth) >= chWidth))
	{
	/* Display one character on LCD */
	BSP_LCD_DisplayChar(refcolumn, Ypos, *Text);
	/* Decrement the column position by 16 */
	refcolumn += chWidth;
	/* Point on the next character */
	Text++;
	i++;
		chWidth = DrawProp.pFont->glyph[getCharIndex(*Text)]->width;
	}
	return size;
}

/**
  * @brief  Displays a character on the LCD.
  * @param  Line: Line where to display the character shape
  *          This parameter can be one of the following values:
  *            @arg  0..19: if the Current fonts is Font8
  *            @arg  0..12: if the Current fonts is Font12
  *            @arg  0...9: if the Current fonts is Font16
  *            @arg  0...7: if the Current fonts is Font20
  *            @arg  0...5: if the Current fonts is Font24
  * @param  ptr: Pointer to string to display on LCD
  * @retval None
  */
void BSP_LCD_DisplayStringAtLine(uint16_t Line, uint8_t *ptr)
{
 // BSP_LCD_DisplayStringAt(0, LINE(Line), ptr, LEFT_MODE);
}

/**
  * @brief  Draws a pixel on LCD.
  * @param  Xpos: X position 
  * @param  Ypos: Y position
  * @param  RGB_Code: Pixel color in RGB mode (5-6-5)  
  * @retval None
  */
void BSP_LCD_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGB_Code)
{
  if(lcd_drv->WritePixel != NULL)
  {
    lcd_drv->WritePixel(Xpos, Ypos, RGB_Code);
  }
}
  
/**
  * @brief  Draws an horizontal line.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  Length: Line length
  * @retval None
  */
void BSP_LCD_DrawHLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
  uint32_t index = 0;
  
  if(lcd_drv->DrawHLine != NULL)
  {
    lcd_drv->DrawHLine(DrawProp.TextColor, Xpos, Ypos, Length);
  }
  else
  {
    for(index = 0; index < Length; index++)
    {
      BSP_LCD_DrawPixel((Xpos + index), Ypos, DrawProp.TextColor);
    }
  }
}

/**
  * @brief  Draws a vertical line.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  Length: Line length
  * @retval None
  */
void BSP_LCD_DrawVLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
  uint32_t index = 0;
  
  if(lcd_drv->DrawVLine != NULL)
  {
    lcd_drv->DrawVLine(DrawProp.TextColor, Xpos, Ypos, Length);
  }
  else
  {
    for(index = 0; index < Length; index++)
    {
      BSP_LCD_DrawPixel(Xpos, Ypos + index, DrawProp.TextColor);
    }
  }
}

/**
  * @brief  Draws an uni-line (between two points).
  * @param  x1: Point 1 X position
  * @param  y1: Point 1 Y position
  * @param  x2: Point 2 X position
  * @param  y2: Point 2 Y position
  * @retval None
  */
void BSP_LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0, 
  curpixel = 0;
  
  deltax = ABS(x2 - x1);        /* The difference between the x's */
  deltay = ABS(y2 - y1);        /* The difference between the y's */
  x = x1;                       /* Start x off at the first pixel */
  y = y1;                       /* Start y off at the first pixel */
  
  if (x2 >= x1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }
  
  if (y2 >= y1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }
  
  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    numadd = deltay;
    numpixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    numadd = deltax;
    numpixels = deltay;         /* There are more y-values than x-values */
  }
  
  for (curpixel = 0; curpixel <= numpixels; curpixel++)
  {
    BSP_LCD_DrawPixel(x, y, DrawProp.TextColor);  /* Draw the current pixel */
    num += numadd;                            /* Increase the numerator by the top of the fraction */
    if (num >= den)                           /* Check if numerator >= denominator */
    {
      num -= den;                             /* Calculate the new numerator value */
      x += xinc1;                             /* Change the x as appropriate */
      y += yinc1;                             /* Change the y as appropriate */
    }
    x += xinc2;                               /* Change the x as appropriate */
    y += yinc2;                               /* Change the y as appropriate */
  }
}

/**
  * @brief  Draws a rectangle.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  Width: Rectangle width  
  * @param  Height: Rectangle height
  * @retval None
  */
void BSP_LCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  /* Draw horizontal lines */
  BSP_LCD_DrawHLine(Xpos, Ypos, Width);
  BSP_LCD_DrawHLine(Xpos, (Ypos + Height - 1), Width);
  
  /* Draw vertical lines */
  BSP_LCD_DrawVLine(Xpos, Ypos, Height);
  BSP_LCD_DrawVLine((Xpos + Width - 1), Ypos, Height);
}
                            
/**
  * @brief  Draws a circle.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  Radius: Circle radius
  * @retval None
  */
void BSP_LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  int32_t  D;       /* Decision Variable */ 
  uint32_t  CurX;   /* Current X Value */
  uint32_t  CurY;   /* Current Y Value */ 
  
  D = 3 - (Radius << 1);
  CurX = 0;
  CurY = Radius;
  
  while (CurX <= CurY)
  {
    BSP_LCD_DrawPixel((Xpos + CurX), (Ypos - CurY), DrawProp.TextColor);
    BSP_LCD_DrawPixel((Xpos - CurX), (Ypos - CurY), DrawProp.TextColor);
    BSP_LCD_DrawPixel((Xpos + CurY), (Ypos - CurX), DrawProp.TextColor);
    BSP_LCD_DrawPixel((Xpos - CurY), (Ypos - CurX), DrawProp.TextColor);
    BSP_LCD_DrawPixel((Xpos + CurX), (Ypos + CurY), DrawProp.TextColor);
    BSP_LCD_DrawPixel((Xpos - CurX), (Ypos + CurY), DrawProp.TextColor);
    BSP_LCD_DrawPixel((Xpos + CurY), (Ypos + CurX), DrawProp.TextColor);
    BSP_LCD_DrawPixel((Xpos - CurY), (Ypos + CurX), DrawProp.TextColor);   

    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  } 
}

/**
  * @brief  Draws an poly-line (between many points).
  * @param  Points: Pointer to the points array
  * @param  PointCount: Number of points
  * @retval None
  */
void BSP_LCD_DrawPolygon(pPoint Points, uint16_t PointCount)
{
  int16_t X = 0, Y = 0;

  if(PointCount < 2)
  {
    return;
  }

  BSP_LCD_DrawLine(Points->X, Points->Y, (Points+PointCount-1)->X, (Points+PointCount-1)->Y);
  
  while(--PointCount)
  {
    X = Points->X;
    Y = Points->Y;
    Points++;
    BSP_LCD_DrawLine(X, Y, Points->X, Points->Y);
  }
}

/**
  * @brief  Draws an ellipse on LCD.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  XRadius: Ellipse X radius
  * @param  YRadius: Ellipse Y radius
  * @retval None
  */
void BSP_LCD_DrawEllipse(uint16_t Xpos, uint16_t Ypos, uint16_t XRadius, uint16_t YRadius)
{
  int x = 0, y = -YRadius, err = 2-2*XRadius, e2;
  float K = 0, rad1 = 0, rad2 = 0;
  
  rad1 = XRadius;
  rad2 = YRadius;
  
  K = (float)(rad2/rad1);
  
  do {      
    BSP_LCD_DrawPixel((Xpos-(uint16_t)(x/K)), (Ypos+y), DrawProp.TextColor);
    BSP_LCD_DrawPixel((Xpos+(uint16_t)(x/K)), (Ypos+y), DrawProp.TextColor);
    BSP_LCD_DrawPixel((Xpos+(uint16_t)(x/K)), (Ypos-y), DrawProp.TextColor);
    BSP_LCD_DrawPixel((Xpos-(uint16_t)(x/K)), (Ypos-y), DrawProp.TextColor);      
    
    e2 = err;
    if (e2 <= x) {
      err += ++x*2+1;
      if (-y == x && e2 <= y) e2 = 0;
    }
    if (e2 > y) err += ++y*2+1;     
  }
  while (y <= 0);
}

/**
  * @brief  Draws a bitmap picture loaded in the STM32 MCU internal memory.
  * @param  Xpos: Bmp X position in the LCD
  * @param  Ypos: Bmp Y position in the LCD
  * @param  pBmp: Pointer to Bmp picture address
  * @retval None
  */
void BSP_LCD_DrawBitmap(uint16_t Xpos, uint16_t Ypos, uint8_t *pBmp)
{
	uint16_t height = 0;
	uint16_t width  = 0;

	BITMAPINFOHEADER *ptr;
	ptr= (BITMAPINFOHEADER*)pBmp;
	/* Read bitmap width */
	width = ptr->biWidth;

	/* Read bitmap height */
	height = ptr->biHeight;

	SetDisplayWindow(Xpos, Ypos, width, height);

	if(lcd_drv->DrawBitmap != NULL)
	{
	lcd_drv->DrawBitmap(Xpos, Ypos, pBmp);
	} 
	SetDisplayWindow(0, 0, BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
}

/**
  * @brief  Draws a full rectangle.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  Width: Rectangle width  
  * @param  Height: Rectangle height
  * @retval None
  */
void BSP_LCD_FillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  lcd_drv->FillRect(Xpos, Ypos, Width, Height, DrawProp.TextColor);
}

/**
  * @brief  Draws a full circle.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  Radius: Circle radius
  * @retval None
  */
void BSP_LCD_FillCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  int32_t  D;        /* Decision Variable */ 
  uint32_t  CurX;    /* Current X Value */
  uint32_t  CurY;    /* Current Y Value */ 
  
  D = 3 - (Radius << 1);

  CurX = 0;
  CurY = Radius;
  
  BSP_LCD_SetTextColor(DrawProp.TextColor);

  while (CurX <= CurY)
  {
    if(CurY > 0) 
    {
      BSP_LCD_DrawHLine(Xpos - CurY, Ypos + CurX, 2*CurY);
      BSP_LCD_DrawHLine(Xpos - CurY, Ypos - CurX, 2*CurY);
    }

    if(CurX > 0) 
    {
      BSP_LCD_DrawHLine(Xpos - CurX, Ypos - CurY, 2*CurX);
      BSP_LCD_DrawHLine(Xpos - CurX, Ypos + CurY, 2*CurX);
    }
    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }

  BSP_LCD_DrawCircle(Xpos, Ypos, Radius);
}

/**
  * @brief  Draws a full poly-line (between many points).
  * @param  Points: Pointer to the points array
  * @param  PointCount: Number of points
  * @retval None
  */
void BSP_LCD_FillPolygon(pPoint Points, uint16_t PointCount)
{
  int16_t X = 0, Y = 0, X2 = 0, Y2 = 0, X_center = 0, Y_center = 0, X_first = 0, Y_first = 0, pixelX = 0, pixelY = 0, counter = 0;
  uint16_t  IMAGE_LEFT = 0, IMAGE_RIGHT = 0, IMAGE_TOP = 0, IMAGE_BOTTOM = 0;  
  
  IMAGE_LEFT = IMAGE_RIGHT = Points->X;
  IMAGE_TOP= IMAGE_BOTTOM = Points->Y;
  
  for(counter = 1; counter < PointCount; counter++)
  {
    pixelX = POLY_X(counter);
    if(pixelX < IMAGE_LEFT)
    {
      IMAGE_LEFT = pixelX;
    }
    if(pixelX > IMAGE_RIGHT)
    {
      IMAGE_RIGHT = pixelX;
    }
    
    pixelY = POLY_Y(counter);
    if(pixelY < IMAGE_TOP)
    {
      IMAGE_TOP = pixelY;
    }
    if(pixelY > IMAGE_BOTTOM)
    {
      IMAGE_BOTTOM = pixelY;
    }
  }  
  
  if(PointCount < 2)
  {
    return;
  }
  
  X_center = (IMAGE_LEFT + IMAGE_RIGHT)/2;
  Y_center = (IMAGE_BOTTOM + IMAGE_TOP)/2;
  
  X_first = Points->X;
  Y_first = Points->Y;
  
  while(--PointCount)
  {
    X = Points->X;
    Y = Points->Y;
    Points++;
    X2 = Points->X;
    Y2 = Points->Y;    
    
    BSP_LCD_FillTriangle(X, Y, X2, Y2, X_center, Y_center);
    BSP_LCD_FillTriangle(X, Y, X_center, Y_center, X2, Y2);
    BSP_LCD_FillTriangle(X_center, Y_center, X2, Y2, X, Y);
  }
  
  BSP_LCD_FillTriangle(X_first, Y_first, X2, Y2, X_center, Y_center);
  BSP_LCD_FillTriangle(X_first, Y_first, X_center, Y_center, X2, Y2);
  BSP_LCD_FillTriangle(X_center, Y_center, X2, Y2, X_first, Y_first);
}

/**
  * @brief  Draws a full ellipse.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  XRadius: Ellipse X radius
  * @param  YRadius: Ellipse Y radius  
  * @retval None
  */
void BSP_LCD_FillEllipse(uint16_t Xpos, uint16_t Ypos, uint16_t XRadius, uint16_t YRadius)
{
  int x = 0, y = -YRadius, err = 2-2*XRadius, e2;
  float K = 0, rad1 = 0, rad2 = 0;
  
  rad1 = XRadius;
  rad2 = YRadius;
  
  K = (float)(rad2/rad1);    
  
  do 
  { 
    BSP_LCD_DrawHLine((Xpos-(uint16_t)(x/K)), (Ypos+y), (2*(uint16_t)(x/K) + 1));
    BSP_LCD_DrawHLine((Xpos-(uint16_t)(x/K)), (Ypos-y), (2*(uint16_t)(x/K) + 1));
    
    e2 = err;
    if (e2 <= x) 
    {
      err += ++x*2+1;
      if (-y == x && e2 <= y) e2 = 0;
    }
    if (e2 > y) err += ++y*2+1;
  }
  while (y <= 0);
}

/**
  * @brief  Enables the display.
  * @param  None
  * @retval None
  */
void BSP_LCD_DisplayOn(void)
{
  lcd_drv->DisplayOn();
}

/**
  * @brief  Disables the display.
  * @param  None
  * @retval None
  */
void BSP_LCD_DisplayOff(void)
{
  lcd_drv->DisplayOff();
}

/*******************************************************************************
                            Static Functions
*******************************************************************************/

/**
  * @brief  Draws a character on LCD.
  * @param  Xpos: Line where to display the character shape
  * @param  Ypos: Start column address
  * @param  pChar: Pointer to the character data
  * @retval None
  */
static void DrawChar(uint16_t Xpos, uint16_t Ypos, uint8_t *pChar)
{
	uint16_t height = 0, width = 0;
	int i;
	uint8_t bt;
	int newW;
	int bit = 128;
	int col = 0, row = 0;
	BITMAPINFOHEADER *ptr;
	glyph_t *gl;
	
	height = DrawProp.pFont->height;

	gl = (glyph_t*)pChar;
	width  = gl->width;
  
  /* Fill bitmap header*/
	ptr = (BITMAPINFOHEADER*)bitmap;
	ptr->biHeight = height;
	ptr->biWidth = width;
	ptr->dataSize = (uint32_t)(width*height);
		
  
	newW = width/8;
	if (width%8 != 0){
			newW++;
		}
		bt = gl->bitsArray[row*newW + col++];
		for ( i = 0; i < height*width*2; i=i+2){
			if ((bt & bit) != 0){
			  bitmap[OFFSET_BITMAP + i+1] = (DrawProp.TextColor & 0xFF00)>>8;
							bitmap[OFFSET_BITMAP + i] = DrawProp.TextColor & 0xFF;
			} else {
							uint8_t low = (DrawProp.BackColor & 0xFF00)>>8;
							uint8_t high = DrawProp.BackColor & 0xFF;
							bitmap[OFFSET_BITMAP + i+1] = low;
							bitmap[OFFSET_BITMAP + i] = high;
			}
			
			bit = bit>>1;
			if (bit == 0 || (i/2+1)%width == 0){
				if (col == newW){
					col = 0;
					row++;
					if (row == height){
						break;
					}
				}
				bit = 128;
				if (row >= height){
					break;
				}
				bt = gl->bitsArray[row*newW + col++];
			}
		}
	BSP_LCD_DrawBitmap(Xpos, Ypos, bitmap);
}

/**
  * @brief  Fills a triangle (between 3 points).
  * @param  Points: Pointer to the points array
  * @param  x1: Point 1 X position
  * @param  y1: Point 1 Y position
  * @param  x2: Point 2 X position
  * @param  y2: Point 2 Y position
  * @param  x3: Point 3 X position
  * @param  y3: Point 3 Y position
  * @retval None
  */
void BSP_LCD_FillTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3)
{
  int16_t a, b, y, last;
  int32_t
	  sa   = 0,
	  sb   = 0;
  int16_t  dx12, dy12, dx13, dy13, dx23, dy23;
	
  // Sort coordinates by Y order (y3 >= y2 >= y1)
  if (y1 > y2)
  {
    SWAP16(y1, y2); SWAP16(x1, x2);
  }
  if (y2 > y3) {
    SWAP16(y3, y2); SWAP16(x3, x2);
  }
  if (y1 > y2) {
    SWAP16(y1, y2); SWAP16(x1, x2);
  }

  if(y1 == y3)
  { // Handle awkward all-on-same-line case as its own thing
    a = b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
    if(x3 < a)      a = x3;
    else if(x3 > b) b = x3;
    BSP_LCD_DrawHLine(a, y1, b - a + 1);
    return;
  }

  dx12 = x2 - x1;
  dy12 = y2 - y1;
  dx13 = x3 - x1;
  dy13 = y3 - y1;
  dx23 = x3 - x2;
  dy23 = y3 - y2;
  

  // For upper part of triangle, find scanline crossings for segments
  // 1-2 and 1-3.  If y2=y3 (flat-bottomed triangle), the scanline y2
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y2 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y1=y2
  // (flat-topped triangle).
  if(y2 == y3) last = y2;   // Include y2 scanline
  else         last = y2 - 1; // Skip it

  for(y = y1; y <= last; y++)
  {
    a   = x1 + sa / dy12;
    b   = x1 + sb / dy13;
    sa += dx12;
    sb += dx13;
    /* longhand:
    a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    b = x1 + (x3 - x1) * (y - y2) / (y3 - y1);
    */
    if(a > b) SWAP16(a, b);
    BSP_LCD_DrawHLine(a, y, b - a + 1);
  }

  // For lower part of triangle, find scanline crossings for segments
  // 1-3 and 2-3.  This loop is skipped if y1=y2.
  sa = (int32_t)dx23 * (y - y2);
  sb = (int32_t)dx13 * (y - y1);
  for(; y <= y3; y++)
  {
    a   = x2 + sa / dy23;
    b   = x1 + sb / dy13;
    sa += dx23;
    sb += dx13;
    /* longhand:
    a = x2 + (x3 - x2) * (y - y2) / (y3 - y2);
    b = x1 + (x3 - x1) * (y - y1) / (y3 - y1);
    */
    if(a > b) SWAP16(a, b);
    BSP_LCD_DrawHLine(a, y, b - a + 1);
  }
}

/**
  * @brief  Sets display window.
  * @param  LayerIndex: layer index
  * @param  Xpos: LCD X position
  * @param  Ypos: LCD Y position
  * @param  Width: LCD window width
  * @param  Height: LCD window height  
  * @retval None
  */
static void SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  if(lcd_drv->SetDisplayWindow != NULL)
  {
    lcd_drv->SetDisplayWindow(Xpos, Ypos, Width, Height);
  }  
}

/**
  * @brief  Get display ID
  * @param  none
  * @retval ID number
  */
uint16_t BSP_LCD_ReadID(void)
{
  if(lcd_drv->ReadID)
    return lcd_drv->ReadID();
  else
    return 0;
}

/**
  * @brief  Get pixel
  * @param  Xpos: LCD X position
  * @param  Ypos: LCD Y position
  * @retval RGB565 pixel color
  */
uint16_t BSP_LCD_ReadPixel(uint16_t Xpos, uint16_t Ypos)
{
  if(lcd_drv->ReadPixel != NULL)
    return lcd_drv->ReadPixel(Xpos, Ypos);
  else
    return 0;
}

/**
  * @brief  Draw RGB565 image (draw direction: right then down)
  * @param  Xpos: LCD X position
  * @param  Ypos: LCD Y position
  * @param  Width: image width
  * @param  Height: image height
  * @param  *pData: image data pointer
  * @retval None
  */
void BSP_LCD_DrawRGB16Image(uint16_t Xpos, uint16_t Ypos, uint16_t Xsize, uint16_t Ysize, uint16_t *pData)
{
  lcd_drv->DrawRGBImage(Xpos, Ypos, Xsize, Ysize, pData);
}

/**
  * @brief  Read RGB565 image (draw direction: right then down)
  * @param  Xpos: LCD X position
  * @param  Ypos: LCD Y position
  * @param  Width: image width
  * @param  Height: image height
  * @param  *pData: image data pointer
  * @retval *pData
  */
void BSP_LCD_ReadRGB16Image(uint16_t Xpos, uint16_t Ypos, uint16_t Xsize, uint16_t Ysize, uint16_t *pData)
{
  lcd_drv->ReadRGBImage(Xpos, Ypos, Xsize, Ysize, pData);
}

/**
  * @brief  Set display scroll parameters
  * @param  Scroll    : Scroll size [pixel]
  * @param  TopFix    : Top fix size [pixel]
  * @param  BottonFix : Botton fix size [pixel]
  * @retval None
  */
void BSP_LCD_Scroll(int16_t Scroll, uint16_t TopFix, uint16_t BottonFix)
{
  lcd_drv->Scroll(Scroll, TopFix, BottonFix);
}

uint32_t getStringWidth (uint8_t* str){
	uint32_t size = 0;
	while(*str != 0){
		size += DrawProp.pFont->glyph[getCharIndex(*str)]->width;
		str++;
	}
	return size;
}

//uint8_t getCharIndex(uint8_t ch){
//	if (ch< ' '){
//		return 0;
//	}
//	if (ch>= ' ' && ch <= '~'){
//		return ch - ' ';
//	}
//	
//	return 0;
//}
uint8_t getCharIndex(uint8_t ch){
  if (ch< ' '){
    return 0;
  }
  if (ch>= ' ' && ch <= '~'){
    return ch - ' ';
  }
  if (ch>='А'&& ch <= 'я') {
    return ch - 'А' + '~' - ' ' + 1;
  }
  return 0;
}
