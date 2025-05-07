#include <stdio.h>   // Para comandos básicos de entrada e saída
#include <stdlib.h>  // Para alocação de memória, controle de processos e números aleatórios
#include <math.h>    // Para funções matemáticas
#include <time.h>    // Para inicializar o gerador de números aleatórios com base no tempo

int HammingCode[16];
int HammingPosition[16];
int ErrorSelected;
int sums[5];
int WrongBit[2];

void SetHammingCode();
void CalcParities();
void SetParities();
void ErrorEvent();

int main(){
     int Choice, chute, rodadas;

     srand(time(NULL));

     printf("Olá. Quantas rodadas você quer jogar? \n");
     scanf("%d", &rodadas);

     for (int zz = 0; zz < rodadas; zz++) {
          ErrorSelected = rand() % 2;
          SetHammingCode();
          SetHammingCode();
          CalcParities();
          SetParities();
          ErrorEvent(ErrorSelected);
          printf("Rodada %d \n", zz +1);
          printf("Tente com este. A paridade é par, e os bits de paridade são os de numeração 1,2,4 e 8 \n");
          for(int bb = 0; bb < 16; bb++) {
               printf("%02d ",HammingPosition[bb]);
          }

          printf("\n");
          for(int bb = 0; bb < 16; bb++) {
               printf(" %d ", HammingCode[bb]);
          }

          printf("\n Nesse caso, qual a resposta? \n");
          printf("\t 1. Não há erro. \n");
          printf("\t 2. Há 1 erro. \n");
          //printf("\t 1. Há mais de um erro. \n");
     scanf("%d", &Choice);

          switch(Choice) {
               case 1:
                    if (Choice - 1 == ErrorSelected) {
                         printf("Correto! \n");
                    } else {
                         printf("Errado! Há sim um bit errado, o bit %d. \n", WrongBit[0]);
                    }
                    break;
               case 2:
                    printf("Em qual bit há o erro? \n");
                    scanf("%d", &chute);
                    if (chute == WrongBit[0]) {
                         printf("Correto!");
                    } else {
                         if (Choice - 1 != ErrorSelected) {
                              printf("Errado! Não houve erro no código, ele estava correto.");
                         } else {
                              printf("Errou! o bit errado é o bit %d. \n", WrongBit[0]);
                         }
                         
                    }
                    break;
          }
     } 
     return 0;
}  

void SetHammingCode() {
     double base = 2;
     double result;
     double resto;


     for (int aa = 1; aa < 16; aa++) {
          result = log(aa) / log(base);
          resto = fmod(result, 1.0);
          HammingPosition[aa] = aa;
          if (resto == 0) {
               HammingCode[aa] = 0;
          } else {
               HammingCode[aa] = rand() % 2;
          }
     }
}

void CalcParities() {
     int checkone, checktwo, checkfour, checkeight = 2;

     for (int cc = 2; cc < 16; cc++) {
          if (checkone < 2) {
               sums[1] += HammingCode[cc];
               checkone++;
           } else  if (checkone > 1) {
               checkone = 1;
               continue;
          } 
     }

     for (int dd = 3; dd < 16; dd++) {
          if (checktwo < 2) {
               sums[2] += HammingCode[dd];
               checktwo++;
           } else  if (checktwo > 4) {
               checktwo = 2;
               continue;
          } else {
               checktwo++;
               continue;
          }
     } 
     

     for (int ee = 5; ee < 16; ee++) {
          if (checkfour < 4) {
               sums[3] += HammingCode[ee];
                checkfour++;
          } else if (checkfour > 8) {
               checkfour = 2;
               continue;
          } else {
               checkfour++;
               continue;
          }
     }

     for (int ff = 9; ff <16; ff++) {
          if (checkeight < 8) {
               sums[4] += HammingCode[ff];
               checkeight++;
          } else if (checkeight > 16) {
               checkeight = 2;
               continue;
          } else {
               checkeight++;
               continue;
          }

          for (int gg = 1; gg < 16; gg++) {
               sums[0] += HammingCode[gg];
          } 
     }

     
}

void SetParities() {
     int ParityBits[2][5] = {{0,0,0,0,0}, {0,1,2,4,8}};
     enum Parity {
          PAR = 0,
          IMPAR = 1
     };

     for (int hh = 0; hh < 5; hh++) {
          ParityBits[0][hh] = sums[hh] % 2;
          if (ParityBits[0][hh] == IMPAR) {
               HammingCode[ParityBits[1][hh]] = 1;
          } else {
               HammingCode[ParityBits[1][hh]] = 0;
          }
     }

}

void ErrorEvent (){
//     int ErrorPlaceSelected[16];
     int ErrorEventSelected;
     if (ErrorSelected == 1) {
         ErrorEventSelected = rand() % 16;
         if (HammingCode[ErrorEventSelected] == 0) {
               HammingCode[ErrorEventSelected] = 1;
          } else {
               HammingCode[ErrorEventSelected] = 0;
          }
          WrongBit[0] = HammingPosition[ErrorEventSelected];
     } 
}

