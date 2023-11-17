#define VAZIO '.'
#define PAREDE_V '|'
#define PAREDE_H '_'
#define HEROI '@'
#define FANTASMA 'F'
#define PILULA 'P'
#define ESQUERDA 'A'
#define DIREITA 'D'
#define CIMA 'W'
#define BAIXO 'S'

struct mapa {
	
	char** matriz;
	int linhas;
	int colunas;
	
};

//criar tipo novo chamado MAPA

typedef struct mapa MAPA;

struct posicao {
	
	int x;
	int y;
	
};

typedef struct posicao POSICAO; 

void lerMapa();
void alocarMapa(MAPA* m);
void desenharMapa(MAPA* m);
void liberatMapa(MAPA* m);
int acabou();
int encontrarJogador(MAPA* m, POSICAO* p);
void movimentar(char direcao);
int podeAndar(int novox, int novoy);
void fantasmas(MAPA* m, POSICAO* f);
void movimentarFantasma(int xAtual, int yAtual);
int podeAndarFantasma(int x, int y);
