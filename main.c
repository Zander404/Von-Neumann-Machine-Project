#include <stdio.h>
#include <stdlib.h>
#include "Cpu.h"
#include <string.h>

//Variavéis para a CPU

unsigned char memoria[154];//  8 bits 0000 0000
unsigned int mbr;          // 32 bits
unsigned int mar=0;          // 32 bits, mas precisa apenas de 21
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
    for (int i = 1; i<4; i++){
        mbr = (mbr << 8) | memoria[mar++];
    }
}


void decodifica(){
    ir = mbr >> 24;

    if( ir >= 0x02 && ir <=0xa ) {
        //formato de funcoes basicas de matematicas
        ro0 = (mbr&mask0)>>21;
        ro1 = (mbr&mask1)>>18;

    }

    if(ir == 0xb ){
        // formato para o commando do tipopalavra NOT
        ro0 = (mbr&mask0)>>21;
    }

    if(ir >= 0xc && ir<=0x12){
        // formato de funcao jump
        mar = mbr & maskendereco;
    }

    if(ir>=0x13 && ir<=0x14){
        //formato para a funcao store e load
        ro0 = (mbr&mask0)>>21;
        mar = (mbr&maskendereco);
    }
    if(ir>=0x15 && ir<= 0x1b){
        //formato para a funcao movi, addi, subi

        ro0 = (mbr&mask0)>>21;
        imm = (mbr&maskendereco);

    }
}


void executa() {

    if (ir == hlt) {
        //Parar a execucao do programa
    }


    if (ir == nop) {
        //Pegar o proximo conjunto de instrucoes
        pc += 4;
    }


    if (ir == add) {
        //Somar o valor de reg[r0] do valor de reg[ro1]

        reg[ro0] = reg[ro0] + reg[ro1];
        pc += 4;
    }


    if (ir == sub) {
        //Subtrair o valor de reg[r0] do valor de reg[ro1]
        reg[ro0] = reg[ro0] - reg[ro1];
        pc += 4;
    }


    if (ir == mul) {
        //Multiplicar o valor de reg[r0] do valor de reg[ro1]
        reg[ro0] = reg[ro0] * reg[ro1];
        pc += 4;
    }


    if (ir == div) {
        //Dividir o valor de reg[r0] do valor de reg[ro1]
        reg[ro0] = reg[ro0] / reg[ro1];
        pc += 4;
    }


    if (ir == cmp) {
        //Comparar o valor de reg[r0] do valor de reg[ro1]
        if (ro0 == ro1) {
            e = 1;
            l = 0;
            g = 0;
        }
        if (ro0 < ro1) {
            e = 0;
            l = 1;
            g = 0;
        }
        if (ro0 > ro1) {
            e = 0;
            l = 0;
            g = 0;
        }
        pc += 4;
    }

    if (ir == movr) {
        //Mover o valor do reg[ro0] para o reg[ro1]
        reg[ro0] = reg[ro1];
        pc += 4;
    }


    if (ir == and) {
        //Fazer a comparação logica AND entre o registrador ro0 e ro1, e por fim armazenar o resultado em ro0
        reg[ro0] = reg[ro0] & reg[ro1];
        pc += 4;
    }


    if (ir == or) {
        //Fazer a comparação LOGICA OR entre os registradores ro0 e ro1, e por fim armazenar o resultado em ro0
        reg[ro0] = reg[ro0] | reg[ro1];
        pc += 4;

    }


    if (ir == xor) {
        //Fazer a comparacao LOGICA XOR( Ou Exclusivo), onde armazenara o resultado no ro0
        reg[ro0] = reg[ro0] ^ reg[ro1];
        pc += 4;
    }


    if (ir == not) {
        //Altera o valor atual do registrador ro0 pelo seu inverso
        reg[ro0] = !reg[ro0];
        pc += 4;

    }


    if (ir == je) {
        //JUMP IF EQUAL:pula para um enderço de memoria, caso executa o valor de E seja igual a 1.
        if (e == 1) {
            pc = mar;
        } else {
            pc += 4;
        }

    }


    if (ir == jne) {
        //JUMP NOT EQUAL: caso o valor de e==0, pule para o endereco de memoria do MAR.
        if (e == 0) {
            pc = mar;
        } else {
            pc += 4;
        }

    }


    if (ir == jl) {
        // JUMP IF LOWER: caso L == 0, pule para o endereco de memoria MAR.
        if (l == 1) {
            pc = mar;

        } else {
            pc += 4;
        }
    }


    if (ir == jle) {
        //JUMP IF LOWER OR EQUAL: caso L==1 ou E==1, pule para o endereco de memoria MAR.
        if (l == 1 || e == 1) {
            pc = mar;
        } else {
            pc += 4;
        }
    }


    if (ir == jg) {
        //JUMP IF GREATER: caso G == 1,pule para o endereco de memoria MAR.
        if (g == 1) {
            pc = mar;
        } else {
            pc += 4;
        }
    }


    if (ir == jge) {
        //JUMP IF GREATER OR EQUAL: caso G==1 ou E==1, pule para o endereco de memoria MAR.
        if (g == 1 || e == 1) {
            pc = mar;
        } else {
            pc += 4;
        }
    }


    if (ir == jmp) {
        // JUMP: pule para o endereco de memoria MAR.
        pc = mar;

    }


    if (ir == ld) {
        //LOAD: Carregue o valor armazenado no endereco de memoria[mar] para o registrador[ro0].
        mbr = memoria[mar++];
        for (int i = 1; i < 4; i++) {
            mbr = (mbr << 8) | memoria[mar++];
        }
        reg[ro0] = mbr;
        pc += 4;

    }


    if (ir == st) {
        //STORE: Armazene o valor do registrador[ro0] na posicao de memoria[mar].
        mbr = reg[ro0];
        memoria[mar++] = mbr >> 24;
        memoria[mar++] = (mbr & 0x00ff0000) >> 16;
        memoria[mar++] = (mbr & 0x0000ff00) >> 16;
        memoria[mar] = (mbr & 0x000000ff);
        pc += 4;

    }


    if (ir == movi) {
        //MOVI: Mover o valor do registrador IMM para o reegistrador RO0.
        reg[ro0] = imm;
        pc += 4;
    }


    if (ir == addi) {
        //ADDI: Somar o valor do re[ro0] com o valor do registrador IMM.
        reg[ro0] = reg[ro0] + imm;
        pc += 4;

    }


    if (ir == subi) {
        //SUBI Subtrair o valor do reg[ro0] com o valor de registrador IMM.
        reg[ro0] = reg[ro0] - imm;
        pc += 4;
    }


    if (ir == muli) {
        //MULT: Multiplica o valor de reh[ro0] com o valor de registrador IMM.
        reg[ro0] = reg[ro0] * imm;
        pc += 4;
    }


    if (ir == divi) {
        //DIVI: Dividir o valor de reg[ro0] pelo valor de IMM
        reg[ro0] = reg[ro0] / imm;
        pc += 4;
    }


    if (ir == lsh) {
        //LSH(LEFT SHIFT): Desloca o valor do reg[ro0] a IMM posicoes a esquerda.
        reg[ro0] = reg[ro0] << imm;
        pc += 4;
    }


    if (ir == rsh) {
        //RSH (RIGHT SHIFT): Desloca o valor de reg[ro0] a IMM posiceoes a direita.
        reg[ro0] = reg[ro0] >> imm;
        pc += 4;
    }

}

