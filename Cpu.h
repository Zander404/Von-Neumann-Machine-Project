// Função de manipulção de arquivo


//Codificação: tipo 1
#define hlt 0x00
#define nop 0x01

//Codificação: tipo 2
#define add 0x02
#define sub 0x03
#define mult 0x04
#define div 0x05
#define cmp 0x06
#define movr 0x07
#define and 0x08
#define or 0x09
#define xor 0xa

//Codificação: tipo 3
#define not 0xb

//Codificação: tipo 4
#define je 0xc
#define jne 0xd
#define jl 0xe
#define jle 0xf
#define jg 0x10
#define jge 0x11
#define jmp 0x12

//Codificação: tipo 5
#define ld 0x13
#define st 0x14

//Codificação: tipo 6
#define movi 0x15
#define addi 0x16
#define subi 0x17
#define multi 0x18
#define divi 0x19
#define lsh 0x1a
#define rsh 0x1b



//Mascaras para a coleta de dados da memoria
#define mask0 0x00e00000 //pegar o Ro0
#define mask1 0x001c0000 //pegar o Ro1
#define maskendereco 0x0003ffff //pegar o endereco


//Registradores
#define r0 reg[000]
#define r1 reg[001]
#define r2 reg[010]
#define r3 reg[011]
#define r4 reg[100]
#define r5 reg[101]
#define r6 reg[110]
#define r7 reg[111]



//0x0     0   0     3  f     f    f    f
//0      0   0     11 1111 1111 1111 1111
