#include "multi.h"
#include <algorithm>


int piso(double x){
	return (int) x;
}

std::string modulo(std::string x){
	if (x[0] == '-'){
		return x.substr(1, x.size()-1);
	}else{
		return x;
	}
}

char intToChar(int x){
	char result;
	if(x >= 0 && x <= 9){
		result = (char)(x + 48);
	}else if (x <= 35){
		result = (char)(x + 55);
	}
	return result;
}

int charToInt(char x){
	if ((int)x - 48 >= 0 && (int)x - 48 <= 9){
		return (int)x - 48;
	}else if((int)x <= 90){
		return (int)x - 55;
	}
}

/*
int x: o numero inteiro a ser convertido
int base: a base do numero inteiro x

return: uma string com o numero inteiro x escrito na base determinada
*/

std::string toBase(int x, int base){
	bool negative = (x < 0);
	if (negative){
		x = -x;
	}
	std::string result = "";
	std::string temp;
	int resto;
	while(x != 0){
		resto = x % base;
		result  = intToChar(resto) + result;
		x = x / base;
	}

	if(result == ""){
		result = "0";
	}
	if(negative){
		result = "-" + result;
	}
	return result;
}

std::string toBase(float x, int base){
	float frac = x - (int)x;
	std::string result = "";

	int count = 0;
	while(frac != 0 && count <= 8){
		frac = frac * base;
		result = result + intToChar((int)frac);
		if(frac >= 1){
			frac = frac - (int)frac;
		}
		count++;
	}

	if(result == ""){
		return toBase((int)x, base);
	}else{
		return toBase((int)x, base) + "." + result;
	}
}
	

float baseToBin(std::string x, int base){
	//point é a posição, na string, do ponto que separaria
	//a parte inteira da parte fracionaria do numero
	int point = 0;
	std::string parteInteira = "", parteFracionaria = "";
	int inteira = 0;
	float fracionaria = 0;

	//localiza o ponto
	for(int i = 0; i < x.size(); i++){
		if(x[i] == '.'){
			point = i;
			break;
		}
	}

	if(point == 0){
		parteInteira = x;
		reverseString(parteInteira);
		parteFracionaria = "0";
	}else{
		parteInteira = x.substr(0, point);
		reverseString(parteInteira);
		parteFracionaria = x.substr(point+1, x.size()-1);
	}

	//std::cout << x << "=" << parteInteira << "." << parteFracionaria[0] << "\n";

	for(int i = 0; i <= parteInteira.size()-1; i++){
		inteira += charToInt(parteInteira[i]) * potencia(base, i);
	}

	//std::cout << inteira << "\n";

	for(int i = 0; i <= parteFracionaria.size()-1; i++){
		fracionaria += charToInt(parteFracionaria[i]) * potencia(base, -i-1);
		//std::cout <<  "+=" << charToInt(parteFracionaria[i]) * potencia(base, -i-1) << "\n";
	}

	//std::cout << fracionaria << "\n";
	return inteira + fracionaria;
}

void reverseString(std::string &a){
	std::string aux = "";
	for(int i = a.size()-1; i >= 0; i--){
		aux += a[i];
	}
	a = aux;
}

float potencia(int x, int y){
	if(y < 0){
		return 1 / (potencia(x, -y));
	}else if(y == 0){
		return 1;
	}else{
		float result = x;
		for(int i = 1; i < y; i++){
			result = result*x;
		}
		return result;
	}
}

/*
std::string x: a sequencia de palavras separadas por ", " para ser processada

return: a ultima palavra da string x, sem conter virgula ou espaço
*/
std::string getLast(std::string x){
	int lastStart = 0;
	for (int i = 1; i < x.size(); i++){
		if(x[i-1] == ' '){
			lastStart = i;
		}
	}
	int tam = 0;
	for (int i = lastStart; i < x.size(); i++){
		if (x[i] != ' ' || x[i] != ','){
			tam++;
		}
	}

	return x.substr(lastStart, tam);
}

/*
std::string x: numero a ser incrementado (pode estar em qualquer base)
int base: base numerica

return: o numero x acrescido de +1;
*/
std::string plusOne(std::string x, int base){
	std::string result = "";
	if(x[0] == '-'){
		x = x.substr(1, x.size() - 1);
		int i = x.size()-1;
		while(charToInt(x[i]) == 0){
			i--;
			//como, neste caso, o numero sempre é menor que zero -> é impossivel haver apenas "0"s na string
		}

		for(int j = i+1; j < x.size(); j++){
			x[j] = intToChar(base-1);
		}

		x[i] = intToChar(charToInt(x[i]) - 1);

		while(x[0] == '0' && x.size() >= 1){
			x = x.substr(1, x.size() - 1);
		}

		if(x == ""){
			x = "0";
		}else{
			x = "-" + x;
		}
		result = x;
		
	}else{
		int i = x.size()-1;

		while(charToInt(x[i]) == base - 1){
			i--;
			if(i == -1){
				break;
			}
		}

		for(int j = i+1; j < x.size(); j++){
			x[j] = '0';
		}

		if(i >= 0){
			x[i] = intToChar(charToInt(x[i]) + 1);
		}else{
			x = "1" + x;
		}

		result = x;
	}
	return result;
}