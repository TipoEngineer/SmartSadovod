#include <EEPROM.h>

//Будем подключать энергонезависимую память!!!
//задача 1. Нужно записать 4 переменные в память чтобы она при перезагрузке сохранялись
//  Time_test
//  time_work
//  time_start_light
//  time_stop_light
//
//задача 2. Уменьшить количество перезаписей, чтобы не убить EEPROM

// Каждая пермеменная будет равна 1 байту




#define WIFI_SSID "9"
#define WIFI_PASS "12312312"
#define BOT_TOKEN "6572535284:AAG4YXp1W6LxuXLuNpXM_9kIUmtMAUZV3xw"
#include <FastBot.h>
FastBot bot(BOT_TOKEN);


#define pump 26
#define lenta 25

bool res = 0;
bool pump_sta = 0;
bool lenta_sta = 0;
bool flag_time_work = false;
bool flag_msg = 0;
bool flag_polivvvv = false;
int time_work_int;
String Time_test = "69:69:69";
String time_work = "69:69:69";
String time_start_light = "69:69:69";
String time_stop_light = "69:69:69";
String otvet;
uint32_t startUnix;
bool flag_flag = true;

bool step0 = false;
bool step1 = false;
bool step2 = false;
bool step3 = false;
bool step4 = false;
bool step5 = false;
bool step6 = false;
bool step7 = false;
bool step8 = false;
bool step9 = false;
bool step10 = false;
bool flag_flag_flag = true;
bool flag_flag_flag_flag = true;
bool flag_flag_flag_flag_flag = true;
bool flagggg = true;
bool eeprom_save = false;

constexpr auto pinSensor = 35; // PIN датчика влажности почвы



void setup() {

  dht.begin();                // запускаем датчик DHT11
  bot.setChatID("468494936"); //написать свой id
  connectWiFi();
  bot.setPeriod(2000);
  bot.attach(newMsg);
  //bot.showMenu("status \t pump on \n pump off");
  bot.showMenu("Лук \n Статус \t Ручной режим \t Перезагрузка");
  bot.setTextMode(FB_MARKDOWN);
  bot.sendMessage("Тестируем Меню");
  startUnix = bot.getUnix();
  pinMode(pump, OUTPUT);
  pinMode(lenta, OUTPUT);
  //Serial.begin(9600);



  // Читаем значение из EEPROM

  EEPROM.begin(100);


  if (EEPROM.read(0) != 'W') {
    EEPROM.writeString(1, Time_test);
    EEPROM.writeString(2, time_work);
    EEPROM.writeString(3, time_start_light);
    EEPROM.writeString(4, time_stop_light);
    EEPROM.write(0, 'W');
  }
  else {
    Time_test = EEPROM.readString(1);
    time_work = EEPROM.readString(2);
    time_start_light = EEPROM.readString(3);
    time_stop_light = EEPROM.readString(4);
  }

  EEPROM.commit();



}