unsigned int setPalavra(char opc[], unsigned int reg0, unsigned int reg1, unsigned int memOuImediate, int i) {
    unsigned int text;
// Traduzir as instrucoes para hexadecimal



    if (strcmp(opc, "ld") == 0) {
        text = 0x13; //
        text = (text << 3) | reg0;
        text = (text << 21) | memOuImediate;


    } else if (strcmp(opc, "st") == 0) {
        text = 0x14;
        text = (text << 3) | reg0;
        text = (text << 21) | memOuImediate;


    } else if (strcmp(opc, "add") == 0) {
        text = 0x02;
        text = (text << 3) | reg0;
        text = (text << 3) | reg1;
        text = text << 18;


    } else if (strcmp(opc, "sub") == 0) {
        text = 0x03;
        text = (text << 3) | reg0;
        text = (text << 3) | reg1;
        text = text << 18;


    } else if (strcmp(opc, "mul") == 0) {
        text = 0x04;
        text = (text << 3) | reg0;
        text = (text << 3) | reg1;
        text = text << 18;


    } else if (strcmp(opc, "div") == 0) {
        text = 0x05;
        text = (text << 3) | reg0;
        text = (text << 3) | reg1;
        text = text << 18;


    } else if (strcmp(opc, "cmp") == 0) {
        text = 0x06;
        text = (text << 3) | reg0;
        text = (text << 3) | reg1;
        text = text << 18;


    } else if (strcmp(opc, "movr") == 0) {
        text = 0x07;
        text = (text << 3) | reg0;
        text = (text << 3) | reg1;
        text = text << 18;


    } else if (strcmp(opc, "and") == 0) {
        text = 0x08;
        text = (text << 3) | reg0;
        text = (text << 3) | reg1;
        text = text << 18;


    } else if (strcmp(opc, "or") == 0) {
        text = 0x09;
        text = (text << 3) | reg0;
        text = (text << 3) | reg1;
        text = text << 18;


    } else if (strcmp(opc, "xor") == 0) {
        text = 0x0A;
        text = (text << 3) | ro0;
        text = (text << 3) | text;
        text = text << 18;


    } else if (strcmp(opc, "not") == 0) {
        text = 0x0B;
        text = (text << 3) | ro0;
        text = text << 21;


    } else if (strcmp(opc, "je") == 0) {
        text = 0x0C;
        text = (text << 24) | memOuImediate;


    } else if (strcmp(opc, "jne") == 0) {
        text = 0x0D;
        text = (text << 24) | memOuImediate;


    } else if (strcmp(opc, "jl") == 0) {
        text = 0x0E;
        text = (text << 24) | memOuImediate;


    } else if (strcmp(opc, "jg") == 0) {
        text = 0x0F;
        text = (text << 24) | memOuImediate;


    } else if (strcmp(opc, "jle") == 0) {
        text = 0x10;
        text = (text << 24) | memOuImediate;


    } else if (strcmp(opc, "jge") == 0) {
        text = 0x11;
        text = (text << 24) | memOuImediate;


    }else if (strcmp(opc, "jmp") == 0) {
        text = 0x12;
        text = (text << 24) | memOuImediate;


    } else if (strcmp(opc, "movi") == 0) {
        text = 0x15;
        text = (text << 3) | reg0;
        text = (text << 21) | memOuImediate;


    } else if (strcmp(opc, "addi") == 0) {
        text = 0x16;
        text = (text << 3) | reg0;
        text = (text << 21) | memOuImediate;


    } else if (strcmp(opc, "subi") == 0) {
        text = 0x17;
        text = (text << 3) | reg0;
        text = (text << 21) | memOuImediate;


    } else if (strcmp(opc, "muli") == 0) {
        text = 0x18;
        text = (text << 3) | reg0;
        text = (text << 21) | memOuImediate;


    } else if (strcmp(opc, "divi") == 0) {
        text = 0x19;
        text = (text << 3) | reg0;
        text = (text << 21) | memOuImediate;


    }
    else if (strcmp(opc, "lsh") == 0) {
        text = 0x1A;
        text = (text << 3) | reg0;
        text = (text << 21) | memOuImediate;


    }
    else if (strcmp(opc, "rsh") == 0) {
        text = 0x1B;
        text = (text << 3) | reg0;
        text = (text << 21) | memOuImediate;


    }
    else if (strcmp(opc, "nop") == 0) {
        text = 0x01;
        text = text << 24;


    }else {
        text = 0;
    }

    printf("%x\n", text);
    memoria[i++] = text >> 24;
    memoria[i++] = (text & 0x00ff0000) >> 16;
    memoria[i++] = (text & 0x0000ff00) >> 16;
    memoria[i] = text & 0x000000ff;

    return text;
}


