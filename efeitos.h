#ifndef EFEITOS_H_INCLUDED
#define EFEITOS_H_INCLUDED

//Função responsável por rotacionar a imagem no sentido anti horário
void girarAntiHorario(pont_imagem Imagem);

//Função responsável por rotacionar a imagem no sentido horário
void girarHorario(pont_imagem Imagem);

//Função responsável pela binarização da imagem, uma vez passado um limite para o truncamento
void threshold(pont_imagem Imagem, int limite);

//Função responsável por ampliar a imagem em x vezes, uma vez que seja passado a quantidade de vezes
void ampliar(pont_imagem Imagem, int zoom);

//Função que reduz a imagem pela metade
void reduzir(pont_imagem Imagem);

//Função responsável por deixar a imagem em escala de cinza, que é feito por meio da média dos valores do r, g e b dos píxeis
void escalaCinza(pont_imagem Imagem);

//Função responsável por aplicar os filtros blurring, sharpening e detector de bordas na imagem
void ManipulacaoEspecial(pont_imagem Imagem, int efeito[3][3], int divisor);


#endif // EFEITOS_H_INCLUDED
