#ifndef GLOBAIS_H_INCLUDED
#define GLOBAIS_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Struct que define os elementos r, g e b de cada pixel
typedef struct{
	int red, green, blue;
}pixel;

//Struct de imagem que contém uma matriz de pixeis, além das outras informações contidas no arquivo ppm
typedef struct{
	pixel **pix_imagem;
	char codigo[3];
	int qualidade, colunas, linhas;
}imagem, *pont_imagem;


//Função responsável por realizar a alocação dînãmica dos pixeis, uma vez passado o endereço de memória da imagem
void AlocarPixeis(pont_imagem Imagem);

//Função responsável por ler a imagem a partir do arquivo e armazenar suas imformações dentro da variável Imagem
void lerImagem(pont_imagem Imagem);

//Função responsável por salvar os dados da imagem em um arquivo
void salvarImagem(pont_imagem Imagem);

//Menu Opções
void menu();


#endif // GLOBAIS_H_INCLUDED
