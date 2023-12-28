  #define BLYNK_TEMPLATE_ID "TMPL6zuls8oo2"
  #define BLYNK_TEMPLATE_NAME "NodemcuBlynk"
  #define BLYNK_AUTH_TOKEN "VKzqTTp1fTgDMw1zcAchM-TDrQKgQv9k"

  #include <Servo.h>
  #include <ESP8266WiFi.h>
  #include <BlynkSimpleEsp8266.h>

  Servo servoMotor;  // Servo nesnesi oluşturuluyor

  char auth[] = "VKzqTTp1fTgDMw1zcAchM-TDrQKgQv9k";  // Blynk uygulaması tarafından, mailinize gelen token key
  char ssid[] = "selim";                             // Bağlantı yapacağınız Wi‐Fi adı
  char pass[] = "58ss58ss58";                        // Wi‐Fi şifreniz

  int servoPin = D1;  // Servo sinyal pini, D1'e bağlı
  int gasSensor = A0; // Gaz sensörü pinini A0'e bağlı

  BLYNK_WRITE(V0) {
    digitalWrite(D0, param.asInt());
   
   if (param.asInt() == HIGH) {
    Serial.println("Işık Açık");
  } else {
    Serial.println("Işık Kapalı");
  }

  }

  BLYNK_WRITE(V1) {
    int servoPosition = param.asInt(); // Blynk uygulamasından gelen değer okunuyor (0-180 arası)
    int mappedPosition = map(servoPosition, 0, 255, 0, 180); // Blynk slider değeri servo derecesine dönüştürülüyor
    servoMotor.write(mappedPosition); // Servo motoru istenilen pozisyona döndürülüyor

   
  if (mappedPosition > 90) {
    Serial.println("Kapı Açılıyor");
  } else {
    Serial.println("Kapı Kapanıyor");
  }


  }



  void setup() {
    Serial.begin(115200);
    Serial.println("Seri Port");
    pinMode(D0, OUTPUT);
    
    servoMotor.attach(servoPin);  // Servo pini ayarlanıyor
    servoMotor.write(0); // Servo başlangıç pozisyonu (0 derece)

    Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  }

  void loop() {
    Blynk.run();

    int gasValue = analogRead(gasSensor); // Gaz sensöründen veri okunuyor
    Serial.print("Gaz Değeri: ");
    Serial.println(gasValue);

    Blynk.virtualWrite(V2, gasValue); // Gaz değeri Blynk'e gönderiliyor

    

    delay(1000); // 1 saniyede bir okuma yapmak için

   

   
  }
