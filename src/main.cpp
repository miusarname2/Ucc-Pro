#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

constexpr uint8_t BUTTON_PIN = 3;
constexpr uint8_t BUZZER_PIN = 6;
constexpr uint8_t SERVO_PIN = 13;
constexpr int SERVO_FORWARD_US = 2000;
constexpr uint8_t SCREEN_WIDTH = 128;
constexpr uint8_t SCREEN_HEIGHT = 64;

struct Note {
  uint16_t frequency;
  uint16_t durationMs;
};

// Original short festive melody; repeats while the button is held.
constexpr Note MELODY[] = {
    {784, 220}, {988, 220}, {1175, 360}, {988, 220},
    {880, 220}, {1047, 360}, {880, 220}, {784, 420},
};
constexpr size_t MELODY_LENGTH = sizeof(MELODY) / sizeof(MELODY[0]);

Servo continuousServo;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
bool servoRunning = false;
bool displayReady = false;
size_t currentNote = 0;
unsigned long nextNoteAt = 0;

void showStatus(bool interacting) {
  if (!displayReady) {
    return;
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  if (interacting) {
    display.setTextSize(2);
    display.setCursor(10, 16);
    display.println(F("Interactu"));
    display.setCursor(22, 40);
    display.println(F("ando..."));
  } else {
    display.setTextSize(1);
    display.setCursor(16, 28);
    display.println(F("Pulsa el boton"));
  }
  display.display();
}

void startMelody() {
  currentNote = 0;
  nextNoteAt = 0;
}

void updateMelody() {
  if (!servoRunning) {
    return;
  }

  const unsigned long now = millis();
  if (static_cast<long>(now - nextNoteAt) < 0) {
    return;
  }

  const Note note = MELODY[currentNote];
  tone(BUZZER_PIN, note.frequency, note.durationMs);
  nextNoteAt = now + note.durationMs + 50;
  currentNote = (currentNote + 1) % MELODY_LENGTH;
}

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  continuousServo.attach(SERVO_PIN);
  continuousServo.writeMicroseconds(1500);
  continuousServo.detach();

  displayReady = display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  if (!displayReady) {
    Serial.println(F("No se pudo iniciar la pantalla OLED SSD1306."));
  } else {
    display.setRotation(2);
    showStatus(false);
  }
}

void loop() {
  const bool buttonPressed = digitalRead(BUTTON_PIN) == LOW;

  if (buttonPressed && !servoRunning) {
    continuousServo.attach(SERVO_PIN);
    continuousServo.writeMicroseconds(SERVO_FORWARD_US);
    servoRunning = true;
    startMelody();
    showStatus(true);
  } else if (!buttonPressed && servoRunning) {
    continuousServo.detach();
    servoRunning = false;
    noTone(BUZZER_PIN);
    showStatus(false);
  }

  updateMelody();
}