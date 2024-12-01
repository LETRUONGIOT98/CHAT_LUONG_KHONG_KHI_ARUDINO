 #include "MQ135.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PIN_MQ135 A3    // Khai báo chân kết nối với chân AO của MQ135
MQ135 mq135_sensor = MQ135(PIN_MQ135);   // Khai báo đối tượng cảm biến MQ135

// Khai báo địa chỉ I2C của màn hình LCD 1602
#define LCD_ADDRESS 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS); // Khai báo kết nối LCD 1602 I2C

// Ngưỡng cảnh báo ppm
const float THRESHOLD = 1000.0;

// Chân kết nối cảm biến cảnh báo (còi)
const int BUZZER_PIN = 2;

void setup() {
  Serial.begin(9600);   // Khởi động kết nối Serial
  lcd.init();           // Khởi động LCD
  lcd.backlight();      // Bật đèn nền LCD
  pinMode(BUZZER_PIN, OUTPUT); // Chỉ định chân BUZZER_PIN là OUTPUT
} 

void loop() {
  float ppm = mq135_sensor.getPPM();  // Đọc giá trị ppm từ cảm biến MQ135
  Serial.print("PPM: ");
  Serial.print(ppm);
  Serial.println(" ppm");

  // Hiển thị giá trị ppm lên LCD
  lcd.setCursor(0, 0);
  lcd.print("PPM: ");
  lcd.print(ppm);

  // Kiểm tra nếu ppm vượt quá ngưỡng cảnh báo
  if (ppm > THRESHOLD) {
    lcd.setCursor(0, 1);
    lcd.print("Air quality high!");
    Serial.println("Air quality high!");
    digitalWrite(BUZZER_PIN, HIGH); // Bật cảnh báo âm thanh
  } else {
    lcd.setCursor(0, 1);
    lcd.print("                "); // Xóa dòng cảnh báo trên LCD nếu không vượt ngưỡng
    digitalWrite(BUZZER_PIN, LOW);  // Tắt cảnh báo âm thanh
  }

  delay(500);  // Đợi 500ms trước khi lấy giá trị ppm tiếp theo
}
