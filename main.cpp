// C++ code
//
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 6, 5, 4, 3);
volatile byte start_state = LOW;

String easyQuestions[5] = {
    // TODO - Adicionar questões e respostas
    "Arduino tem 14 portas digitais?",
};
bool easyQuestionsResponse[5] = {};

String mediumQuestions[5] = {};
String hardQuestions[5] = {};
bool gameActive = false;
int questionIndex = 0;
int score = 0;
int scrollPosition = 0;

void setup()
{
  pinMode(2, INPUT_PULLUP);  // btn 1
  pinMode(8, INPUT_PULLUP);  // btn 2
  pinMode(9, INPUT_PULLUP);  // btn 3
  pinMode(10, INPUT_PULLUP); // btn 4
  pinMode(7, OUTPUT);        // green
  pinMode(13, OUTPUT);       // red
  lcd.begin(16, 2);
  lcd.print("Bem vindo!");
  attachInterrupt(digitalPinToInterrupt(2), start, FALLING);
}

void loop()
{

  if (gameActive)
  {
    if (digitalRead(8) == LOW)
    {
      printf("Foi");
    }
    else if (digitalRead(9) == LOW)
    {
      printf("Foi");
    }
    else if (digitalRead(10) == LOW)
    {
      nextQuestion();
    }
  }
}

void start()
{

  gameActive = true;
  score = 0;
  nextQuestion();
}

void nextQuestion()
{
  questionIndex = random(0, 5);
  lcd.clear();
  lcd.print(easyQuestions[0]);
  delay(3000);
  for (int positionCounter = 0; positionCounter < 16; positionCounter++)
  {
    lcd.scrollDisplayLeft();
    lcd.setCursor(0, 1);
    delay(2000);
    // lcd.print("Pontuacao: ");
    // lcd.print(score);
    // delay(150);
  }
}
