#ifndef MULTI
#define MULTI

#include <iostream>
#include <string>

int piso(double x);

std::string modulo(std::string x);

char intToChar(int x);

int charToInt(char x);

/*
int x: o numero inteiro a ser convertido
int base: a base do numero inteiro x

return: uma string com o numero inteiro x escrito na base determinada
*/
std::string toBase(int x, int base);

std::string toBase(float x, int base);

float baseToBin(std::string x, int base);

float potencia(int x, int y);
void reverseString(std::string &a);
/*
std::string x: a sequencia de palavras separadas por ", " para ser processada

return: a ultima palavra da string x, sem conter virgula ou espaço
*/
std::string getLast(std::string x);

/*
std::string x: numero a ser incrementado
int base: base numerica

return: o numero x acrescido de +1;
*/
std::string plusOne(std::string x, int base);

#endif