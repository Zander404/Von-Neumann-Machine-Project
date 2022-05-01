//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
////
////int main(){
////
////    FILE *pf;
////    char str[100];
////    char *result;
////    if((pf = fopen("arquivo.txt","r")) == NULL){
////        printf("\n Arquivo Invalido / Ou nao existente ");
////        exit(1);
////
////    }
////    while (!feof(pf)){
////        result = fgets(str, 100, pf);
////        if(result) printf(" - %s", str);
////
////    }
////    fclose(pf);
////
////}
//
//int main() {
//    char palavra[50] = {"38;i;ld r1, 82"};
//    char *pt;
//    int count = 0;
//    int tipoPalavra;
//
//    int endInicio;
//    int opc;
//    int reg1;
//    int reg2;
//    int endMemOuImediate;
//    int dado, dado1;
//
//    pt = strtok(palavra, ";");
//    while (count < 3) {
//        printf("token: %s \n", pt);
//        if (count == 0) {
//            endInicio = (int) strtol(pt, NULL, 16);
//            printf("%s  -- ", pt);
//            printf("%i -- %x", endInicio, endInicio);
//        } else if (count == 1) {
//            tipoPalavra = (*pt == "i") ? 1 : 0;
//            printf("%i -- %x\n ", dado, dado1);
//        }
//        else{
//            if(tipoPalavra == 0){
//                palavra = (int) strtol(pt, NULL, 16);
//                printf("%i -- %x \n ");
//            }
//
//
//
//
//        //instrucao
//        }
//    }
//}