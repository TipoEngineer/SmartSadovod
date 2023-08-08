# 1 "C:\\Users\\Robokvantum 01\\YandexDisk\\Universal folder\\Projects\\Git\\SmartSadovod\\Program_Smart_Sadovod\\Program_Smart_Sadovod.ino"
# 2 "C:\\Users\\Robokvantum 01\\YandexDisk\\Universal folder\\Projects\\Git\\SmartSadovod\\Program_Smart_Sadovod\\Program_Smart_Sadovod.ino" 2




//#define WIFI_SSID "9"
//#define WIFI_PASS "12312312"                                                                                                                                                                                                                                                                                                                     
//#define BOT_TOKEN "6572535284:AAG4YXp1W6LxuXLuNpXM_9kIUmtMAUZV3xw"


//#define WIFI_SSID "Pixel"                                                                                                                                                   
//#define WIFI_PASS "123456789"
//#define BOT_TOKEN "6572535284:AAG4YXp1W6LxuXLuNpXM_9kIUmtMAUZV3xw"






# 21 "C:\\Users\\Robokvantum 01\\YandexDisk\\Universal folder\\Projects\\Git\\SmartSadovod\\Program_Smart_Sadovod\\Program_Smart_Sadovod.ino" 2
FastBot bot("6572535284:AAG4YXp1W6LxuXLuNpXM_9kIUmtMAUZV3xw");

# 24 "C:\\Users\\Robokvantum 01\\YandexDisk\\Universal folder\\Projects\\Git\\SmartSadovod\\Program_Smart_Sadovod\\Program_Smart_Sadovod.ino" 2
DHT dht(33, DHT11); // сообщаем на каком порту будет датчик
# 37 "C:\\Users\\Robokvantum 01\\YandexDisk\\Universal folder\\Projects\\Git\\SmartSadovod\\Program_Smart_Sadovod\\Program_Smart_Sadovod.ino"
bool res = 0;
uint32_t startUnix;

bool min_poplovok = false;
bool max_poplovok = false;

bool pump_sta = false;
bool privod_sta = false;
bool privod_sta_closed = false;

bool eeprom_save = false;

float temp;

bool flag = false;

int shag = 0;
bool step_start = false;

int temp_work;
int poliv_work;

String timer_start_poliv = "69:69:69";
String poliv_work_String = "69:69:69";
String temp_String = "69:69:69";


static uint32_t tmr2;
static uint32_t tmr3;
# 68 "C:\\Users\\Robokvantum 01\\YandexDisk\\Universal folder\\Projects\\Git\\SmartSadovod\\Program_Smart_Sadovod\\Program_Smart_Sadovod.ino"
void setup();
# 103 "C:\\Users\\Robokvantum 01\\YandexDisk\\Universal folder\\Projects\\Git\\SmartSadovod\\Program_Smart_Sadovod\\Program_Smart_Sadovod.ino"
void newMsg(FB_msg& msg);
# 268 "C:\\Users\\Robokvantum 01\\YandexDisk\\Universal folder\\Projects\\Git\\SmartSadovod\\Program_Smart_Sadovod\\Program_Smart_Sadovod.ino"
void loop();
# 360 "C:\\Users\\Robokvantum 01\\YandexDisk\\Universal folder\\Projects\\Git\\SmartSadovod\\Program_Smart_Sadovod\\Program_Smart_Sadovod.ino"
void connectWiFi();
# 373 "C:\\Users\\Robokvantum 01\\YandexDisk\\Universal folder\\Projects\\Git\\SmartSadovod\\Program_Smart_Sadovod\\Program_Smart_Sadovod.ino"
void trubleshuting();
# 406 "C:\\Users\\Robokvantum 01\\YandexDisk\\Universal folder\\Projects\\Git\\SmartSadovod\\Program_Smart_Sadovod\\Program_Smart_Sadovod.ino"
void temperatuta();
# 68 "C:\\Users\\Robokvantum 01\\YandexDisk\\Universal folder\\Projects\\Git\\SmartSadovod\\Program_Smart_Sadovod\\Program_Smart_Sadovod.ino"
void setup() {
  connectWiFi();
  bot.setChatID("468494936"); //написать свой id
  bot.setPeriod(2000);
  bot.attach(newMsg);
  pinMode(18, 0x01);
  pinMode(32, 0x01);
  pinMode(25, 0x03);
  pinMode(26, 0x03);
  pinMode(19, 0x03);
  bot.sendMessage("Тестируем Меню");
  startUnix = bot.getUnix();
  bot.showMenu("Ручной режим \t Автоматический режим \n Статус \t Перезагрузка");
  dht.begin();

  EEPROM.begin(100);


  if (EEPROM.read(0) != 'W') {
    EEPROM.writeString(10, timer_start_poliv);
    EEPROM.writeInt(20, poliv_work);
    EEPROM.writeInt(30, temp_work);
    EEPROM.write(0, 'W');
  }
  else {
    timer_start_poliv = EEPROM.readString(10);
    poliv_work = EEPROM.readInt(20);
    temp_work = EEPROM.readInt(30);
  }

  EEPROM.commit();

}

