#include "globais.h"
#include "efeitos.h"


/*#####################################################
#######################################################
################# ROTACIONAR A IMG ####################
#######################################################
#####################################################*/

void girarAntiHorario(pont_imagem Imagem){
	int i, j, l;

    //cria uma nova struct para armazenar os dados da img modificada
	imagem ImagemModificada;
	ImagemModificada.linhas = Imagem->colunas;
	ImagemModificada.colunas = Imagem->linhas;
	//aloca a nova matriz
	AlocarPixeis(&ImagemModificada);

    //
	for(j = Imagem->colunas - 1, l = 0; l < Imagem->linhas && j >= 0; j--, l++){
		for(i = 0; i < Imagem->linhas; i++){
			ImagemModificada.pix_imagem[l][i] = Imagem->pix_imagem[i][j];
		}
	}
	//limpa a memoria
	free(Imagem->pix_imagem);
	//passa os dados modificados para a img original
	Imagem->pix_imagem = ImagemModificada.pix_imagem;
	Imagem->colunas = ImagemModificada.colunas;
	Imagem->linhas = ImagemModificada.linhas;
}

void girarHorario(pont_imagem Imagem){
	int i, j, l;

	imagem ImagemModificada;
	ImagemModificada.linhas = Imagem->colunas;
	ImagemModificada.colunas = Imagem->linhas;
	AlocarPixeis(&ImagemModificada);

	for(l = Imagem->colunas - 1, i = 0; i < Imagem->linhas && l >= 0; i++, l--){
		for(j = 0; j < Imagem->colunas; j++){
			ImagemModificada.pix_imagem[j][l] = Imagem->pix_imagem[i][j];
		}
	}
	free(Imagem->pix_imagem);
	Imagem->pix_imagem = ImagemModificada.pix_imagem;
	Imagem->colunas = ImagemModificada.colunas;
	Imagem->linhas = ImagemModificada.linhas;
}

/*#####################################################
#######################################################
#################      THRESHOLD   ####################
#######################################################
#####################################################*/

void threshold(pont_imagem Imagem, int limite){
	int mediaCores, i, j;
	for(i = 0; i < Imagem->linhas; i++){
		for(j = 0; j < Imagem->colunas; j++){
			mediaCores = (Imagem->pix_imagem[i][j].green + Imagem->pix_imagem[i][j].red + Imagem->pix_imagem[i][j].blue) / 3;
			if(mediaCores > limite){
				Imagem->pix_imagem[i][j].green = 255;
				Imagem->pix_imagem[i][j].red = 255;
				Imagem->pix_imagem[i][j].blue = 255;
			}else{
				Imagem->pix_imagem[i][j].green = 0;
				Imagem->pix_imagem[i][j].red = 0;
				Imagem->pix_imagem[i][j].blue = 0;
			}
		}
	}
}

/*#####################################################
#######################################################
#################### AMPLIAR  #########################
#######################################################
#####################################################*/

void ampliar(pont_imagem Imagem, int zoom){
	int i, j, k, l;

	imagem ImagemModificada;
	ImagemModificada.linhas = Imagem->linhas * zoom;
	ImagemModificada.colunas = Imagem->colunas * zoom;
	AlocarPixeis(&ImagemModificada);

	for(i = 0, k = 0; i < Imagem->linhas && k < ImagemModificada.linhas; k ++){
		if(k % zoom == 0 && k != 0){
			i++;
		}
		for(j = 0, l = 0; j < Imagem->colunas && l < ImagemModificada.colunas;  l++){
			if(l % zoom == 0 && l != 0){
				j++;
			}
			ImagemModificada.pix_imagem[k][l] = Imagem->pix_imagem[i][j];
		}
	}
	free(Imagem->pix_imagem);
	Imagem->linhas = ImagemModificada.linhas;
	Imagem->colunas = ImagemModificada.colunas;
	Imagem->pix_imagem = ImagemModificada.pix_imagem;

}

/*#####################################################
#######################################################
#################### REDUZIR  #########################
#######################################################
#####################################################*/

