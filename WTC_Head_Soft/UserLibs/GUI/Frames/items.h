#include "main.h"

//Main Frame
extern uint8_t* ITEM_MAIN_FRAME[];

//Clock Set Frame
extern uint8_t* ITEM_CLOCKSET_FRAME[];
extern uint8_t* ITEM_CALENDAR_FRAME[];
//TimeSet Frame
extern uint8_t* ITEM_TIME_ruText[];
//menuFrame
#define MODE_CUSTOMER "Пользователь"
extern uint8_t* ITEM_MENU[];
//Pincode Frame
extern uint8_t* ITEM_PINCODE_FRAME[];
//serviceMenuFrame
#define MODE_SERVICE "Инженер"
extern uint8_t* ITEM_SERVICE_MENU[];

//historyMenuFrame
#define MODE_HISTORY "История"
extern uint8_t* ITEM_HISTORY_MENU[];
//historyMenuItems
#define MODE_HISTORY_FILTER "Промывки фильтра"
#define MODE_HISTORY_WATER "Потребления воды"
#define MODE_HISTORY_MAX_WATER "Максимальный расход"
#define MODE_HISTORY_ERRORS "Ошибки"

//widgets
#define NEXT_CYCLE_TIME "ч"
#define CURRENT_WATER_CONSUMPTION "л/мин"
#define AMOUNT_OF_WATER "л"


//washingTimeCustomerFrame
#define MODE_WASHING_TIME "Время промывки"
#define DAY "День"
#define NIGHT "Ночь"

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
extern uint8_t* ITEM_FILTER_SELECTION[];

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
extern uint8_t* ITEM_FILTERING[];
#define SAVE "Сохранить"
#define MINUTE "Мин"
#define CREATE "Создать"

//softeningFrame
#define MODE_SOFTENING "Умягчение"
extern uint8_t* ITEM_SOFTENING[];

//adjustmentFrame
#define MODE_ADJUSTMENT "Регулировка"
extern uint8_t* ITEM_ADJUSTMENT[];
#define RESET_TEXT "Сброс"
#define POSITION "Поз:"
#define START_ENG "Старт"


//stepFrame
#define STEPS_LIST "Стадии"
extern uint8_t* ITEM_STEPS[];

//ManualFilteringSettingsFrame
extern uint8_t* ITEM_MANUAL_SETTINGS[];

extern uint8_t* ITEM_WATER_BR[];

extern uint8_t* ITEM_SERVICE_INFO[];

extern uint8_t* ITEM_LOAD_TYPE[];

extern uint8_t* ITEM_INPUT_ONE_FRAME[];

extern uint8_t* ITEM_UNIVERSAL_OUTPUT_FRAME[];

extern uint8_t* ITEM_EL_MAG_FRAME[];

