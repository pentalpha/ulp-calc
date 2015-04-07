#include <iostream>      
#include <math.h>
#include <fstream>
#include <string>
#include "multi.h"
#include "ulp-calc.h"

int main (int argc, char **argv)
{   
    if(argc == 1){
        std::cout << "insira 'ulp-demo x' para gerar graficos\n";
        std::cout << "ou 'ulp-demo x y' para calcular o ulp de y\n";
    }else{
        //converte a mantissa (x) de const char* para int
        //pressumindo que esteja escrita na base 10
        int mant = baseToBin(argv[1], 10);
        if(argc == 2){ //./ulp-demo x
            //monta os graficos
            exponentialGraph(mant);
            linearGraph(mant);
            trueGraph(mant);
            //relativePrecisionGraph(mant);
        }else if(argc == 3){// ./ulp-demo x y
            //converte o valor (y) de const char* para int
            //pressumindo que esteja escrito na base 10
            int x = baseToBin(modulo(argv[2]), 10);
            
            std::cout << "Mantissa: " << mant << "\n";
            std::cout << "Valor: " << x << "\n";
            std::cout << "ULP: " << ulp(mant, x) << "\n";
        }
    }
    
    return 0;
}