void reduzir(pont_imagem Imagem){
	int i, j, k, l;

	imagem ImagemModificada;
	ImagemModificada.linhas = Imagem->linhas / 2;
	ImagemModificada.colunas = Imagem->colunas / 2;
	AlocarPixeis(&ImagemModificada);

	for(i = 0, k = 1; i < ImagemModificada.linhas && k < Imagem->linhas; i++, k += 2){
		for(j = 0, l = 1; j < ImagemModificada.colunas && l < Imagem->colunas; j++, l += 2){

			//RED
			ImagemModificada.pix_imagem[i][j].red = (
                Imagem->pix_imagem[k - 1][l - 1].red +
                Imagem->pix_imagem[k - 1][l].red +
                Imagem->pix_imagem[k][l - 1].red +
                Imagem->pix_imagem[k][l].red
            ) / 4;
			//GREEN
			ImagemModificada.pix_imagem[i][j].green = (
                Imagem->pix_imagem[k - 1][l - 1].green +
                Imagem->pix_imagem[k - 1][l].green +
                Imagem->pix_imagem[k][l - 1].green +
                Imagem->pix_imagem[k][l].green
            ) / 4;
			//BLUE
			ImagemModificada.pix_imagem[i][j].blue = (
                Imagem->pix_imagem[k - 1][l - 1].blue +
                Imagem->pix_imagem[k - 1][l].blue +
                Imagem->pix_imagem[k][l - 1].blue +
                Imagem->pix_imagem[k][l].blue
            ) / 4;
		}
	}
	free(Imagem->pix_imagem);
	Imagem->linhas = ImagemModificada.linhas;
	Imagem->colunas = ImagemModificada.colunas;
	Imagem->pix_imagem = ImagemModificada.pix_imagem;
}

/*#####################################################
#######################################################
################## ESCALA DE CINZA ####################
#######################################################
#####################################################*/

void escalaCinza(pont_imagem Imagem){
	int i, j;
	int mediaCores;
	for(i = 0; i < Imagem->linhas; i++){
		for(j = 0; j < Imagem->colunas; j++){
			mediaCores = (Imagem->pix_imagem[i][j].red + Imagem->pix_imagem[i][j].green + Imagem->pix_imagem[i][j].blue) / 3;
			Imagem->pix_imagem[i][j].red = mediaCores;
			Imagem->pix_imagem[i][j].green = mediaCores;
			Imagem->pix_imagem[i][j].blue = mediaCores;
		}
	}
}

/*#####################################################
#######################################################
################## APLICAR EFEITO  ####################
#######################################################
#####################################################*/

//Função responsável por aplicar os filtros blurring, sharpening e detector de bordas na imagem

void ManipulacaoEspecial(pont_imagem Imagem, int efeito[3][3], int divisor){
	int i = 0, j = 0, k, l;
	pixel somaElementos;
	somaElementos.red = 0;
	somaElementos.green = 0;
	somaElementos.blue = 0;

	imagem ImagemModificada;
	ImagemModificada.linhas = Imagem->linhas;
	ImagemModificada.colunas = Imagem->colunas;
	AlocarPixeis(&ImagemModificada);

	do{
		k = 0;
		l = 0;
		do{
			somaElementos.red += Imagem->pix_imagem[i + k][j + l].red * efeito[k][l];
			somaElementos.green += Imagem->pix_imagem[i + k][j + l].green * efeito[k][l];
			somaElementos.blue += Imagem->pix_imagem[i + k][j + l].blue * efeito[k][l];
			if(l == 2){
				l = 0;
				k++;
			}else{
				l++;
			}
		}while(k < 3);
		somaElementos.red /= divisor;
		somaElementos.green /= divisor;
		somaElementos.blue /= divisor;
		//se o valor for maior que o máximo para o pixel da img, ele sera igual a qualidade
		if(somaElementos.red > 255)
			somaElementos.red = Imagem->qualidade;
		if(somaElementos.green > 255)
			somaElementos.green = Imagem->qualidade;
		if(somaElementos.blue > 255)
			somaElementos.blue = Imagem->qualidade;
		//se o valor for menor que zero, será igual a zero
		if(somaElementos.red < 0)
			somaElementos.red = 0;
		if(somaElementos.green < 0)
			somaElementos.green = 0;
		if(somaElementos.blue < 0)
			somaElementos.blue = 0;
		ImagemModificada.pix_imagem[i + 1][j + 1] = somaElementos;
		somaElementos.red = 0;
		somaElementos.green = 0;
		somaElementos.blue = 0;
		if(j == Imagem->colunas - 3){
			j = 0;
			i++;
		}else{
			j++;
		}
	}while(i < Imagem->linhas - 2);
	for(i = 0; i < Imagem->linhas; i++){
		for(j = 0; j < Imagem->colunas; j++){
			if(i == 0 || i == Imagem->linhas - 1 || j == 0 || j == Imagem->colunas - 1){
				ImagemModificada.pix_imagem[i][j] = Imagem->pix_imagem[i][j];
			}
		}
	}
	free(Imagem->pix_imagem);
	Imagem->linhas = ImagemModificada.linhas;
	Imagem->colunas = ImagemModificada.colunas;
	Imagem->pix_imagem = ImagemModificada.pix_imagem;
}
