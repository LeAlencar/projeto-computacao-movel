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
  "Corinthians e o melhor time de todos?"
  "Este projeto merece uma nota 10?"
}
bool finalAnswer[3]{
  true,
  true,
  true,
}
bool gameActive = false;
int questionIndex = 0;
int skipsRemaining = 3;
int currentLevel = 0;
int score = 0;
int correctAnswer = 0;
unsigned long questionStartTime;
const unsigned long questionTimeLimit = 100000;
const unsigned long warningTime = 3000;
bool isQuestionFullyDisplayed = false;
unsigned long lastScrollTime = 0;
bool isScrolling = false;
int scrollPosition = 0; // Nova variável para controlar a posição da rolagem
String question;

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
    unsigned long currentTime = millis();
    // Lógica do tempo de resposta
    if (currentTime - questionStartTime > questionTimeLimit)
    {
      skipQuestion();
    }
    else if (currentTime - questionStartTime > questionTimeLimit - warningTime)
    {
      blinkWarning();
    }

    // Verificação dos botões
    if (digitalRead(8) == LOW)
    {
      checkAnswer(true);
    }
    else if (digitalRead(9) == LOW)
    {
      checkAnswer(false);
    }
    else if (digitalRead(10) == LOW && skipsRemaining > 0)
    {
      skipQuestion();
    }

    if (isQuestionFullyDisplayed)
    {
      showOptionsAndScore();
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
  if (correctAnswer >= 5)
  {
    correctAnswer = 0;
    currentLevel++;
    if (currentLevel > 3)
    {
      endGame(true);
      return;
    }
  }
  questionIndex = random(0, 10);
  currentLevel = 0;

  switch (currentLevel)
  {
  case 0:
    question = easyQuestions[questionIndex];
    break;
  case 1:
    question = mediumQuestions[questionIndex];
    break;
  case 2:
    question = hardQuestions[questionIndex];
    break;
  case 3:
    question = finalQuestions[random(0, 3)];
    break;
  }
  lcd.clear();
  lcd.print(question);
  isQuestionFullyDisplayed = question.length() <= 16;
  if (!isQuestionFullyDisplayed)
  {
    lastScrollTime = millis();
    isScrolling = true;
    scrollPosition = 0;
  }
  else
  {
    showOptionsAndScore(); // Chame aqui se a pergunta couber na tela sem rolagem
  }
}

void checkAnswer(bool isYes)
{
  bool correctAnswer = false;
  if (currentLevel < 3)
  {
    switch (currentLevel)
    {
    case 0:
      correctAnswer = easyAnswers[questionIndex];
      break;
    case 1:
      correctAnswer = mediumAnswers[questionIndex];
      break;
    case 2:
      correctAnswer = hardAnswers[questionIndex];
      break;
    }

    if ((isYes && correctAnswer) || (!isYes && !correctAnswer))
    {
      score += currentLevel + 1;
      correctAnswer++;
      nextQuestion();
      // Tocar som de acerto
    }
    else
    {
      endGame(false); // Jogador errou a pergunta
    }
  }
  else
  {
    // Lógica para a pergunta final
    if (isYes == finalAnswers[random(0, 3)])
    {
      endGame(true); // Jogador venceu o jogo
    }
    else
    {
      endGame(false); // Jogador errou a pergunta final
    }
  }
}

void endGame(bool won)
{
  gameActive = false;
  lcd.clear();
  if (won)
  {
    lcd.print("Vitoria!");
    playSound(4); // Som de vitória
  }
  else
  {
    lcd.print("Errado! Fim.");
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
