// 60 minutos LTDA
// Dispositivo da bomba Sala Hora Zero.
//13 de Julho de 2018
// Um display LCD, um teclado alfanúmerico e uma placa de controle simulam uma bomba, na qual o usuário após digitar a senha correta a ativa ao invés de desativar. Um Buzzer apita a cada intervalo de tempo 
// para simular a bomba em funcionamento
//A placa de controle é feita como stand alone.



#include <Keypad.h> // BIBLIOTECA PARA O FUNCIONAMENTO DO TECLADO DE MEMBRANA
#include <LiquidCrystal.h>  // Biblioteca para o display LCD
#define BUZZER 0 // Pino do Buzzer NO ATMEGA

LiquidCrystal lcd(6, 5, 4, 3, 2, 1); //Pino para o display LCD

unsigned long previousMillis = 0; // Variável para guardar o tempo 1
unsigned long previousMillis2 = 0; // Variável para guardar o tempo 2
const long interval = 2000; // Variável para o tempo de espera 1
const long interval2 = 440; // Variável para o tempo de espera 1           
char key; // Variável que guarda a letra apertada no teclado
int BuzzerState=LOW; 
int lcdState=LOW;

char key2[6]; // Variável que guarda a senha completa que o usuário digita
char* password = "251092"; //SENHA CORRETA PARA DESTRANCAR A FECHADURA
int position_2=0;
const byte ROWS = 4; //NUMERO DE LINHAS DO TECLADO
const byte COLS = 3; //NUMERO DE COLUNAS DO TECLADO
char keys[ROWS][COLS] = { //DECLARAÇÃO DOS NUMEROS, LETRAS E CARACTERES DO TECLADO
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};

byte rowPins[ROWS] = { 7, 8, 9, 10 }; // PINOS DE CONEXAO DAS LINHAS DO TECLADO
byte colPins[COLS] = { 11, 12, 13 }; //PINOS DE CONEXAO DAS COLUNAS DO TECLADO

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );//AS VARIAVEIS rowPins E colPins RECEBERÃO O VALOR DE LEITURA DOS PINOS DAS LINHAS E COLUNAS RESPECTIVAMENTE

void setLocked(int locked){ //TRATANDO O ESTADO
  // Se a senha correta for digitada a bomba é ativada indicando o seu inicios e a o Buzzer fica apitando em intervalos regulares de tempo
if(!locked){ 
    lcd.clear();    
    lcd.setCursor(1, 0);
    lcd.print("PROTOCOLO HORA");
    lcd.setCursor(1, 1);
    lcd.print("ZERO INICIADO");
    tone(BUZZER,660,100);delay(100); tone(BUZZER,660,100);delay(100);tone(BUZZER,660,100);delay(100); tone(BUZZER,660,100);delay(100);tone(BUZZER,660,100);delay(100);
    tone(BUZZER,660,100);delay(100); tone(BUZZER,660,100);delay(100);tone(BUZZER,660,100);delay(100); tone(BUZZER,660,100);delay(100);tone(BUZZER,660,100);delay(100);
    tone(BUZZER,660,100);delay(100); tone(BUZZER,660,100);delay(100);tone(BUZZER,660,100);delay(100); tone(BUZZER,660,100);delay(100);tone(BUZZER,660,100);delay(100);
    noTone(BUZZER);

    while(1){
      unsigned long currentMillis = millis();


      if (currentMillis - previousMillis2 >= interval2) {
  
  
    previousMillis2 = currentMillis;
    if (BuzzerState == LOW) {
      BuzzerState = HIGH;
      tone(BUZZER,4000);
    }
    else {
       BuzzerState = LOW;
       noTone(BUZZER);
    }

   //digitalWrite(BUZZER,BuzzerState);
  }
      if (currentMillis - previousMillis >= interval) {
  
    previousMillis = currentMillis;
    if (lcdState == LOW) {
      lcdState = HIGH;
    lcd.clear();    
    lcd.setCursor(1, 0);
    lcd.print("PORTA TRANCADA");
    lcd.setCursor(3, 1);
    lcd.print("CODE 0479");
    }
    else {
    lcdState = LOW;
    lcd.clear();    
      lcd.setCursor(1, 0);
    lcd.print("PROTOCOLO HORA");
    lcd.setCursor(1, 1);
    lcd.print("ZERO INICIADO");
    }

  }
    }
}
}

void setup(){
  pinMode(BUZZER, OUTPUT);
  lcd.begin(16, 2);
  setLocked(true); //ESTADO INICIAL 
  
}

void loop(){

    lcd.clear();
  

 key = keypad.getKey(); //LEITURA DAS TECLAS PRESSIONADAS 


if(key!=NO_KEY){
// Armazenamento de cada caractere inserido pelo usuário
key2[position_2]=key;
// Verificação da senha digitada pelo usuário
position_2++;
  if(position_2==6){
    if((key2[0]=='2') && (key2[1]=='5')&&(key2[2]=='1') && (key2[3]=='0')&&(key2[4]=='9') && (key2[5]=='2')){
      setLocked(false);
    }
  else{
    lcd.setCursor(0, 0);
    lcd.print("INSIRA O CODIGO:");
    lcd.setCursor(5,1);
    lcd.print(key2[0]);
    lcd.setCursor(6,1);
    lcd.print(key2[1]);
    lcd.setCursor(7,1);
    lcd.print(key2[2]);
    lcd.setCursor(8,1);
    lcd.print(key2[3]);
    lcd.setCursor(9,1);
    lcd.print(key2[4]);
    lcd.setCursor(10,1);
    lcd.print(key2[5]);
    
    noTone(BUZZER);
    delay(200);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("SENHA ERRADA");
    //Limpa o display depois da tentativa de inserir a senha
    key2[0]='\0';
    key2[1]='\0';
    key2[2]='\0';
    key2[3]='\0';
    key2[4]='\0';
    key2[5]='\0';
 
    
    position_2=0;
    

    
    tone(BUZZER,500,1000);
    delay(1000);
    noTone(BUZZER);
   
    }
  }
}
 
  if(key){
    noTone(BUZZER);
    tone(BUZZER,660);
    delay(10);
    noTone(BUZZER);
    

    
  }
  
    lcd.setCursor(0, 0);
    lcd.print("INSIRA O CODIGO:");
    lcd.setCursor(5,1);
    lcd.print(key2);


delay(100);
}

