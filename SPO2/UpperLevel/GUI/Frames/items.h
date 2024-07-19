#include "main.h"

//Main Frame
extern const uint8_t* ITEM_MAIN_FRAME[];

//Clock Set Frame
extern const uint8_t* ITEM_CLOCKSET_FRAME[];
extern const uint8_t* ITEM_CALENDAR_FRAME[];
//TimeSet Frame
extern const uint8_t* ITEM_TIME_ruText[];
//menuFrame
#define MODE_CUSTOMER "Пользователь"
extern const uint8_t* ITEM_MENU[];
//Pincode Frame
extern const uint8_t* ITEM_PINCODE_FRAME[];
//serviceMenuFrame
#define MODE_SERVICE "Инженер"
extern const uint8_t* ITEM_SERVICE_MENU[];

//historyMenuFrame
#define MODE_HISTORY "История"
extern const uint8_t* ITEM_HISTORY_ERROR[];
extern const uint8_t* ITEM_HISTORY_MENU[];
//historyMenuItems
#define MODE_HISTORY_FILTER "Промывки фильтра"
#define MODE_HISTORY_WATER "Потребления воды"
#define MODE_HISTORY_MAX_WATER "Максимальный расход"
#define MODE_HISTORY_ERRORS "Ошибки"

//widgets
#define NEXT_CYCLE_TIME "ч"
#define CURRENT_WATER_CONSUMPTION_LITERS "л/мин"
#define CURRENT_WATER_CONSUMPTION_M_CUBE "м3/мин"
#define LITERS "л"
#define M_CUBE "м3"


//washingTimeCustomerFrame
//#define MODE_WASHING_TIME "Время промывки"
//#define DAY "День"
//#define NIGHT "Ночь"

//forcedRegenCustomerFrame
#define MODE_FORCED_REGEN "Принудительная рег."
#define FAST_REGEN "Рег."
#define DELAYED_REGEN "Отл.рег."

//delayedRegenCustomerFrame
#define MODE_DELAYED_REGEN "Отложенная рег."
#define DAY_BEFORE_REGEN "Дней до регенерации"

//daysBetweenRegenCustomerFrame
#define MODE_DAYS_BETWEEN_REGEN "ДМР"
#define DAY_BETWEEN_REGEN "Дней между регенерациями"

//filterSelectionFrame
#define MODE_FILTER_SELECTION "Тип фильтра"
extern const uint8_t* ITEM_FILTER_SELECTION[];

//regenPeriodServiceFrame
#define MODE_REGEN_PERIOD "Период регенерации"

//washingTimeServiceFrame
#define MODE_REGEN_TIME "Время промывки"

//washingTimeServiceFrame
#define PERIOD_REGEN "Период промывки"

//quantityCountServiceFrame
#define MODE_QUANTITY_COUNT "Счетчик воды"
#define QUANTITY_COUNT "Объем"

//regenServiceFrame
#define MODE_REGEN "Регенерация"

//alarmNotiFrame
#define MODE_ALARM_NOTI "Уведомление"
#define NOTI_STRING_1 "Для сервисного обслуживания и"
#define NOTI_STRING_2 "ремонта необходимо обратиться в"
#define NOTI_STRING_3 "ООО \"Промэнергоинвест\""
#define NOTI_STRING_4 ""

//alarmListFrame
#define MODE_ALARM_LIST "Список ошибок"

//filteringFrame
#define MODE_FILTERING "Фильтрация"
extern const uint8_t* ITEM_FILTERING[];
#define SAVE "Сохранить"
#define MINUTE "Мин"
#define CREATE "Создать"

//softeningFrame
#define MODE_SOFTENING "Умягчение"
extern const uint8_t* ITEM_SOFTENING[];

//adjustmentFrame
#define MODE_ADJUSTMENT "Регулировка штока"
extern const uint8_t* ITEM_ADJUSTMENT[];
#define RESET_TEXT "Сброс"
#define POSITION "Поз:"
#define START_ENG "Старт"


//stepFrame
#define STEPS_LIST "Стадии"
extern const uint8_t* ITEM_STEPS[];
extern const uint8_t* ITEM_STEPS_WITH_MES[];
//ManualFilteringSettingsFrame
extern const uint8_t* ITEM_MANUAL_SETTINGS[];

extern const uint8_t* ITEM_WATER_BR[];

extern const uint8_t* ITEM_SERVICE_INFO[];

extern const uint8_t* ITEM_LOAD_TYPE[];

extern const uint8_t* ITEM_INPUT_ONE_FRAME[];

extern const uint8_t* ITEM_UNIVERSAL_OUTPUT_FRAME[];

extern const uint8_t* ITEM_EL_MAG_FRAME[];

extern const uint8_t* ITEM_IMPULSE_WEIGHT[];

extern const uint8_t* ITEM_MOTOR_SETTINGS[];
