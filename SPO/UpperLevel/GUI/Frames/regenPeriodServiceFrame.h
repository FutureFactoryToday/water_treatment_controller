#include "main.h"

//#define MODE_REGEN_PERIOD "ПЕРИОД РЕГЕНЕРАЦИИ"

//Public defines sizers


#define REGEN_PERIOD_VALUE_BOX_X 30
#define REGEN_PERIOD_VALUE_BOX_Y TOP_BOT_LINE_WIDTH + 70 
#define REGEN_PERIOD_VALUE_BOX_SIZE_X 80
#define REGEN_PERIOD_VALUE_BOX_SIZE_Y 60

#define REGEN_PERIOD_VALUE_X REGEN_PERIOD_VALUE_BOX_X + 14
#define REGEN_PERIOD_VALUE_Y REGEN_PERIOD_VALUE_BOX_Y + 13


//Public defines statusbar sizers

//extern int8_t regenPeriod;

void ShowRegenPeriodServiceFrame(void);

void RefreshRegenPeriodServiceFrame(void);

void AnimateTimeRegenPeriodServiceFrame(void);

void TranslateRegenPeriodServiceFrameMSG(void);