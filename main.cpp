// C++ code
//
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 6, 5, 4, 3);
volatile byte start_state = LOW;

struct Question
{
  String question;
  bool answer;
  int level;
  int points;
};

Question questions[] = {
    {"Arduino 14 portas digitais?", true, 1, 10},
    {"Baleia azul>animal vivo?", true, 1, 10},
    {"WW2 acabou em 45?", true, 1, 10},
    {"Newton fez 3 leis fisica?", true, 1, 10},
    {"Windows 10 final att?", false, 1, 10},
    //{"Miranha marvel first hero?", false, 1, 10},
    //{"FEI lost RoboCup 2022?", false, 1, 10},

    {"Cold War acabou em 89?", true, 2, 20},
    {"Menor osso e no ouvido?", true, 2, 20},
    {"Arduino criado em 2005?", true, 2, 20},
    {"Primeiro PC de 1930?", false, 2, 20},
    {"Senna morreu na Franca?", false, 2, 20},
    //{"FEI fundada em 47?", false, 2, 20},
    //{"BR ganhou WorldCup 98?", false, 2, 20},

    {"Steve Jobs foi CEO Pixar?", true, 3, 30},
    {"Ada primeira programadora?", true, 3, 30},
    {"Senna venceu 3 mundiais?", true, 3, 30},
    {"Barbie foi lancada em 59?", true, 3, 30},
    {"Tupi e lingua oficial?", false, 3, 30},
    //{"Toriyama faleceu em 64?", false, 3, 30},
    //{"BambamVSPopo foi 1min?", false, 3, 30},

    //{"Chicoin=homem integro?", true, 4, 40},
    //{"Corinthians best team?", true, 4, 40},

};

int contador = 0;
int questionIndex = 0;
int skipsRemaining = 3;
int score = 0;
int correctAnswersPerLevel[4] = {0, 0, 0, 0};
bool gameActive = false;
unsigned long questionStartTime;
const unsigned long questionTimeLimit = 10000;
const unsigned long warningTime = 7000;

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  pinMode(2, INPUT_PULLUP);  // btn 1
  pinMode(10, INPUT_PULLUP); // btn 2
  pinMode(9, INPUT_PULLUP);  // btn 3
  pinMode(8, INPUT_PULLUP);  // btn 4
  pinMode(13, OUTPUT);       // red
  lcd.begin(16, 2);
  // tone(A0, 294);
  // delay(500);
  // noTone(A0);
  lcd.print("Bem vindo!");
}

void loop()
{

  if (digitalRead(8) == LOW)
  {
    checkAnswer(true);
  }
  else if (digitalRead(9) == LOW)
  {
    checkAnswer(false);
  }
  else if (digitalRead(2) == LOW)
  {
    start();
  }
  else if (digitalRead(10) == LOW)
  {
    skipQuestion();
  }
  if (gameActive)
  {
    if (millis() - questionStartTime > questionTimeLimit)
    {
      skipQuestion();
    }
    else if (millis() - questionStartTime > warningTime)
    {
      blinkWarning();
    }
  }
}

void start()
{
  gameActive = true;
  // randomizeQuestions();
  score = 0;
  questionIndex = 0;
  contador = 0;
  questionIndex = 0;
  skipsRemaining = 3;
  nextQuestion();
  tone(A0, 1000, 500);
  delay(100);
}

void nextQuestion()
{

  lcd.clear();
  Serial.println(contador);
  lcd.setCursor(0, 0);
  if (contador == 15)
  {
    lcd.print("Cor best team?");

    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pontos: ");
    lcd.print(score);
    lcd.setCursor(0, 1);
    lcd.print("Pulos: ");
    lcd.print(skipsRemaining);
  }
  else
  {
    lcd.print(questions[questionIndex].question);
    delay(1000);

    int lengthOfQuestion = questions[questionIndex].question.length();
    int scrollTimes = lengthOfQuestion > 16 ? lengthOfQuestion - 16 : 0;

    for (int positionCounter = 0; positionCounter < scrollTimes; positionCounter++)
    {
      lcd.setCursor(0, 0);
      lcd.scrollDisplayLeft();
      delay(200);
    }

    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pontos: ");
    lcd.print(score);
    lcd.setCursor(0, 1);
    lcd.print("Pulos: ");
    lcd.print(skipsRemaining);
    questionStartTime = millis();
  }
}

void checkAnswer(bool isTrue)
{

  if (gameActive)
  {
    if (questionIndex >= 15)
    {
      if (contador >= 15 && isTrue)
      {
        endGame(true);
        return;
      }
      else
      {
        endGame(false);
        return;
      }
    }
  }
  if (questions[questionIndex].answer == isTrue)
  {
    score += questions[questionIndex].points;
    tone(A0, 200);
    delay(1000);
    noTone(A0);

    questionIndex++;
    contador++;
    if (questionIndex > 15)
    {
      endGame(true); // Ganha se responder todas corretamente
    }
    else
    {
      nextQuestion();
    }
  }
  else
  {
    tone(A0, 100);
    delay(1000);
    noTone(A0);
    endGame(false); // Perde se errar qualquer pergunta
  }
}

void endGame(bool won)
{
  gameActive = false;
  lcd.clear();
  if (won)
  {
    lcd.print("Vitoria!");
    tone(A0, 200);
    delay(500);
    tone(A0, 300);
    delay(500);
    tone(A0, 400);
    delay(500);
    tone(A0, 500);
    delay(500);
    tone(A0, 600);
    delay(500);
    tone(A0, 700);
    delay(500);
    tone(A0, 780);
    delay(500);
    tone(A0, 800);
    delay(500);
    tone(A0, 900);
    delay(5000);
    noTone(A0);
  }
  else
  {
    lcd.print("Errado! Fim.");
    questionIndex = 0;
    score = 0;
    skipsRemaining = 3;
    tone(A0, 100);
    delay(1000);
    noTone(A0);
  }
  lcd.setCursor(0, 1);
  lcd.print("Pontuacao: ");
  lcd.print(score);
  delay(2000);
  lcd.clear();
  lcd.print("Bem vindo!");
}

void blinkWarning()
{

  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
}

void skipQuestion()
{
  contador++;
  skipsRemaining--;
  questionIndex++;
  nextQuestion();
  tone(A0, 294);
  delay(100);
  noTone(A0);
  // Tocar som de pular (usando pino de som)
}
