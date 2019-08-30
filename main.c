#include "globais.h"
#include "efeitos.h"

int main(){
	imagem Imagem;
	lerImagem(&Imagem);
	menu(&Imagem);
	salvarImagem(&Imagem);
	return 0;
}
