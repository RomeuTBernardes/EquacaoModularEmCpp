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
	bool positivo = true;
	bool multiplicando = false;
	bool eVariavel = false;
	bool dividindo = false;
} Token;

int main()
{
	double b = 0;
	double bNeg; 
	int coeficiente;
	int divisorA = 0;
	int divisorB = 0;
	int multiplicadorA = 1;
	int multiplicadorB;

	string in;

	Token lista[50];
	int indexLista = 0;

	cout << "Digite a equação modular: " << endl;
	getline(cin, in);

	char variavel;

	bool modulo = false;
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

		else if(in[i] == '=')
		{
			esquerdoAtual = false;
			continue;
		}
		
		else if(in[i] == '+' or in[i] == ' ') 
		{
			proximoPositivo = true;
			continue;
		}

		else if(in[i] ==  '-')
		{
			proximoPositivo = false;
			if(in[i + 1] == ' ') i++;
			continue;
		}

		else if(in[i] == '*')
		{
			lista[indexLista - 1].multiplicando = true;
			lista[indexLista].multiplicando = true;
			if(in[i + 1] == ' ') i++;
			continue;
				
		}

		else if(in[i] == '/')
		{
			lista[indexLista - 1].dividindo = true;
			lista[indexLista].dividindo = true;
			if(in[i + 1] == ' ') i++;
			continue;
		}

		else if(isdigit(in[i]) && isalpha(in[i + 1]))
		{
			lista[indexLista].multiplicando = true;
			lista[indexLista + 1].multiplicando = true;
		}


		else if(isdigit(in[i]))
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

		else
		{
			cout << "ERRO: caractere (" << in[i] << ") inválido!" << endl;
			return 1;
		}
			
		lista[indexLista].tok = in[i];
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

		if(!lista[i].ladoEsquerdo && !lista[i].eVariavel && !lista[i].multiplicando)
		{
			coeficiente = stoi(lista[i].tok);
			if(!lista[i].positivo) coeficiente *= -1;
			b += coeficiente;
		}
	}

	bNeg = b * -1;
	
	for(int i = 0; i < indexLista; i++)
	{
		if(lista[i].ladoEsquerdo)
		{
			if(!lista[i].eVariavel && !lista[i].multiplicando && !lista[i].dividindo)
			{
				coeficiente = stoi(lista[i].tok);
				if(lista[i].positivo) b -= coeficiente;
				else b += coeficiente;
				if(lista[i].positivo) bNeg -= coeficiente;
				else bNeg += coeficiente;
			}
			
			else if(lista[i].eVariavel && !lista[i].multiplicando)
			{
				if(lista[i].positivo) divisorA++;
				else divisorA--;
			}

			else if(lista[i].multiplicando && !lista[i].eVariavel)
			{
				coeficiente = stoi(lista[i].tok);
				if(!lista[i].positivo) coeficiente *= -1;
				divisorA += coeficiente;
			}

			else if(lista[i].dividindo && !lista[i].eVariavel)
			{
				coeficiente = stoi(lista[i].tok);
				if(!lista[i].positivo) coeficiente *= -1;
				multiplicadorA *= coeficiente;
			}
		}

		else
		{
			if(lista[i].multiplicando && !lista[i].eVariavel)
			{
				coeficiente = stoi(lista[i].tok);
				if(!lista[i].positivo) coeficiente *= -1; 
				divisorB += coeficiente;
			}

			else if(lista[i].eVariavel && !lista[i].multiplicando)
			{
				if(lista[i].positivo) divisorB++;
				else divisorB--;
			}
		}
	}
	
	if(divisorA - divisorB == 0)
	{
		cout << "ERRO: variável zerada" << endl;
		return 1;
	}

	b = (b/(divisorA - divisorB))*multiplicadorA;

	bNeg = (bNeg/(divisorA + divisorB))*multiplicadorA;

	cout << "\nResultado de " << variavel << " para A = B: " << b << endl;
	cout << "Resultado de " << variavel << " para A = -B: " << bNeg << endl;

	return 0;
}
