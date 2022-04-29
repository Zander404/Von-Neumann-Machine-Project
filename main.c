#include <stdio.h>
#include <stdlib.h>
#include "Cpu.h"

//Variavéis para a CPU
unsigned char memoria[154];
unsigned int mbr;          // 32 bits
unsigned int mar;          // 32 bits, mas precisa apenas de 21
unsigned char ir;          //  8 bits
unsigned char ro0;         //  8 bits, mas deveria ser de 3 bits
unsigned char ro1;         //  8 bits, mas deveria ser de 3 bits
unsigned int imm;          // 32 bits, mas deveria ser de 21 bits
unsigned int pc = 0;       // 32 bits
unsigned char l, g, e;     //  8 bits
unsigned int reg[8];       // 32bits

int count = 0;

void busca(){
    mar = pc;
    mbr = memoria[mar++];
    for (int i = 0; i<3; i++){
        mbr = mbr  << 8;
        mbr = (mbr | memoria[mar++] );
    }
};

void decodifica(){
    ir = mbr >> 24;
    if(ir >= 2 & ir <= 10) {
        //formato de funcoes basicas de matematicas
        ro0 = (mbr&mask0)>>21;
        ro1 = (mbr&mask1)>>18;

        printf("\n %x ", ro0);
        printf("\n %x", ro1);
    }

    if(ir == 11 ){
        // formato para o commando do tipo NOT
        ro0 = (mbr&mask0)>>21;
    }

    if(ir >=12 & ir<=18){
        // formato de funcao jump
        mar = mbr & maskendereco;
    }

    if(ir>=19 & ir<=20){
        //formato para a funcao store e load
        ro0 = (mbr&mask0)>>21;
        mar = (mbr&maskendereco);
    }
    if(ir>=21 & ir<= 27){
        //formato para a funcao movi, addi, subi

        ro0 = (mbr&mask0)>>21;
        imm = mbr&maskendereco;

    }
}

void executa(){

    if(ir==hlt){
        //Parar a execucao do programa

    }


    if(ir==nop){
        //Pegar o proximo conjunto de instrucoes
    pc+=4;
    }


    if(ir==add){
        //Somar o valor de reg[r0] do valor de reg[ro1]

        reg[ro0] = reg[ro0]+reg[ro1];
        pc+=4;
    }


    if(ir==sub){
        //Subtrair o valor de reg[r0] do valor de reg[ro1]
        reg[ro0] = reg[ro0]-reg[ro1];
        pc+=4;
    }


    if(ir==mult){
        //Multiplicar o valor de reg[r0] do valor de reg[ro1]
        reg[ro0] = reg[ro0]*reg[ro1];
        pc+=4;
    }


    if(ir== div){
        //Dividir o valor de reg[r0] do valor de reg[ro1]
        reg[ro0] = reg[ro0]/reg[ro1];
        pc+=4;
    }


    if(ir==cmp){
        //Comparar o valor de reg[r0] do valor de reg[ro1]
        if(ro0==ro1){
            e=1;
            l=0;
            g=0;
        }
        if(ro0<ro1){
            e=0;
            l=1;
            g=0;
        }
        if(ro0>ro1){
            e=0;
            l=0;
            g=0;
        }
        pc+=4;
    }

    if(ir==movr){
        //Mover o valor do reg[ro0] para o reg[ro1]
        reg[ro0]=reg[ro1];
        pc+=4;
    }


    if(ir==and){
        reg[ro0]=reg[ro0]&reg[ro1];
        pc+=4;
    }


    if(ir==or){
        reg[ro0]=reg[ro0]|reg[ro1];
        pc+=4;

    }


    if(ir==xor){
        reg[ro0]=reg[ro0]^reg[ro1];
        pc+=4;
    }


    if(ir==not){
        reg[ro0] = !reg[ro0];
        pc+=4;

    }


    if(ir==je){
        if(e==1)
            pc = memoria[mar];


    }


    if(ir==jne){
        if (e==0)
            pc = memoria[mar];


    }


    if(ir==jl){
        if(l==1)
            pc =memoria[mar];

    }


    if(ir==jle){
        if(l==1 || e==1)
            pc = memoria[mar];

    }


    if(ir==jg){
        if(g==1)
            pc = memoria[mar];

    }


    if(ir==jge){
        if(g==1 || e ==1)
            pc = memoria[mar];

    }


    if(ir==jmp){
        pc = memoria[mar];

    }


    if(ir==ld){
        reg[ro0] = memoria[mar];

    }


    if(ir==st){
        memoria[mar] = reg[ro0];

    }


    if(ir==movi){
        reg[ro0] = imm;

    }


    if(ir==addi){
        reg[ro0] = reg[ro0] + imm;

    }


    if(ir==subi){
        reg[ro0] = reg[ro0] - imm;

    }


    if(ir==multi){
        reg[ro0] = reg[ro0]*imm;

    }


    if(ir==divi){
        reg[ro0] = reg[ro0]/imm;

    }


    if(ir==lsh){
        reg[ro0] = reg[ro0]<<imm;

    }


    if(ir==rsh){
        reg[ro0] = reg[ro0]>>imm;

    }

}






int main() {
    memoria[0] = 0x13; //0001 0010 OP
    memoria[1] = 0x40; //0100 0000 RO0 e RO1
    memoria[2] = 0x21; //0010 0001
    memoria[3] = 0x1e; //0001 1101
    memoria[4] = 0x16; //0001 0110
    memoria[5] = 0x0;  //0000 0000
    memoria[6] = 0x0;  //0000 0000
    memoria[7] = 0x14; //0001 0100
    memoria[30] = 0x0; //0000 0000
    memoria[31] = 0x0; //0000 0000
    memoria[32] = 0x0; //0000 0000
    memoria[33] = 0xf; //0000 1111
    //while(ir!=hlt){
    busca();
    printf("%x", mbr);
    decodifica();
    executa();
    printf("\n %x", ro0);
    printf("\n %x", reg[0]);
   // }

}