#include "items.h"

const uint8_t* ITEM_MENU[] = { "Время/Дата", "Старт промывки", "Период промывки", "Фильтроцикл" };

const uint8_t* ITEM_SERVICE_MENU[] = { "Тип фильтра", "Тип промывки", "Внешний сигнал (ВХ1)", "Универсальный выход (ВЫХ1)", "ЭМК (ВЫХ2)","Сервисное обслуживание", "Контакты","Регулировка положений", "Настройка мотора", "Смена пароля"};// , "Регулировка", "Ручное управление" };

const uint8_t* ITEM_HISTORY_MENU[] = { "Промывки фильтра", "Потребление воды", "Максимальный расход", "Ошибки", "Общая информация"};

const uint8_t* ITEM_GENERAL_INFO_MENU[] = { "Общее время работы", "Общий объем воды", "Количество промывок", "Версия ПО" };

const uint8_t* ITEM_FILTER_SELECTION[] = { "Фильтрация", "Умягчение", "Ручная настройка" };

const uint8_t* ITEM_FILTERING[] = { "Обратная промывка", "Прямая промывка"};

const uint8_t* ITEM_SOFTENING[] = { "Обратная промывка", "Засос солевого раствора", "Прямая промывка", "Заполнение солевого бака"};

//const uint8_t* ITEM_ADJUSTMENT = &ITEM_STEPS[];
const uint8_t* ITEM_ERRORS[] = {"ОТСУТСВУЕТ ОСНОВНОЕ ПИТАНИЕ","ОТСУТСТВИЕ ВРАЩЕНИЯ ШЕСТЕРНИ","ДЛИТЕЛЬНОЕ ВРАЩЕНИЕ МОТОРА","","","","","","","","","","","","","","","История отказов"};

const uint8_t* ITEM_STEPS[] = { "Фильтрация", "Прямая промывка", "Обратная промывка", "Засос солевого раствора", "и медленная отмывка", "Заполнение солевого бака"/*"Расход соли на регенерацию"*/};/*"Заполнение солевого бака и медленная отмывка"};*/ 

const uint8_t* ITEM_STEPS_WITH_MES[] = { "Фильтрация, мин", "Прямая промывка, мин", "Обратная промывка, мин", "Засос солевого раствора", "и медленная отмывка, мин", "Заполнение солевого бака",",кг" /*"Расход соли на", "регенерацию, кг"*/};/*"Заполнение солевого бака и медленная отмывка"};*/ 

const uint8_t* ITEM_IMPULSE_WEIGHT[] = {"1 л/имп","10 л/имп","100 л/имп","Вес импульсного выхода"};

const uint8_t* ITEM_MAIN_FRAME[] = {"ЦИКЛ УМЯГЧЕНИЯ","РЕЖИМ", "ОТЛ. РЕГЕН.", "СКОРОСТЬ","ВРЕМЯ", "ДНЕЙ","Л/МИН","ЧЧ:ММ"};

const uint8_t* ITEM_CLOCKSET_FRAME[] = {"ЧАСЫ","МИНУТЫ"};

const uint8_t* ITEM_PINCODE_FRAME[] = {"Пароль для сервиса","Пожалуйста, ведите пароль","Войти","Введите число" };

const uint8_t* ITEM_CHANGE_PINCODE_FRAME[] = {"Введите старый пароль", "Введите новый пароль", "Сохранить"};

const uint8_t* ITEM_CALENDAR_FRAME[] = {"День","Месяц","Год"};

const uint8_t* ITEM_MANUAL_SETTINGS[] = {"Ручная настройка", "Добавить шаг"};

const uint8_t* ITEM_WATER_BR[] = {"Расход воды", "м"};

const uint8_t* ITEM_SERVICE_INFO[] = {"Сервисное обслуживание", "Дата следующего сервисного", "обслуживания", "Сервис выполнен", "Необходимо провести сервис", "Следующее сервисное обслуживание","сделать через:", "0", "3", "6", "9", "12", "Месяцев"};

const uint8_t* ITEM_LOAD_TYPE[] = {"Тип промывки", "По дням", "По часам", "Универсальная", "Немедленная","Отложенная" ,};

const uint8_t* ITEM_INPUT_ONE_FRAME[] = {"Удаленный запуск промывки", "Запрет промывки", "ВХ1"};

const uint8_t* ITEM_UNIVERSAL_OUTPUT_FRAME[] = {"Не активен", "Промывка фильтра", "Импульсный выход", "Запуск в промывку соседа", "ВЫХ1"};

const uint8_t* ITEM_AC_OUTPUT_FRAME[] = {"ВЫХ2", "Работа с компрессором", "Промывка фильтра"};

const uint8_t* ITEM_EL_MAG_FRAME[] = {"ВЫХ2"};

const uint8_t* ITEM_MOTOR_SETTINGS[] = {"Настройки двигателя", "Максимальная скорость", "Замедленная скорость"};