void lerTexto()
{
    FILE *arq;
    char *pt;
    char texto[50];
    char opc[10];
    int count = 0;

    int inicio;
    char tipopalavra;
    unsigned int palavra;
    unsigned int reg0;
    unsigned int reg1;
    unsigned int memOuImm;

    arq = fopen("arquivo.txt", "r");

    if (NULL == arq) {
        printf("Arquivo programa.txt nao encontrado \n");
    } else{
        while (fgets(texto, 50, arq) != NULL) {
            pt = strtok(texto, ";");
            while(count < 3)
            {
                if(count == 0)
                {
                    //inicio
                    inicio = (int) strtol(pt,NULL,16);
                } else if(count == 1)
                {
                    //tipopalavra
                    tipopalavra = *pt;
                } else{
                    if(tipopalavra == 'i')
                    {
                        pt = strtok(pt,", ");
                        if(strcmp(pt, "add") == 0 || strcmp(pt, "sub") == 0 ||
                           strcmp(pt, "mul") == 0 || strcmp(pt, "div") == 0 ||
                           strcmp(pt, "cmp") == 0 || strcmp(pt, "movr") == 0 ||
                           strcmp(pt, "and") == 0 || strcmp(pt, "or") == 0 ||
                           strcmp(pt, "xor") == 0){ //decodificacao tipo 2
                            strcpy(opc,pt); //copiar o ponteiro para o opcode

                            pt = strtok(NULL,"r, "); //pegar o ro0
                            reg0 = (int) strtol(pt, NULL, 16);

                            pt = strtok(NULL,"r, "); //pegar o ro1
                            reg1 = (int) strtol(pt, NULL, 16);

                            setPalavra(opc,reg0,reg1,0,inicio); //criar a instrucao

                        } else if(strcmp(pt, "not") == 0){
                            strcpy(opc,pt); //copiar o ponteiro para o opcode

                            pt = strtok(NULL,"r, ");
                            reg0 = (int) strtol(pt, NULL, 16);
                            setPalavra(opc,reg0,0x0,0x0,inicio);
                        } else if(strcmp(pt, "je") == 0 || strcmp(pt, "jne") == 0 ||
                                  strcmp(pt, "jl") == 0 || strcmp(pt, "jle") == 0 ||
                                  strcmp(pt, "jg") == 0 || strcmp(pt, "jge") == 0 ||
                                  strcmp(pt, "jmp") == 0){

                            strcpy(opc,pt); //copia o ponteiro para o opcode

                            pt = strtok(NULL,", "); //pega o endereco de memoria
                            memOuImm = (int) strtol(pt, NULL, 16);

                            palavra = setPalavra(opc,0x00,0x00,memOuImm,inicio);
                        } else if(strcmp(pt, "ld") == 0 || strcmp(pt,"st") == 0)
                        {
                            //Mnemônico
                            strcpy(opc,pt); //copiar o ponteiro para o opcode
                            pt = strtok(NULL, "r, "); //pega o ro0
                            reg0 = (int) strtol(pt,NULL,16);
                            pt = strtok(NULL, ", "); //pega o endereco de memoria
                            memOuImm = (int) strtol(pt, NULL, 16);

                            palavra = setPalavra(opc,reg0,0x00,memOuImm,inicio);

                        }else if(strcmp(pt, "addi") == 0 || strcmp(pt, "subi") == 0 ||
                                 strcmp(pt, "muli") == 0 || strcmp(pt, "divi") == 0 ||
                                 strcmp(pt, "movi") == 0 ||strcmp(pt, "lsh") == 0 ||
                                 strcmp(pt, "rsh") == 0)
                        { // decodificacao tipo 6
                            strcpy(opc, pt); //copia o ponteiro para o opcode
                            pt = strtok(NULL,"r, ");
                            reg0 = (int) strtol(pt, NULL, 16);

                            pt = strtok(NULL,"r, "); //posicao da memoria
                            memOuImm = (int) strtol(pt,NULL,16);

                            palavra = setPalavra(opc,reg0,0x00,memOuImm,inicio);
                        }else if(strcmp(pt, "nop") == 0 || strcmp(pt, "hlt") == 0){ //decodificacao tipopalavra 1
                            strcpy(opc,pt);
                            palavra = setPalavra(opc,0x00,0x00,0x00,inicio);
                        }
                    } else{
                        palavra = (int) strtol(pt,NULL,16);
                        memoria[inicio++] = palavra >> 24;
                        memoria[inicio++] = (palavra & 0x00ff0000) >> 16;
                        memoria[inicio++] = (palavra & 0x0000ff00) >> 16;
                        memoria[inicio] = palavra & 0x000000ff;
                    }
                }
                pt = strtok(NULL,";");
                count++;
            }
            count = 0;
        }
    }
    fclose(arq);
}



    int main() {
//    memoria[0] = 0x13; //0001 0010 OP
//    memoria[1] = 0x40; //0100 0000 RO0 e RO1
//    memoria[2] = 0x00; //0000 0001
//    memoria[3] = 0x00; //0001 1101
//    memoria[4] = 0x16; //0001 0110
//    memoria[5] = 0x0;  //0000 0000
//    memoria[6] = 0x0;  //0000 0000
//    memoria[7] = 0x14; //0001 0100
//    memoria[30] = 0x0; //0000 0000
//    memoria[31] = 0x0; //0000 0000
//    memoria[32] = 0x0; //0000 0000
//    memoria[33] = 0xf; //0000 1111

        lerTexto();

        busca();
        decodifica();


        while (ir != hlt) {
            executa();
            busca();
            decodifica();

        }
        printf("\n Resultado: ");
        printf("\n %d", memoria[0x85]);

        return 0;
    }
