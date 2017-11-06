int ledPin = 13;                // Memilih pin untuk LED
int inputPin = 2;               // Memilih input pin (untuk sensor PIR)
int pirState = LOW;             // Kita mulai, dengan asumsi tidak ada gerakan terdeteksi
int val = 0;                    // Variabel untuk membaca status pin
int jumlah = 0;

void setup() {
  pinMode(ledPin, OUTPUT);      // Mendeklarasikan LED sebagai output
  pinMode(inputPin, INPUT);     // Mendeklarasikan sensor sebagai input
  Serial.begin(9600);
}

void loop(){
  val = digitalRead(inputPin);  // Membaca nilai masukan
  if (val == HIGH) {            // Memeriksa apakah input adalah TINGGI
    digitalWrite(ledPin, HIGH); // Hidupkan LED ON
//    delay(0);
   
    if (pirState == LOW) {
      jumlah++;
      // Kita baru saja diaktifkan
      Serial.print("Motion detected! ");
      Serial.println(jumlah);
      // Kami hanya ingin mencetak pada perubahan output, tidak menyatakan
      pirState = HIGH;
    }
  } else {
      digitalWrite(ledPin, LOW); // turn LED OFF
//      delay(0);   
      if (pirState == HIGH){
      // Kita baru saja dimatikan
      Serial.println("Motion ended!");
      // Kami hanya ingin mencetak pada perubahan output, tidak menyatakan
      pirState = LOW;
    }
  }
}
