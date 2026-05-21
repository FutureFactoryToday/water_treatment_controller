#include "main.h"

//#define MODE_DELAYED_REGEN "ОТЛОЖЕННАЯ РЕГЕН."

//Public defines sizers

#define DELAYED_REGEN_VALUE_BOX_X 110
#define DELAYED_REGEN_VALUE_BOX_Y TOP_LINE_WIDTH + 70 
#define DELAYED_REGEN_VALUE_BOX_SIZE_X 120
#define DELAYED_REGEN_VALUE_BOX_SIZE_Y 60

#define DELAYED_REGEN_VALUE_X DELAYED_REGEN_VALUE_BOX_X + 14
#define DELAYED_REGEN_VALUE_Y DELAYED_REGEN_VALUE_BOX_Y + 13

//Public defines statusbar sizers
void ShowDelayedRegenCustFrame(void);

void RefreshDelayedRegenCustFrame(void);

void AnimateTimeDelayedRegenCustFrame(void);

void TranslateDelayedRegenCustFrameMSG(void);