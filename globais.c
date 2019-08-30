#include "globais.h"
#include "efeitos.h"

/*#####################################################
#######################################################
###########  ALOCAÇÃO DOS PIXELS ######################
#######################################################
#####################################################*/

void AlocarPixeis(pont_imagem Imagem){
	int i;
	Imagem->pix_imagem = (pixel**)malloc(Imagem->linhas * sizeof(pixel*));
	//ALOCA OS PIXELS USANDOS AS LINHAS E COLUNAS DO ARQUIVO PPM
	for(i = 0; i < Imagem->linhas; i++){
		Imagem->pix_imagem[i] = (pixel*)malloc(Imagem->colunas * sizeof(pixel));
	}
}
/*#####################################################
#######################################################
################## ABRIR IMG ##########################
#######################################################
#####################################################*/

void lerImagem(pont_imagem Imagem){
	FILE *imagem;
	int i, j;
	char nomeImagem[50];

	printf("Digite o nome da imagem a ser aberta: ");
	scanf("%s", nomeImagem);

    //abre o arquivo ppm no modo leitura "r"
	imagem = fopen(nomeImagem, "r");

	if(imagem == NULL){
		printf("Houve um erro ao abrir a imagem\n");
		//fecha o programa caso tenha erro ao abrir a img
		exit(1);
	}
    //Recupera os dados da imagem ppm
	fscanf(imagem,"%s",Imagem->codigo);
	fscanf(imagem,"%i",&Imagem->colunas);
	fscanf(imagem,"%i",&Imagem->linhas);
	AlocarPixeis(Imagem);
	fscanf(imagem,"%i",&Imagem->qualidade);

	for(i = 0; i < Imagem->linhas; i++){
		for(j = 0; j < Imagem->colunas; j++){
			fscanf(imagem,"%i",&Imagem->pix_imagem[i][j].red);
			fscanf(imagem,"%i",&Imagem->pix_imagem[i][j].green);
			fscanf(imagem,"%i",&Imagem->pix_imagem[i][j].blue);
		}
	}

	fclose(imagem);
}

/*#####################################################
#######################################################
########## SALVAR DADOS ALTERADOS NA IMG ##############
#######################################################
#####################################################*/

void salvarImagem(pont_imagem Imagem){
	FILE *imagem;
	int i, j;
	char nome_imagem[100];
	printf("Digite o nome da nova imagem:");
	scanf("%s", nome_imagem);

	imagem = fopen(nome_imagem, "w");

	fprintf(imagem,"%s\n",Imagem->codigo);
	fprintf(imagem,"%i ",Imagem->colunas);
	fprintf(imagem,"%i\n",Imagem->linhas);
	fprintf(imagem,"%i\n",Imagem->qualidade);

	for(i = 0; i < Imagem->linhas; i++){
		for(j = 0; j < Imagem->colunas; j++){
			fprintf(imagem,"%i ",Imagem->pix_imagem[i][j].red);
			fprintf(imagem,"%i ",Imagem->pix_imagem[i][j].green);
			fprintf(imagem,"%i\n",Imagem->pix_imagem[i][j].blue);
		}
	}
	fclose(imagem);
	//limpa a memória
	free(Imagem->pix_imagem);

    printf("\nImagem salva com sucesso!\n");
}


/*#####################################################
#######################################################
################## MENU ###############################
#######################################################
#####################################################*/

void menu(pont_imagem Imagem){

	int Blurring[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
	int DetectorBorda[3][3] = {{-1, -1, -1},{-1, 8, -1},{-1, -1, -1}};
	int Sharpe[3][3] = {{0, -1, 0},{-1, 5, -1},{0, -1, 0}};
	int i, zoom;
	int angulo, limite;
	int opc;
	char opc2[3];

	do{
	printf("\n/****************************************/\n");
	printf("/*\t(1) - Ampliar \t\t\t*/\n");
	printf("/*\t(2) - Reduzir \t\t\t*/\n");
	printf("/*\t(3) - Rotacionar \t\t*/\n");
	printf("/*\t(4) - Escala de Cinza\t\t*/\n");
    printf("/*\t(5) - Detectar Bordas\t\t*/\n");
    printf("/*\t(6) - Blurring\t\t\t*/\n");
	printf("/*\t(7) - Sharpening\t\t*/\n");
    printf("/*\t(8) - Thresholdingt\t\t*/\n\n");
	printf("/*\t(9) - Sair\t\t\t*/\n");
	printf("/****************************************/\n");
	printf("Opcao: ");
	scanf("%i", &opc);

	switch(opc){

	    case 1:
            printf("Digite o zoom: ");
            scanf("%i", &zoom);
            ampliar(Imagem, zoom);
            break;
        case 2:
            reduzir(Imagem);
            break;
        case 3:
            printf("Digite o angulo: ");
            scanf("%i",&angulo);

                if(angulo > 0){
                    for(i = 0; i < angulo / 90; i++){
                    girarHorario(Imagem);
                    }
                }else if(angulo < 0){
                    for(i = 0; i < angulo / -90; i++){
                    girarAntiHorario(Imagem);
                    }
                }
            break;
        case 4:
            escalaCinza(Imagem);
            break;
        case 5:
            ManipulacaoEspecial(Imagem, DetectorBorda, 1);
            break;
        case 6:
            ManipulacaoEspecial(Imagem, Blurring, 9);
            break;
        case 7:
            ManipulacaoEspecial(Imagem, Sharpe, 1);
            break;
        case 8:
            printf("Digite um valor limite: ");
            scanf("%i", &limite);
            threshold(Imagem, limite);
            break;
        case 9:
			exit(1);
            break;
        default:
            printf("Operacao nao reconhecida\n");
            /*######RECURSÃO##########*/
            menu(Imagem);
	}
	printf("Deseja realizar outra operacao? s (sim)/n(nao): ");
	scanf("%s", opc2);
	if(strcmp(opc2, "S") == 0){
		menu(Imagem);
	}else{
        break;
    }
	}while(opc!=10);
}
