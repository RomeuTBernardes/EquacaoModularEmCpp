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

double provaReal(Token lista[], double b)
{
	int k = 0;
	double coeficiente;
	double resultado = 0;

	while(lista[k].ladoEsquerdo)
	{
		if(lista[k].eVariavel) coeficiente = b;
		else coeficiente = stod(lista[k].tok);
			
		if(!lista[k].positivo) coeficiente *= -1;
		
		if(lista[k].dividindo || lista[k].multiplicando) 
		{
			k++;
			while(lista[k].dividindo || lista[k].multiplicando)
			{
				if(lista[k].multiplicando)
				{	
					if(lista[k].eVariavel) coeficiente *= b;
					else coeficiente *= stod(lista[k].tok);
				}

				else
				{
					if(lista[k].eVariavel) coeficiente /= b;
					else coeficiente /= stod(lista[k].tok);
				}

				if(!lista[k].positivo) coeficiente *= -1;
				
				k++;
			}
			k--;
		}
	
		resultado += coeficiente;
		
		k++;
	}

	return resultado;
}

int main()
{
	double b = 0;
	double bNeg; 
	double coeficiente;
	double divisorA = 0;
	double divisorB = 0;
	double multiplicadorA = 0;
	double multiplicadorB = 0;

	string in;

	Token lista[50];
	int indexLista = 0;

	cout << "Digite a equação modular: " << endl;
	getline(cin, in);

	char variavel = ' ';

	bool divisorAtivado = false;
	bool multiplicadorAtivado = false;
	bool modulo = false;
	bool esquerdoAtual = true;

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
			continue;
		}

		else if(in[i] ==  '-')
		{
			lista[indexLista].positivo = false;
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
		
		else if(!isdigit(in[i]) && !isalpha(in[i]))
		{
			cout << "ERRO: caractere (" << in[i] << ") inválido!" << endl;
			return 1;
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
			if(in[i] != variavel && variavel != ' ')
			{
				cout << "ERRO: este programa aceita apenas uma variável!" << endl;
				return 1;
			}

			variavel = in[i];
			lista[indexLista].eVariavel = true;
		}

		lista[indexLista].ladoEsquerdo = esquerdoAtual;
		lista[indexLista].dentroModulo = modulo;

		indexLista++;
	}

	if(esquerdoAtual)
	{
		cout << "ERRO: não existe lado B na equação" << endl;
		return 1;
	}

	// isolando modulo
	for(int i = 0; i < indexLista; i++)
	{
		if(!divisorAtivado && lista[i].multiplicando) divisorAtivado = true;
		if(!multiplicadorAtivado && lista[i].dividindo) multiplicadorAtivado = true;

		if(lista[i].ladoEsquerdo && !lista[i].dentroModulo)
		{
			lista[i].positivo = !lista[i].positivo;
			lista[i].ladoEsquerdo = false;
		}

		if(!lista[i].ladoEsquerdo && !lista[i].eVariavel && !lista[i].multiplicando && !lista[i].dividindo)
		{
			coeficiente = stod(lista[i].tok);
			if(!lista[i].positivo) coeficiente *= -1;
			b += coeficiente;
		}
	}

	double ladoDireito = b;

	bNeg = b * -1;

	for(int i = 0; i < indexLista; i++)
	{
		if(lista[i].ladoEsquerdo)
		{
			if(!lista[i].eVariavel && !lista[i].multiplicando && !lista[i].dividindo)
			{
				coeficiente = stod(lista[i].tok);
				if(lista[i].positivo) b -= coeficiente;
				else b += coeficiente;
				if(lista[i].positivo) bNeg -= coeficiente;
				else bNeg += coeficiente;
			}
			
			else if(lista[i].eVariavel && !lista[i].multiplicando && !lista[i].dividindo)
			{
				if(lista[i].positivo) divisorA++;
				else divisorA--;
			}

			else if(lista[i].multiplicando && !lista[i].eVariavel)
			{
				coeficiente = stod(lista[i].tok);
				if(!lista[i].positivo) coeficiente *= -1;
				divisorA += coeficiente;
			}

			else if(lista[i].dividindo && !lista[i].eVariavel)
			{
				coeficiente = stod(lista[i].tok);
				if(!lista[i].positivo) coeficiente *= -1;
				multiplicadorA += 1/coeficiente;
			}
		}

		else
		{
			if(lista[i].multiplicando && !lista[i].eVariavel)
			{
				coeficiente = stod(lista[i].tok);
				if(!lista[i].positivo) coeficiente *= -1; 
				divisorB += coeficiente;
			}

			else if(lista[i].eVariavel && !lista[i].multiplicando && !lista[i].dividindo)
			{
				if(lista[i].positivo) divisorB++;
				else divisorB--;
			}

			else if(lista[i].dividindo && !lista[i].eVariavel)
			{
				coeficiente = stod(lista[i].tok);
				if(!lista[i].positivo) coeficiente *= -1;
				multiplicadorB += 1/coeficiente;
			}
		}
	}
	
	// evitando divisão por zero
	if(!divisorAtivado && !multiplicadorAtivado) divisorA = 1;

	if(divisorA - divisorB  + multiplicadorA - multiplicadorB == 0)
	{
		cout << "ERRO: variável zerada" << endl;
		return 1;
	}

	b = b/(divisorA - divisorB + multiplicadorA - multiplicadorB);

	bNeg = bNeg/(divisorA + divisorB + multiplicadorA + multiplicadorB);

	double prova1 = provaReal(lista, b);
	double prova2 = provaReal(lista, bNeg);

	bool temRaiz = false;
	
	cout << endl;

	if((prova1 >= 0 && prova1 == ladoDireito) || (prova1 < 0 && -prova1 == ladoDireito)) 
	{
		cout << variavel << " = " << b << endl;
		temRaiz = true;
	}

	if(((prova2 >= 0 && prova2 == ladoDireito) || (prova2 < 0 && -prova2 == ladoDireito)) && ladoDireito != 0) 
	{
		cout << variavel << " = " << bNeg << endl;
		temRaiz = true;
	}

	if(!temRaiz) cout << "A equação não possui raizes reais" << endl;

	return 0;
}
