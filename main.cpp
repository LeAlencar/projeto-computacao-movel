// C++ code
//
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 6, 5, 4, 3);
volatile byte start_state = LOW;

String easyQuestions[10] = {
  // TODO - Adicionar questões e respostas
  "Arduino tem 14 portas digitais?",
  "Pedro Alvares Cabral descobriu o Brasil?",
  "Baleia azul e o maior animal vivo no planeta?"
  "A segunda guerra mundial acabou em 1945?"
  "As 3 leis da física foi criado por Newton?"
  "Windows parou de atualizar no 10?"
  "A lingua mais falada no mundo e ingles?"
  "O alfabeto tem 27 letras?"
  "Homem aranha foi o primeiro heroi da marvel?"
  "A FEI perdeu o RoboCup 2022?"
};
bool easyAnswers[10] = {
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

String mediumQuestions[10] = {
  "A queda do muro de Berlim foi em 89?"
  "Vargas tomou o poder em 1930?"
  "O menor osso humano fica no ouvido?"
  "Steve Jobs faleceu em 2011?"
  "Arduino foi criado em 2005?"
  "O primeiro computador e de 1930?"
  "A revolucao industrial foi no sec.XX"
  "Ayrton Senna morreu na Franca?"
  "A FEI foi fundada em 1947?"
  "O BR ganhou a copa do mundo em 98?"
};
bool mediumAnswers[10]{
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
}

String hardQuestions[10] = {
  "Steve Jobs foi CEO da Pixar?"
  "Ada Lovelace foi a primeira programadora?"
  "Ayrton Senna venceu 3 mundiais?"
  "A boneca barbie foi lancada em 59?"
  "O homem pisou na lua em 69?"
  "O tupi guarani e uma lingua oficial do BR?"
  "O Brasil tem 3 liguas oficiais?"
  "Cinderela a primeira princesa da Disney?"
  "Akira Toriyama faleceu dia 8 de marco de 2024?"
  "Bambam durou 1 minuto contra Popo?"
};
bool hardAnswers[10]{
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
}

String finalQuestion[3]{
  "Chico moedas e um homem integro?"
}
bool finalAnswer[3]{
  true,
}
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
