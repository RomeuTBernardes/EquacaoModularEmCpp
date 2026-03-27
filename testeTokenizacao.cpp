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
} Token;

int main()
{
	string in = "|-2 * x - 1| + 2 = 7";

	Token lista[50];
	int indexLista = 0;

	//cin >> in;

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

	for(int i = 0; i < indexLista; i++)
	{
		cout << lista[i].tok << " Positivo: " << lista[i].positivo << " Lado: " << lista[i].ladoEsquerdo << " Modulo: " << lista[i].dentroModulo << " Multiplicando: " << lista[i].multiplicando << " Variavel: " << lista[i].eVariavel << endl;
	}

	return 0;
}
