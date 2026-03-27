# Resolução de equação modular em C++
Programa em C++ que resolve equações modulares (|A| = B) simples escritas diretamente no terminal. Realizado como um pequeno exercício de tratamento de string e matemática.

O programa principal que deve ser compilado para uso é "cod.cpp". O outro código é usado para testes.

Por enquanto, o programa apenas resolve equações que: 
    
- Possuem uma variável apenas;
- Possuem variável apenas do lado esquerdo (A) da equação;
- Realizam multiplicação apenas na variável;
- Não realizam divisão.

Padrões de input:

- Multiplicação sempre indicada explicitamente com '*' (ex: "2 * x", ao invés de "2x");
- Parte "A" da equação do lado esquerdo (ou seja a parte com módulo);
- Nunca mais de um espaço separando caracteres;
- '|' para abrir e fechar o módulo.

Exemplo de input/output:

in: 

|-4 * x + 3| - 5 = 10

out: 

Resultado de x para A = B: -3
Resultado de x para A = -B: 4.5
