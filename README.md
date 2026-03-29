# Resolução de equação modular em C++
Programa em C++ que resolve equações modulares (|A| = B) simples escritas diretamente no terminal. Realizado como um pequeno exercício de tratamento de string e matemática.

O programa principal que deve ser compilado para uso é "cod.cpp". O outro código é usado para testes.

Por enquanto, o programa apenas resolve equações que: 
    
- Possuem uma variável apenas;
- Não realizam potenciação;
- Possuem duas raízes reais (por enquanto não há checagem de condição);
- Realizam multiplicação e divisão apenas na variável.

Padrões de input:

- Multiplicação pode ser indicada explicitamente com '*' ("2 * x") ou apenas colocando a variável ao lado do coeficiente ("2x");
- Parte "A" (parte com módulo) da equação sempre do lado esquerdo;
- Nunca mais de um espaço separando caracteres;
- '|' para abrir e fechar o módulo.

Exemplo de input/output:

in: 

|-4x + 3| - 5 = 10

out: 

Resultado de x para A = B: -3

Resultado de x para A = -B: 4.5
