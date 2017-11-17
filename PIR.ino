#include<LiquidCrystal.h>
//Variabel PIR
int ledPin = 13;                // Memilih pin untuk LED
int inputPin = 6;               // Memilih input pin (untuk sensor PIR)
int pirState = LOW;             // Mengasumsi tidak ada gerakan terdeteksi
int val = 0;                    // Variabel untuk membaca status pin
int jumlah = 0;                 // variabel untuk menghitung masuk ornag
int PinSuhu = A0;               // Memilih input pin untuk sensor suhu
float suhu, data;               // penyimpanan nilai dari sensor

//variabel LED
//The circuit:
// * LCD RS pin to digital pin 12
// * LCD Enable pin to digital pin 11
// * LCD D4 pin to digital pin 5
// * LCD D5 pin to digital pin 4
// * LCD D6 pin to digital pin 3
// * LCD D7 pin to digital pin 2
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(ledPin, OUTPUT);      // Mendeklarasikan LED sebagai output
  pinMode(inputPin, INPUT);     // Mendeklarasikan sensor PIR sebagai input
  pinMode(PinSuhu, INPUT);      // Mendeklarasikan sensor suhu sebagai input
  
  lcd.begin(16, 2);             // Setting awal nomor colum dan baris pada LCD
  lcd.print("Orang = ");        // Menampilkan pesan orang
  
  Serial.begin(9600);
}

void loop(){
  lcd.setCursor(0, 1);                      // Memulai LCD
  val = digitalRead(inputPin);              // Membaca nilai masukan sensor PIR
  
  analogReference(INTERNAL);                // mengunakan Referensi 1.1 volt
  data = analogRead(PinSuhu);               // Membaca nilai masukan sensor Suhu
  
  if (val == HIGH) {                        // Memeriksa apakah input adalah TINGGI
      digitalWrite(ledPin, HIGH);           // Hidupkan LED ON

      suhu = data / 9.309;                  // 5V mengunakan 2.0479; 1.1V(internal) mengunakan 9.309
   
      if (pirState == LOW) {                // cek asumsi tidak ada gerakan
          jumlah++;
          
          Serial.print("Motion detected! "); // mencetak pada perubahan output, tidak menyatakan
          Serial.println(jumlah);              // menampilkan pada konsole

          Serial.print("suhu = ");          // just string
          Serial.println(suhu);                // menampilkan nilai suhu
          
          lcd.print(jumlah);                 // menampilkan pada LCD
          
          pirState = HIGH;                   // di asumsikan ada gerakan terdeteksi
      }
  } else {
      digitalWrite(ledPin, LOW);             // turn LED OFF

      if (pirState == HIGH) {                // cek asumsi ada gerakan
          
          Serial.println("Motion ended!");   // mencetak pada perubahan output, tidak ada orang
          
          Serial.print("suhu = ");           // just string
          Serial.println(suhu);                // menampilkan nilai suhu
          
          pirState = LOW;                    // di asumsikan tidak ada gerakan terdeteksi
    }
  }
}