void newMsg(FB_msg& msg) {
  // Датчик влажности почвы
  int valueSensor = analogRead(pinSensor);
  int procent = map(valueSensor, 0, 4095, 0, 100);
  String P_Pochva = "Влажность почвы: " + String(procent);


  // Датчик температуры и влажности воздуха
  float h = dht.readHumidity();
  float temp = dht.readTemperature();
  String T_Vozduh = "Температура воздуха: " + String(temp);
  String H_Vozduh = "Влажность воздуха: " + String(h);


  // Статус
  String pump_msg = "Состояние помпы: " + String(pump_sta);
  String lenta_msg = "Состояние ленты: " + String(lenta_sta);
  if (msg.text == "Статус") {
    bot.sendMessage(P_Pochva);
    bot.sendMessage(T_Vozduh);
    bot.sendMessage(H_Vozduh);
    bot.sendMessage(pump_msg);
    bot.sendMessage(lenta_msg);
  }

  // Ручной режим работы

  if (msg.text == "Ручной режим") {
    bot.showMenu("Включить помпу \t  Включить УФ ленту \n Выключить помпу \t Выключить УФ ленту \n Назад");
  }

  if (msg.text == "Назад" ) {
    bot.showMenu("Лук \n Статус \t Ручной режим \t Перезагрузка");
  }





  if (msg.text == "Включить помпу" && pump_sta == 0) {
    digitalWrite(pump, HIGH);
    pump_sta = true;

    bot.sendMessage("Помпа включена");
  }

  if (msg.text == "Выключить помпу" && pump_sta == 1) {
    digitalWrite(pump, LOW);
    pump_sta = false;

    bot.sendMessage("Помпа Выключена");
  }

  if (msg.text == "Включить УФ ленту" && lenta_sta == 0) {
    digitalWrite(lenta, HIGH);
    lenta_sta = true;

    bot.sendMessage("Лента включена");
  }

  if (msg.text == "Выключить УФ ленту" && lenta_sta == 1) {
    digitalWrite(lenta, LOW);
    lenta_sta = false;

    bot.sendMessage("Лента Выключена");
  }










  // Автоматический режим работы
  if (msg.text == "Лук") {
    bot.showMenu("План \t Перенастроить \n Назад");
  }



  FB_Time t(msg.unix, 3);


  if (msg.text == "Перенастроить" ) {
    step1 = true;
    step0 = true;
Time_test = "69:69:69";
time_work = "69:69:69";
time_start_light = "69:69:69";
time_stop_light = "69:69:69";
  }

//  if (step0 == true) {
//
//    if (step1 == true) {
//      bot.sendMessage("Введите Время начала полива");
//      step1 = false;
//      step2 = true;
//    }
//
//    if (step2 == true && msg.text != "Перенастроить") {
//      Time_test = msg.text;
//    }
//
//    if (Time_test != "69:69:69" && msg.text != "Перенастроить" && flag_flag_flag == true) {
//      step2 = false;
//      step3 = true;
//    }
//
//    if (step3 == true) {
//      bot.sendMessage("Введите время полива в секундах");
//      step3 = false;
//      step4 = true;
//    }
//
//    if (step4 == true) {
//      time_work = msg.text;
//      flag_flag_flag = false;
//    }
//
//    if (Time_test != time_work && flagggg == true) {
//      step4 = false;
//      step5 = true;
//    }
//
//    if (step5 == true && flag_flag_flag_flag == true) {
//
//      step5 = false;
//      step6 = true;
//      flagggg = false;
//    }
//
//
//
//
//    if (step6 == true) {
//      bot.sendMessage("Введите время начала засвета");
//      step6 = false;
//      step7 = true;
//      flag_flag_flag_flag = false;
//    }
//
//
//    if (step7 == true) {
//      time_start_light = msg.text;
//    }
//
//    if (time_work != time_start_light && time_start_light != "69:69:69" && flag_flag_flag_flag_flag == true) {
//      step7 = false;
//      step8 = true;
//    }
//
//    if (step8 == true) {
//      bot.sendMessage("Введите время окончания засвета");
//      step8 = false;
//      step9 = true;
//      flag_flag_flag_flag_flag = false;
//    }
//
//    if (step9 == true) {
//      time_stop_light = msg.text;
//      step10 = true;
//    }
//
//    if (step10 == true && time_stop_light != "69:69:69" && time_stop_light != time_start_light) {
//      step9 = false;
//      bot.sendMessage("Готово");
//      step10 = false;
//      eeprom_save = true;
//    }
//
//    if (msg.text == "Готово") {
//      step0 = false;
//    }
//
//  }

  time_work_int = time_work.toInt();

  if (eeprom_save == true) {
    EEPROM.writeString(1, Time_test);
    EEPROM.writeString(2, time_work);
    EEPROM.writeString(3, time_start_light);
    EEPROM.writeString(4, time_stop_light);
    EEPROM.commit();
    eeprom_save = false;
  }

  if (msg.text == "План") {
    bot.sendMessage("Время начала полива " + Time_test);
    bot.sendMessage("Время полива " + time_work);
    bot.sendMessage("Время начала засвета " + time_start_light);
    bot.sendMessage("Время окончания засвета " + time_stop_light);
  }


  // Перезагрузка контроллера

  if (msg.text == "Перезагрузка") res = 1;
  if (msg.OTA && msg.chatID == "468494936") bot.update();
  if (msg.unix < startUnix) return;
}

void loop() {
  bot.tick();
  if (res == 1) {
    bot.tickManual();
    ESP.restart();
  }
  //trubleshuting();
  steps();

  // Время включения/выключения помпы
  static uint32_t tmr;
  static uint32_t tmr2;

  if (millis() - tmr >= 1000) {
    tmr = millis();
    // выведем время и дату
    FB_Time t = bot.getTime(3);





    if (t.timeString() == Time_test) {
      Serial.print("Время");
      flag_polivvvv = true;
      digitalWrite(pump, HIGH);
      tmr2 = millis();
    }



    if (t.timeString() == time_start_light) {
      digitalWrite(lenta, HIGH);
      lenta_sta = true;
      Serial.println("Засвет начат");
    }
    if (t.timeString() == time_stop_light) {
      digitalWrite(lenta, LOW);
      lenta_sta = false;
      Serial.println("Засвет окончен");
    }



  }

  if (flag_polivvvv == true && millis() - tmr2 >= time_work_int * 1000) {
    tmr2 = millis();
    Serial.println("Полив");
    digitalWrite(pump, LOW);
    flag_polivvvv = false;
  }






  // Условие сохранения в EEprom




  //  Time_test
  //  time_work
  //  time_start_light
  //  time_stop_light



}

void connectWiFi() {
  delay(2000);
  Serial.begin(115200);
  Serial.println();
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() > 15000) ESP.restart();
  }
  Serial.println("Connected");
}

void trubleshuting() {
  static uint32_t tmr3;
  if (millis() - tmr3 >= 1000) {
    tmr3 = millis();
    Serial.println(" ");
    Serial.println("Время начала полива: " + Time_test);
    Serial.println("Время полива: " + time_work);
    Serial.println("Время начала засвета: " + time_start_light);
    Serial.println("Время окончания засвета: " + time_stop_light); //flag_time_work
    Serial.println(flag_time_work);
    Serial.println(time_work_int);
  }
}


void steps() {
  static uint32_t tmr3;
  if (millis() - tmr3 >= 1000) {
    tmr3 = millis();
    Serial.println(" ");
    Serial.println(step1);
    Serial.println(step2);
    Serial.println(step3);
    Serial.println(step4);
    Serial.println(step5);
    Serial.println(step6);
    Serial.println(step7);
    Serial.println(step8);
    Serial.println(step9);
    Serial.println(step10);
    Serial.println(eeprom_save);
    Serial.println("Время начала полива: " + Time_test);
    Serial.println("Время полива: " + time_work);
    Serial.println("Время начала засвета: " + time_start_light);
    Serial.println("Время окончания засвета: " + time_stop_light);
  }
}