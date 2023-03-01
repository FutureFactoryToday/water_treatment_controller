#include "main.h"

//#define MODE_WASHING_TIME "ВРЕМЯ ПРОМЫВКИ"

//Public defines sizers

#define WASHING_TIME_CUST_VALUE_BOX_X 30
#define WASHING_TIME_CUST_VALUE_BOX_Y TOP_LINE_WIDTH + 70 
#define WASHING_TIME_CUST_VALUE_BOX_SIZE_X 120
#define WASHING_TIME_CUST_VALUE_BOX_SIZE_Y 60

#define WASHING_TIME_CUST_VALUE_X WASHING_TIME_CUST_VALUE_BOX_X + 14
#define WASHING_TIME_CUST_VALUE_Y WASHING_TIME_CUST_VALUE_BOX_Y + 13


//Public defines statusbar sizers

#define MODE_WASH_TIME_X 65
#define MODE_WASH_TIME_Y 13

void ShowWashTimCustFrame(void);

void RefreshWashTimCustFrame(void);

void AnimateTimeWashTimCustFrame(void);

void TranslateWashTimCustFrameMSG(void);