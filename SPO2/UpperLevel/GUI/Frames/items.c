#include "items.h"

uint8_t* ITEM_MENU[] = { "Время/Дата", "Время промывки", "Принудительная рег.", "Отложенная рег.", "Дней между рег."};

uint8_t* ITEM_SERVICE_MENU[] = { "Режим промывки", "Вид загрузки", "Время промывки", "Период регенерации", "Расход воды", "Сервисное обслуживание", "Уведомление" };

uint8_t* ITEM_FILTER_SELECTION[] = { "Фильтрация", "Умягчение", "Ручная настройка" };

uint8_t* ITEM_FILTERING[] = { "Обр.пром.", "Прям.пром."};

uint8_t* ITEM_SOFTENING[] = { "Обр.пром.", "Реаг.пром.", "Обр.пром.", "Прямая.пром.", "Заливка" };

//uint8_t* ITEM_ADJUSTMENT = &ITEM_STEPS[];

uint8_t* ITEM_STEPS[] = { "ЗАКРЫТ","ОБРАТНАЯ ПРОМ.", "РЕГЕНЕРАЦИЯ", "ЗАПОЛНЕНИЕ", "УМЯГЧЕНИЕ", "ПРОМЫВКА", "ФИЛЬТРАЦИЯ" };

uint8_t* ITEM_MAIN_FRAME[] = {"ЦИКЛ УМЯГЧЕНИЯ","РЕЖИМ", "ОТЛ. РЕГЕН.", "СКОРОСТЬ","ВРЕМЯ", "ДНЕЙ","Л/МИН","ЧЧ:ММ"};

uint8_t* ITEM_CLOCKSET_FRAME[] = {"ЧАСЫ","МИНУТЫ"};

uint8_t* ITEM_PINCODE_FRAME[] = {"Пароль для сервиса","Введите пароль","Войти","Введите число" };

uint8_t* ITEM_CALENDAR_FRAME[] = {"День","Месяц","Год"};

uint8_t* ITEM_MANUAL_SETTINGS[] = {"Ручная настройка", "Добавить шаг"};

uint8_t* ITEM_WATER_BR[] = {"Расход воды", "м"};
uint8_t* ITEM_SERVICE_INFO[] = {"Сервисное обслуживание", "Дата следующего обслуживания", "Сервис выполнен", "Необходимо провести сервис", "Следующее сервисное обслуживание","провести через:", "3", "6", "9", "12", "Месяцев"};

uint8_t* ITEM_LOAD_TYPE[] = {"Обезжелезивание", "Умягчение", "Сорбция", "Осветление", "Тип загрузки"};


uint8_t* ITEM_TIME_ruText[] = {
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