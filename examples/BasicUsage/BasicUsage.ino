#include <DS3231.h>

void setup() {
  Serial.begin(9600);
  // Установка времени (опционально)
  //DS3231.setDateTime(50, 18, 3, 4, 29, 5, 25); // 01.01.2023 12:00:00
  // Получение и вывод даты/времени
  String datetime = DS3231.getDateTime();
  Serial.print("Дата и время: ");
  Serial.println(datetime);

  // Получение и вывод температуры
  float temp = DS3231.getTemperature();
  Serial.print("Температура: ");
  Serial.print(temp);
  Serial.println(" °C");
}

void loop() {
  // Пример периодического обновления (раз в секунду)
    String currentTime = DS3231.getDateTime();
    Serial.println(currentTime);
    delay(1000);
  
}