// обработчик сообщений
void newMsg(FB_msg& msg) {
  // выводим ID чата, имя юзера и текст сообщения


  // Ручной режим
  if (msg.text == "Ручной режим") {
    bot.showMenu("Включить помпу \t  Открыть привод \n Выключить помпу \t Закрыть привод \n Назад");
  }

  if (msg.text == "Назад" ) {
    bot.showMenu("Ручной режим \t Автоматический режим \n Статус \t Перезагрузка");
  }

  if (msg.text == "Включить помпу" && pump_sta == 0) {
    digitalWrite(25, 0x1);
    pump_sta = true;

    bot.sendMessage("Помпа включена");
  }

  if (msg.text == "Выключить помпу" && pump_sta == 1) {
    digitalWrite(25, 0x0);
    pump_sta = false;

    bot.sendMessage("Помпа Выключена");
  }




  if (msg.text == "Открыть привод" && privod_sta == false) {
    digitalWrite(26, 0x1);
    tmr2 = millis();
    privod_sta = true;

  }


  if (msg.text == "Закрыть привод" && privod_sta_closed == false) {
    digitalWrite(19, 0x1);
    tmr3 = millis();
    privod_sta_closed = true;

  }

  // Автоматический режим
  if (msg.text == "Автоматический режим") {
    bot.showMenu("Статус авто \t Перенастроить \n Назад");
  }

  if (msg.text == "Назад" ) {
    bot.showMenu("Ручной режим \t Автоматический режим \n Статус \t Перезагрузка");
  }


  String pump_msg = "MAX " + String(!max_poplovok);
  String lenta_msg = "MIN " + String(!min_poplovok);
  String temper = "T " + String(temp);




  if (msg.text == "Статус") {
    bot.sendMessage(pump_msg);
    bot.sendMessage(lenta_msg);
    bot.sendMessage(temper);
    // bot.sendMessage("Помпа: " + );
  }

  if (msg.text == "Перезагрузка") res = 1;
  if (msg.OTA && msg.chatID == "468494936") bot.update();
  if (msg.unix < startUnix) return;
# 190 "C:\\Users\\Robokvantum 01\\YandexDisk\\Universal folder\\Projects\\Git\\SmartSadovod\\Program_Smart_Sadovod\\Program_Smart_Sadovod.ino"
  // Автоматический режим


  if (msg.text == "Перенастроить") {
    msg.text = " "; // Сброс
    shag = 1;
  }

  if (shag == 1) {
    bot.sendMessage("Введите время полива");
    shag = 2;
  }

  if (shag == 2) {
    timer_start_poliv = msg.text;
    if (msg.text != " ") {
      shag = 3;
    }
  }

  if (shag == 3) {
    bot.sendMessage("Введите время работы помпы");
    msg.text = " "; // Сброс
    shag = 4;
  }

if (shag == 4){
  poliv_work_String = msg.text;
    if (msg.text != " ") {
      shag = 5;
    }
  }


if (shag == 5){
  bot.sendMessage("Введите температуру");
  poliv_work = poliv_work_String.toInt();
  msg.text = " "; // Сброс
  shag = 6;
  }

if (shag == 6){
  temp_String = msg.text;
    if (msg.text != " ") {
      shag = 7;
    }
  }

if (shag == 7){
  temp_work = temp_String.toInt();
  msg.text = " "; // Сброс
  shag = 8;
  eeprom_save = true;
  }




  if (eeprom_save == true) {
    EEPROM.writeString(10, timer_start_poliv);
    EEPROM.writeInt(20, poliv_work);
    EEPROM.writeInt(30, temp_work);
    EEPROM.commit();
    eeprom_save = false;
  }


  if (msg.text == "Статус авто") {
    String poliv_string_send = String (poliv_work);
    String temp_string_send = String(temp_work);
    bot.sendMessage(timer_start_poliv);
    bot.sendMessage(poliv_string_send);
    bot.sendMessage(temp_string_send);
  }
}