const uint8_t* ITEM_HISTORY_ERROR[] = {"Журнал загружается","Журнал пуст", "Промывка фильтра в "," л", " л/мин",

" Нет основного питания",
" Нет батареи",
" Нет 5В",
" Нет питания ВЫХ1",
" Перегрев",
" Отказ драйвера 1",
" Отказ драйвера 2",
" Отказ двигателя",
" Заклинивание",
" Отказ поршня",
" Выбег",
" Отказ ВЫХ1",
" Отказ ВЫХ2",
" Отказ дисплея",
" Отказ тачскрина",
" Отказ ОЗУ",
" Отказ ПЗУ",
" Память заполнена",
};

const uint8_t* ITEM_TIME_ruText[] = { 
	"Дата/Время",
	"Установка даты и времени",
	"Год",
	"Месяц",
	"День",
	"Час",
	"Минуты",
	"Сохранить",
	"Сброс",
	"Установка даты и времени",
	"Введите год",
	"Введите месяц",
	"Введите день",
	"Введите час",
	"Введите минуты"
};

const uint8_t* ITEM_LOG_TEXT[] = {
	"Запуск промывки по внешнему сигналу. Время - ",
	"Запуск промывки вручную. Время - ",
	"Режим - ПО ДНЯМ/ЧАСАМ. Запуск промывки по времени. Время - ",
	"Режим - УНИВЕРСАЛЬНЫЙ. Запуск промывки по отсутствию потребления воды. Время - ",
	"Воды отфильтровано с прошлой промывки - ",
	"Лимит отфильтрованной воды - "
	"Режим - УНИВЕРСАЛЬНЫЙ. Запуск промывки в предпочтительное время. Время - ",
	"Режим - УНИВЕРСАЛЬНЫЙ. Запуск промывки по истечению времени. Время - ",
};

const uint8_t* ITEM_SETTINGS_FLUSH[] = {"Сброс настроек", "Сбросить настройки на заводские?","СБРОС", "ОТМЕНА", "Производится сброс настроек"};

const uint8_t* ITEM_PROD_TEST_MAINSCREEN[] = {
	"FAIL", //0
	"PASS", //1
	"NOT STARTED", //2
	"Battery voltage: ", " V",  //3 4
	"Main voltage 3.3V: ", " V", //5 6
	"Secondary voltage 5V: ", " V", //7 8
	"Voltage on \"ВХ1\": ", " V", //9 10
	"IC temperature: ", " ", //11 12
	"Input voltage: ", " V", //13 14
	"Motor Test:", //15
	"TFT Test:", //16
	"Touch Test:", //17 
	"Memory Test:", //18
	"IO Test:", //19
	"Display color test", //20
	"Test contain 5 colors: White, Black, Red, Blue, Green", //21
	"Tap screen to change color", //22
	"Press \"Start\"", //23
	"All colors was OK?", //24
	"Touchscreen test", //25
	"Test consist of series of buttons.", //26
	"Press and release button to proceed to next one.", //27
	"Each button have 10sec delay before auto fail.", //28
	"Motor and optic test", //29
	"Check motor connection and put your PCB on first chasis.", //30
	"After you press \"Start\" motor wil run several tests", //31
	"with autocheck.", //32
	"Test for input/output ports", //33
	"Connect \"ВЫХ1\" to DC power supply (0..24V) and load (1A),", //34
	"\"ВЫХ2\" to AC power supply (110-220V,50Hz) and load (0.5A)", //35
	"Connect \"ВХ1\" то descrete command generator (0..5V DC),",//36
  "\"РАСХОДОМЕР\" to PWM source (0..5V, 0..25Hz)", //37
	"Compare measured and test values", //38
	"ON", //39
	"OFF", //40
	"Output \"ВЫХ1\": ", //41
	"Output \"ВЫХ1\" measured: ", //42
	"Output \"ВЫХ2\": ", //43
	"Output \"ВЫХ2\" measured: ", //44
	"Input \"ВХ1\" measured: ", //45
	"\"РАСХОДОМЕР\" input frequancy: ", //46
	"Test passed. Press \"PASS\"", //47
	"Test failed. ", //48
	"Destination position should be: ", //49
	"Current position: ", //50 
	"Press \"FAIL\"", //51
	"Memory Test", //52
	"Test contains automatic memoty IC tests", //53
	"Wait until it finishes", //54
	"Test failed", //55
	"Couldn't write to FRAM adress: ", //56
	"Couldn't read from FRAM adress: ", //57
	"Content in FRAM adress differs from test value.", //58
	"Expected value: ", //59
	"Received value: ", //60
	"Couldn't write to RAM adress: ", //61
	"Couldn't read from RAM adress: ", //62
	"Test completed successfully", //63
	"FRAM read test", //64
	"FRAM write test", //65
	"RAM read test", //66
	"RAM write test", //67
	"FRAM and RAM simultaneous work",//68
};