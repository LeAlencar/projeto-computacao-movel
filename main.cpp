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

Question questions[9] = {
    {"Arduino tem 14 portas digitais?", true, 1, 1},
    {"Pedro Alvares Cabral descobriu o Brasil?", true, 1, 1},
    {"Baleia azul e o maior animal vivo no planeta?", true, 1, 1},
    {"A segunda guerra mundial acabou em 1945?", true, 1, 1},
    {"As 3 leis da física foi criado por Newton?", true, 1, 1},
    {"Windows parou de atualizar no 10?", true, 1, 1},
    {"A lingua mais falada no mundo e ingles?", true, 1, 1},
    {"O alfabeto tem 27 letras?", true, 1, 1},
    {"Homem aranha foi o primeiro heroi da marvel?", true, 1, 1}};
/*
const String easyQuestions[] = {
    "Arduino tem 14 portas digitais?",
    "Pedro Alvares Cabral descobriu o Brasil?",
    "Baleia azul e o maior animal vivo no planeta?",
    "A segunda guerra mundial acabou em 1945?",
    "As 3 leis da física foi criado por Newton?",
    "Windows parou de atualizar no 10?",
    "A lingua mais falada no mundo e ingles?",
    "O alfabeto tem 27 letras?",
    "Homem aranha foi o primeiro heroi da marvel?",
    "A FEI perdeu o RoboCup 2022?",
    "A queda do muro de Berlim foi em 89?",
    "Vargas tomou o poder em 1930?",
    "O menor osso humano fica no ouvido?",
    "Steve Jobs faleceu em 2011?",
    "Arduino foi criado em 2005?",
    "O primeiro computador e de 1930?",
    "A revolucao industrial foi no sec.XX",
    "Ayrton Senna morreu na Franca?",
    "A FEI foi fundada em 1947?",
    "O BR ganhou a copa do mundo em 98?",
    "Steve Jobs foi CEO da Pixar?",
    "Ada Lovelace foi a primeira programadora?",
    "Ayrton Senna venceu 3 mundiais?",
    "A boneca barbie foi lancada em 59?",
    "O homem pisou na lua em 69?",
    "O tupi guarani e uma lingua oficial do BR?",
    "O Brasil tem 3 liguas oficiais?",
    "Cinderela a primeira princesa da Disney?",
    "Akira Toriyama faleceu dia 8 de marco de 2024?",
    "Bambam durou 1 minuto contra Popo?",
};

bool easyAnswers[] = {
    true,
    true,
    true,
    true,
    true,
    false,
    false,
    false,
    false,
    false,
    true,
    true,
    true,
    true,
    true,
    false,
    false,
    false,
    false,
    false,
    true,
    true,
    true,
    true,
    true,
    false,
    false,
    false,
    false,
    false,
};
 */
/*
String finalQuestions[]{
    "Chico moedas e um homem integro?",
    "Corinthians e o melhor time de todos?",
    "Este projeto merece uma nota 10?",
};

bool finalAnswers[3]{
    true,
    true,
    true,
};
*/

int questionIndex = 0;
int skipsRemaining = 3;
int currentLevel = 0;
int score = 0;
unsigned long questionStartTime;
const unsigned long questionTimeLimit = 100000;
const unsigned long warningTime = 3000;

void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);  // btn 1
  pinMode(10, INPUT_PULLUP); // btn 2
  pinMode(9, INPUT_PULLUP);  // btn 3
  pinMode(8, INPUT_PULLUP);  // btn 4
  pinMode(7, OUTPUT);        // green
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
}

void start()
{
  score = 0;
  questionIndex = 0;
  skipsRemaining = 3;
  nextQuestion();
  tone(A0, 1000, 500);
}

void nextQuestion()
{

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(questions[questionIndex].question);
  delay(1000);
  int lengthOfQuestion = questions[questionIndex].question.length();
  int scrollTimes = lengthOfQuestion > 16 ? lengthOfQuestion - 15 : 0;

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
}

void checkAnswer(bool isTrue)
{
  if (questions[questionIndex].answer == isTrue)
  {
    score += questions[questionIndex].points;
    questionIndex++;
    nextQuestion();
  }
  else
  {
    endGame(false);
  }
}

void endGame(bool won)
{
  lcd.clear();
  if (won)
  {
    lcd.print("Vitoria!");
    playSound(4); // Som de vitória
  }
  else
  {
    lcd.print("Errado! Fim.");
    questionIndex = 0;
    score = 0;
    skipsRemaining = 3;
    playSound(3); // Som de erro
  }
  lcd.setCursor(0, 1);
  lcd.print("Pontuacao: ");
  lcd.print(score);
  delay(2000);
  lcd.clear();
  lcd.print("Bem vindo!");
}

void playSound(int soundType)
{
  // soundType: 1 para acerto, 2 para pular, 3 para erro, 4 para vitória
}

void blinkWarning()
{
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
}

void skipQuestion()
{
  skipsRemaining--;
  questionIndex++;
  nextQuestion();
  tone(A0, 294);
  // Tocar som de pular (usando pino de som)
}
