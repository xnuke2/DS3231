#pragma once
#include <Arduino.h>
#include <Wire.h>

#define DS3231_ADDR 0x68
#define REGISTER_TIME 0x00
#define REGISTER_TEMPERATURE 0x11

class DS3231_Class {
public:
    /**
     * @brief Получает единственный экземпляр класса DS3231_Class
     * @return Ссылка на экземпляр DS3231_Class
     */
    
    DS3231_Class() { Wire.begin(); } // конструктор
    /**
     * @brief Устанавливает дату и время в DS3231_Class
     * @param sec Секунды (0-59)
     * @param min Минуты (0-59)
     * @param hour Часы (0-23)
     * @param weekday День недели (1-7, 1=понедельник)
     * @param day День месяца (1-31)
     * @param month Месяц (1-12)
     * @param year Год (0-99, 00=2000)
     */
    void setDateTime(byte sec, byte min, byte hour,
        byte weekday, byte day, byte month, byte year);

    /**
     * @brief Получает текущую дату и время в виде строки
     * @return Строка с датой и временем в формате "DD.MM.YYYY HH:MM:SS"
     */
    String getDateTime();

    /**
     * @brief Получает температуру с датчика DS3231_Class
     * @return Температура в градусах Цельсия
     */
    float getTemperature();

private:
    
    
    /**
     * @brief Получает сырые данные времени и даты
     * @param dateTime Указатель на массив для хранения данных (7 байт)
     */
    void getDateTimeRaw(byte* dateTime);

    /**
     * @brief Получает сырые данные температуры
     * @param temp Указатель на массив для хранения данных (2 байта)
     */
    void getTemperatureRaw(byte* temp);
};

// Глобальный экземпляр для удобства использования
extern DS3231_Class DS3231;
