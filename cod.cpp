#include <stdio.h>
#include <string>
#include <iostream>
#include <cctype>

using namespace std;

typedef struct
{
	string tok;
	bool ladoEsquerdo;
	bool dentroModulo;
	bool positivo;
	bool multiplicando = false;
	bool eVariavel = false;
	bool dividindo = false;
} Token;

int main()
{
	double b = 0;
	double bNeg; 
	int coeficiente;
	int divisor = 1;
	int multiplicador = 1;
	string in;

	Token lista[50];
	int indexLista = 0;

	cout << "Digite a equação modular: " << endl;
	getline(cin, in);

	bool modulo = false;

	char variavel;
	bool esquerdoAtual = true;
	bool proximoPositivo = true;
	bool multAtual = false;

	for(int i = 0; i < in.length(); i++)
	{
		if(in[i] == '|')
		{
			modulo = !modulo;				
			continue;
		}

		if(in[i] == '=')
		{
			esquerdoAtual = !esquerdoAtual;
			continue;
		}
		
		if(in[i] == '+' or in[i] == ' ') 
		{
			proximoPositivo = true;
			continue;
		}

		if(in[i] ==  '-')
		{
			proximoPositivo = false;
			if(in[i + 1] == ' ') i++;
			continue;
		}

		if(in[i] == '*')
		{
			lista[indexLista - 1].multiplicando = true;
			lista[indexLista].multiplicando = true;
			if(in[i + 1] == ' ') i++;
			continue;
				
		}

		if(in[i] == '/')
		{
			lista[indexLista - 1].dividindo = true;
			lista[indexLista].dividindo = true;
			if(in[i + 1] == ' ') i++;
			continue;
		}

		lista[indexLista].tok = in[i];

		if(isdigit(in[i]))
		{
			i++;
			while(isdigit(in[i]))
			{
				lista[indexLista].tok += in[i];
				i++;
			}
			i--;
		}
		
		else if(isalpha(in[i]))
		{
			variavel = in[i];
			lista[indexLista].eVariavel = true;
		}

		lista[indexLista].ladoEsquerdo = esquerdoAtual;
		lista[indexLista].dentroModulo = modulo;
		lista[indexLista].positivo = proximoPositivo;

		indexLista++;
	}

	// isolando modulo
	for(int i = 0; i < indexLista; i++)
	{
		if(lista[i].ladoEsquerdo && !lista[i].dentroModulo)
		{
			lista[i].positivo = !lista[i].positivo;
			lista[i].ladoEsquerdo = false;
		}

		if(!lista[i].ladoEsquerdo)
		{
			coeficiente = stoi(lista[i].tok);
			if(!lista[i].positivo) coeficiente *= -1;

			b += coeficiente;
		}
	}

	bNeg = b * -1;
	
	for(int i = 0; i < indexLista; i++)
	{
		if(lista[i].ladoEsquerdo && !lista[i].eVariavel && !lista[i].multiplicando && !lista[i].dividindo)
		{
			coeficiente = stoi(lista[i].tok);
			if(lista[i].positivo) b -= coeficiente;
			else b += coeficiente;
			if(lista[i].positivo) bNeg -= coeficiente;
			else bNeg += coeficiente;
		}

		if(lista[i].multiplicando && lista[i].ladoEsquerdo && !lista[i].eVariavel)
		{
			coeficiente = stoi(lista[i].tok);
			if(!lista[i].positivo) coeficiente *= -1;
			divisor *= coeficiente;
		}

		if(lista[i].dividindo && lista[i].ladoEsquerdo && !lista[i].eVariavel)
		{
			coeficiente = stoi(lista[i].tok);
			if(!lista[i].positivo) coeficiente *= -1;
			multiplicador *= coeficiente;
		}
	}

	b = (b/divisor)*multiplicador;

	bNeg = (bNeg/divisor)*multiplicador;

	cout << "\nResultado de " << variavel << " para A = B: " << b << endl;
	cout << "Resultado de " << variavel << " para A = -B: " << bNeg << endl;

	return 0;
}
