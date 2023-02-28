#include "main.h"

//#define MODE_QUANTITY_COUNT "СЧЁТЧИК ВОДЫ"

//Public defines sizers


#define QUANTITY_COUNT_BOX_X 30
#define QUANTITY_COUNT_BOX_Y TOP_BOT_LINE_WIDTH + 70 
#define QUANTITY_COUNT_BOX_SIZE_X 80
#define QUANTITY_COUNT_BOX_SIZE_Y 60

#define QUANTITY_COUNT_VALUE_X QUANTITY_COUNT_BOX_X + 14
#define QUANTITY_COUNT_VALUE_Y QUANTITY_COUNT_BOX_Y + 13


//Public defines statusbar sizers

void ShowQuantityCountServiceFrame(void);

void RefreshQuantityCountServiceFrame(void);

//void AnimateTimeQuantityCountServiceFrame(void);

void TranslateQuantityCountServiceFrameMSG(void);