#include <stdio.h>
#include <stdlib.h>
#include "Cpu.h"

//Variavéis para a CPU
unsigned char memoria[154];//  8 bits 0000 0000
unsigned int mbr;          // 32 bits
unsigned int mar;          // 32 bits, mas precisa apenas de 21
unsigned char ir;          //  8 bits
unsigned char ro0;         //  8 bits, mas deveria ser de 3 bits
unsigned char ro1;         //  8 bits, mas deveria ser de 3 bits
unsigned int imm;          // 32 bits, mas deveria ser de 21 bits
unsigned int pc = 0;       // 32 bits
unsigned char l, g, e;     //  8 bits lower, greater, equal
unsigned int reg[8];       // 32bits

void busca(){
    mar = pc;
    mbr = memoria[mar++];
    for (int i = 0; i<3; i++){
        mbr = mbr  << 8;
        mbr = (mbr | memoria[mar++]);
    }
};

//void busca(){
//    mar = pc;
//    mbr = memoria[mar++]; //mbr = 32 bits |  memoria = 8 bits 32/8  =     mbr =0000 0000 0000 0000  xxxx xxxx yyyy yyyy
//
//    for(int i =0; i<3; i++) {
//        mbr = mbr << 8;
//        mbr = (mbr | memoria[mar++]);
//    }
//}

//
void decodifica(){
    ir = mbr >> 24;

    if( ir >= 0x02 & ir <=0xa ) {
        //formato de funcoes basicas de matematicas
        ro0 = (mbr&mask0)>>21;
        ro1 = (mbr&mask1)>>18;

        printf("\n %x ", ro0);
        printf("\n %x", ro1);
    }

    if(ir == 0xb ){
        // formato para o commando do tipo NOT
        ro0 = (mbr&mask0)>>21;
    }

    if(ir >= 0xc & ir<=0x12){
        // formato de funcao jump
        mar = mbr & maskendereco;
    }

    if(ir>=0x13 & ir<=0x14){
        //formato para a funcao store e load
        ro0 = (mbr&mask0)>>21;
        mar = (mbr&maskendereco);
    }
    if(ir>=0x15 & ir<= 0x1b){
        //formato para a funcao movi, addi, subi

        ro0 = (mbr&mask0)>>21;
        imm = (mbr&maskendereco);

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
        //Fazer a comparação logica AND entre o registrador ro0 e ro1, e por fim armazenar o resultado em ro0
        reg[ro0]=reg[ro0]&reg[ro1];
        pc+=4;
    }


    if(ir==or){
        //Fazer a comparação LOGICA OR entre os registradores ro0 e ro1, e por fim armazenar o resultado em ro0
        reg[ro0]=reg[ro0]|reg[ro1];
        pc+=4;

    }


    if(ir==xor){
        //Fazer a comparacao LOGICA XOR( Ou Exclusivo), onde armazenara o resultado no ro0
        reg[ro0]=reg[ro0]^reg[ro1];
        pc+=4;
    }


    if(ir==not){
        //Altera o valor atual do registrador ro0 pelo seu inverso
        reg[ro0] = !reg[ro0];
        pc+=4;

    }


    if(ir==je){
        //JUMP IF EQUAL:pula para um enderço de memoria, caso executa o valor de E seja igual a 1.
        if(e==1)
            pc = memoria[mar];


    }


    if(ir==jne){
        //JUMP NOT EQUAL: caso o valor de e==0, pule para o endereco de memoria do MAR.
        if (e==0)
            pc = memoria[mar];


    }


    if(ir==jl){
        // JUMP IF LOWER: caso L == 0, pule para o endereco de memoria MAR.
        if(l==1)
            pc =memoria[mar];

    }


    if(ir==jle){
    //JUMP IF LOWER OR EQUAL: caso L==1 ou E==1, pule para o endereco de memoria MAR.
        if(l==1 || e==1)
            pc = memoria[mar];

    }


    if(ir==jg){
        //JUMP IF GREATER: caso G == 1,pule para o endereco de memoria MAR.
        if(g==1)
            pc = memoria[mar];

    }


    if(ir==jge){
        //JUMP IF GREATER OR EQUAL: caso G==1 ou E==1, pule para o endereco de memoria MAR.
        if(g==1 || e ==1)
            pc = memoria[mar];

    }


    if(ir==jmp){
        // JUMP: pule para o endereco de memoria MAR.
        pc = memoria[mar];

    }


    if(ir==ld){
        //LOAD: Carregue o valor armazenado no endereco de memoria[mar] para o registrador[ro0].
        reg[ro0] = memoria[mar];

    }


    if(ir==st){
        //STORE: Armazene o valor do registrador[ro0] na posicao de memoria[mar].
        memoria[mar] = reg[ro0];

    }


    if(ir==movi){
        //MOVI: Mover o valor do registrador IMM para o reegistrador RO0.
        reg[ro0] = imm;

    }


    if(ir==addi){
        //ADDI: Somar o valor do re[ro0] com o valor do registrador IMM.
        reg[ro0] = reg[ro0] + imm;

    }


    if(ir==subi){
        //SUBI Subtrair o valor do reg[ro0] com o valor de registrador IMM.
        reg[ro0] = reg[ro0] - imm;

    }


    if(ir==multi){
        //MULT: Multiplica o valor de reh[ro0] com o valor de registrador IMM.
        reg[ro0] = reg[ro0]*imm;

    }


    if(ir==divi){
        //DIVI: Dividir o valor de reg[ro0] pelo valor de IMM
        reg[ro0] = reg[ro0]/imm;

    }


    if(ir==lsh){
        //LSH(LEFT SHIFT): Desloca o valor do reg[ro0] a IMM posicoes a esquerda.
        reg[ro0] = reg[ro0]<<imm;

    }


    if(ir==rsh){
        //RSH (RIGHT SHIFT): Desloca o valor de reg[ro0] a IMM posiceoes a direita.
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

    busca();
    printf("%x", mbr);
    decodifica();
    executa();


    printf("\n print reg[ro0]: %x", reg[ro0]);
    printf("\n print ro0:  %x", ro0);
    printf("\n print ir:  %x", ir);
    }