void loop() {
  bot.tick();

  if (res == 1) {
    bot.tickManual();
    ESP.restart();
  }

  trubleshuting();


  // Попловок MAX
  //читаем инвертированное значение для удобства
  bool btnState_max = !digitalRead(18);
  if (btnState_max && !max_poplovok) { // обработчик нажатия
    max_poplovok = true;
    Serial.println("Максимальный");
  }
  if (!btnState_max && max_poplovok) { // обработчик отпускания
    max_poplovok = false;
    //Serial.println("release");
  }



  // Попловок MIN
  bool btnState_min = !digitalRead(32);
  if (btnState_min && !min_poplovok) { // обработчик нажатия
    min_poplovok = true;
    Serial.println("Минимальный");
  }
  if (!btnState_min && min_poplovok) { // обработчик отпускания
    min_poplovok = false;
    //Serial.println("release");
  }

  temperatuta();



  static uint32_t tmr;
  static uint32_t tmr1;



  if (millis() - tmr >= 1000) {
    tmr = millis();
    // выведем время и дату
    FB_Time t = bot.getTime(3);





    if (t.timeString() == timer_start_poliv && min_poplovok) {
      Serial.print("Время");
      pump_sta = true;
      digitalWrite(25, 0x1);
      tmr1 = millis();
    }



  }

  if (pump_sta == true && millis() - tmr1 >= poliv_work * 1000) {
    tmr1 = millis();
    Serial.println("Полив");
    digitalWrite(25, 0x0);
    pump_sta = false;
  }



  if (temp >= temp_work) {
    digitalWrite(26, 0x1);
    tmr2 = millis();
    privod_sta = true;
  }


  if (temp <= temp_work) {
    digitalWrite(19, 0x1);
    tmr3 = millis();
    privod_sta_closed = true;
  }



}


void connectWiFi() {
  delay(2000);
  Serial.begin(115200);
  Serial.println();
  WiFi.begin("R&P Home", "PoRnOfILmS");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() > 15000) ESP.restart();
  }
  Serial.println("Connected");
}

void trubleshuting() {
  static uint32_t tmr1;
  if (millis() - tmr1 >= 1000) {
    tmr1 = millis();
    Serial.println("#######################");
    Serial.println(" ");
    Serial.println(max_poplovok);
    Serial.println(min_poplovok);
    Serial.println(temp);
    Serial.println(privod_sta);
    Serial.println(shag);
    Serial.println(timer_start_poliv);
    Serial.println(poliv_work_String);
    Serial.println(poliv_work);
    Serial.println(temp_work);
    Serial.println(temp_String);

    if (privod_sta == true && millis() - tmr2 >= 3000) {
      tmr2 = millis();
      digitalWrite(26, 0x0);
      privod_sta = false;
    }

    if (privod_sta_closed == true && millis() - tmr3 >= 3000) {
      tmr3 = millis();
      digitalWrite(19, 0x0);
      privod_sta_closed = false;
    }


  }
}

void temperatuta() {
  temp = dht.readTemperature();
}
