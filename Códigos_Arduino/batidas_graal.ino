// 60 minutos LTDA
// Dispositivo de Batidas Sala Graal
//13 de Julho de 2018
// Um piezo elétrico é escondido na parede a fim de fornecer uma tensão quando as batidas acontecem, essa leitura acontece na porta analógica do ATMEGA328P com um resistor de 1M ohms em paralelo, 
//caso aconteça as três batidas o microcontrolador ativa o sinal no relé para a abertura da fechadura eletromagnética. 
//A placa de controle é feita como stand alone.
//Dois push-buttons são usados para aumentar ou diminuir a sensibilidade das batidas que é armazenado na memória EEPROM
//a chave de 2 estados indica o modo de configuração e funcionamento do dispositivo.


#include "EEPROM.h"  //Biblioteca para armazenamento de valores na memória

//Indicação das portas e variáveis do programa
int botao = 9; // Chave de dois estados para configuração
int rele = 1; // Rele para ativar ou desativar 
int mais = 8; // Push button para aumentar a sensibilidade
int menos = 7; // Push Button para diminuir a sensiblidade
int coeficiente = EEPROM.read(2); // Gravação do coeficiente de sensibilidade no endereço da memória EEPROM
int buzzer = 2;
int batidas = 0;
int leitura = 0; // Variável para a leitura da porta analógica do piezoelétrico



//Funções de melodia do buzzer
void bip_but(){
 tone(buzzer,2000,100);delay(100);tone(buzzer,2500,100); 
}

void bip_rong(){
int tempo = 500;
  tone(buzzer,8000,400);delay(tempo);tone(buzzer,8000,400);
}


void bip(){
  
tone(buzzer,1599,100);delay(100);tone(buzzer,1299,100);delay(100);
 tone(buzzer,1499,100);delay(100);tone(buzzer,1399,100);delay(100);
tone(buzzer,1299,100);delay(100);tone(buzzer,1499,100);delay(1000); 
  
}



void setup() {
  pinMode(buzzer,OUTPUT);

  pinMode(botao, INPUT_PULLUP);
  pinMode(mais, INPUT_PULLUP);
  pinMode(menos, INPUT_PULLUP);
  pinMode(rele, OUTPUT);
  digitalWrite(rele,LOW);

 // Se os dois push button são apertados volta a configuração inicial
  if (!digitalRead(mais) && !digitalRead(menos)){
    coef(200);
    bip();
  }

 // Se a chave é ativada inicia a função de configuração
  if(!digitalRead(botao)){
    congifcoef(); 
  }


}
// Funçao para gravação do coeficiente na memrória EEPROM
void coef(int x){
  EEPROM.write(2,x);
  coeficiente = x;

}

// Função para a alteração do coeficiente a partir dos push buttons
void congifcoef(){
    int cof = coeficiente;
  
      while(!digitalRead(botao)){
      if(!digitalRead(mais)){
        cof = cof+10;
        bip_but();
        coeficiente = cof;
        while(!digitalRead(mais));
        delay(200); 
      }

      if(!digitalRead(menos)){
        bip_but();
        cof= cof-10;
        coeficiente = cof;
        while(!digitalRead(menos));
        delay(200); 
      }

    }
    coef(cof);
    delay(2000);
 }

void loop() {

  leitura = analogRead(0); // Leitura da porta analógica
  if (leitura > coeficiente){ // Condição para verificar se a batida acontece
    while(leitura>coeficiente){
      leitura = analogRead(0);
    }
    bip_but();
    batidas++;
    }
   
    if (batidas==3) { // Se as batidas foram iguais a 3 a relé é ativado
      bip();
      digitalWrite(rele, HIGH);
      delay(1000);
      digitalWrite(rele, LOW);
      batidas=0;
    }



}

