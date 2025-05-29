#include "DS3231.h"

// Реализация глобального экземпляра
DS3231_Class DS3231 = DS3231_Class();

void DS3231_Class::setDateTime(byte sec, byte min, byte hour,
    byte weekday, byte day, byte month, byte year) {
    // Преобразование в BCD формат (как требует DS3231_Class)
    byte data[7] = {
        (byte)(((sec / 10) << 4) | (sec % 10)),    // Секунды (BCD)
        (byte)(((min / 10) << 4) | (min % 10)),    // Минуты (BCD)
        (byte)(((hour / 10) << 4) | (hour % 10)),  // Часы (BCD, 24h format)
        weekday,                                  // День недели (1-7)
        (byte)(((day / 10) << 4) | (day % 10)),    // Число месяца (BCD)
        (byte)(((month / 10) << 4) | (month % 10)),// Месяц (BCD)
        (byte)(((year / 10) << 4) | (year % 10))  // Год (BCD)
            };

    Wire.beginTransmission(DS3231_ADDR);
    Wire.write(0x00); // Начинаем с регистра секунд (0x00)
    Wire.write(data, 7); // Записываем 7 байтов данных
    Wire.endTransmission();
}

void DS3231_Class::getDateTimeRaw(byte* dateTime) {
    Wire.beginTransmission(DS3231_ADDR);
    Wire.write(REGISTER_TIME);
    Wire.endTransmission();

    Wire.requestFrom(DS3231_ADDR, 7);
    for (uint8_t i = 0; i < 7; i++) {
        dateTime[i] = Wire.read();
    }
}

String DS3231_Class::getDateTime() {
    byte dateTime[7];
    getDateTimeRaw(dateTime);
    String result = "";
    if (dateTime[4] < 10) result += "0";
    result += String(dateTime[4], HEX); 
    result += ".";
    if (dateTime[5] < 10) result += "0";
    result += String(dateTime[5], HEX);
    result += ".20";
    result += String(dateTime[6], HEX); 
    result += " ";
    if (dateTime[2] < 10) result += "0";
    result += String(dateTime[2], HEX); 
    result += ":";
    if (dateTime[1] < 10) result += "0";
    result += String(dateTime[1], HEX);
    result += ":";
    if (dateTime[0] < 10) result += "0";
    result += String(dateTime[0], HEX);

    return result;
}

float DS3231_Class::getTemperature() {
    byte temp[2];
    getTemperatureRaw(temp);
    return temp[0] + (temp[1] >> 6) * 0.25f; // Преобразование в градусы Цельсия
}

void DS3231_Class::getTemperatureRaw(byte* temp) {
    Wire.beginTransmission(DS3231_ADDR);
    Wire.write(REGISTER_TEMPERATURE);
    Wire.endTransmission();

    Wire.requestFrom(DS3231_ADDR, 2);
    temp[0] = Wire.read();  // Целая часть температуры
    temp[1] = Wire.read();  // Дробная часть температуры
}