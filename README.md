![GitHub top language](https://img.shields.io/github/languages/top/opedro-c/bar-chart-race?color=red&label=%20&logo=c%2B%2B&style=for-the-badge)
![GitHub](https://img.shields.io/github/license/opedro-c/bar-chart-race?label=%20&style=for-the-badge)
# Bar Chart Race

Esse programa tem como objetivo simular uma disputa de corrida entre barras de 
acordo com os dados passados a partir de um arquivo no formato csv.
O programa conta com a customização de alguns detalhes que podem ser escolhidos pelo usuário,
como a velocidade de execução do programa e o número de barras que são exibidas na tela.

## Compilando o Código Fonte

A partir da pasta principal do repositório local  faça:

```
cmake -S source -B build
cmake --build build
```
ou (se não der certo)

```
cmake -S source -B build
cd build
make
```

## Usando compilação manual com g++

É possível compilar o programa "na mão" (i.e. sem o `cmake`) usando o `g++`. Para isso use o comando abaixo a partir da pasta principal do repo local **Implementação BarChart**:

```
mkdir -p build
g++ -Wall -std=c++11 -pedantic source/core/*.cpp source/libs/coms.cpp -I source/core -I source/libs -o build/bcr
```

## Executando

Independente do procedimento utilizado para compilar, será gerado um executável com o nome `bcr` dentro da pasta `build`. No __windows__ esse executável fica na pasta `Debug`.

Logo após a compilação, para executar o programa gerado use os comandos:

No linux:
```
./build/bcr data/algum_dos_arquivos.txt
```
No windows:
```
.\Debug\bcr.exe data/algum_dos_arquivos.txt
```
O número de barras exibidas na tela pode ser escolhida utilizando o argumento:
```
-b <número de barras>
```
Intervalo válido de número de barras: [1, 15]

A velocidade em que as barras são exibidas na tela pode ser escolhida utilizando o argumento:
```
-f <frames por segundo>
```
Intervalo válido de fps: [1, 24]
