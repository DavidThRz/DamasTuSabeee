const int ml = 8;
void eatCounter(bool t, int i, int j, int& eat, int baux[8][8]);
class Box{
public:
	int prop;//0 vacia, 1 roja , 2 negra, 3 reina roja, 4 reina negra
	int eat;//fichas que se puede capturar en este turno

};
class Board {
	bool turn;//0 turno de rojo, 1 turno de negro
	Box Boxs[ml][ml];// casillas del tablero
	Board();
	void Draw();
	void CheckEat();
	void Eat();
	void CheckMove();
	void Move();
};
Board::Board() {
	turn = true;//empieza rojo
	for (int i = 0; i < ml; i++)
	{
		for (int j = 0; j < ml; j++)
		{
			if (i + j % 2) {
				if (i < (ml / 2))Boxs[i][j].prop = 2;//fichas negras
				else Boxs[i][j].prop = 1;//inicializar fichas rojas
			}
			else Boxs[i][j].prop = 0;//vacio
		};
	};
	//inicializar fichas
};

void Board::CheckEat() {
	int aux[ml][ml];
	for (int i = 0; i < ml; i++)for (int j = 0; j < ml; j++)aux[i][j] = Boxs[i][j].prop;//copiar la matriz
	for (int i = 0; i < ml; i++)for (int j = 0; j < ml; j++)eatCounter(turn,i,j,Boxs[i][j].eat,aux);
};

void eatCounter(bool t,int i, int j,int &eat,int baux[8][8]) 
{
	int aux[ml][ml];
	for (int i = 0; i < ml; i++)for (int j = 0; j < ml; j++)aux[i][j] = baux[i][j];//copiar la matriz
	int auxx, auxy;
	if (t) {//turno de rojas
		if ((aux[i][j] == 1 || aux[i][j] == 3) && (i < ml-2))
		{
			auxx = 1;
			if (j < ml - 2)//dentro del tablero
			{
				auxy=1;//direcction de captura
				if ((aux[i + auxx][j + auxy] == 2 || aux[i + auxx][j + auxy] == 4) && (aux[i + auxx * 2][j + auxy * 2] == 0))
				{
					eat++;
					aux[i + auxx][j + auxx] = 0;
					aux[i + auxx*2][j + auxy*2] = aux[i][j];
					aux[i][j] = 0;
					eatCounter(t,i+auxx*2,j+auxy*2,eat,aux);
				};
			}
			else if (j > 1)
			{
				auxy = -1;
				if ((aux[i + auxx][j + auxy] == 2 || aux[i + auxx][j + auxy] == 4) && (aux[i + auxx * 2][j + auxy * 2] == 0))
				{
					eat++;
					aux[i + auxx][j + auxx] = 0;
					aux[i + auxx * 2][j + auxy * 2] = aux[i][j];
					aux[i][j] = 0;
					eatCounter(t, i + auxx * 2, j + auxy * 2, eat, aux);
				};
			};
		}
		else if ((aux[i][j] == 3) && (i > 1))
		{
			auxx = -1;
			if (j < ml - 2)
			{
				auxy = 1;//direcction de captura
				if ((aux[i + auxx][j + auxy] == 2 || aux[i + auxx][j + auxy] == 4) && (aux[i + auxx * 2][j + auxy * 2] == 0))
				{
					eat++;
					aux[i + auxx][j + auxx] = 0;
					aux[i + auxx * 2][j + auxy * 2] = aux[i][j];
					aux[i][j] = 0;
					eatCounter(t, i + auxx * 2, j + auxy * 2, eat, aux);
				};
			}
			else if (j > 1)
			{
				auxy = -1;
				if ((aux[i + auxx][j + auxy] == 2 || aux[i + auxx][j + auxy] == 4) && (aux[i + auxx * 2][j + auxy * 2] == 0))
				{
					eat++;
					aux[i + auxx][j + auxx] = 0;
					aux[i + auxx * 2][j + auxy * 2] = aux[i][j];
					aux[i][j] = 0;
					eatCounter(t, i + auxx * 2, j + auxy * 2, eat, aux);
				};
			};
		};
	}
	else 
	{
		if ((aux[i][j] == 2 || aux[i][j] == 4) && (i >1))
		{
			auxx = -1;
			if (j < ml - 2)//dentro del tablero
			{
				auxy = 1;//direcction de captura
				if ((aux[i + auxx][j + auxy] == 2 || aux[i + auxx][j + auxy] == 4) && (aux[i + auxx * 2][j + auxy * 2] == 0))
				{
					eat++;
					aux[i + auxx][j + auxx] = 0;
					aux[i + auxx * 2][j + auxy * 2] = aux[i][j];
					aux[i][j] = 0;
					eatCounter(t, i + auxx * 2, j + auxy * 2, eat, aux);
				};
			}
			else if (j > 1)
			{
				auxy = -1;
				if ((aux[i + auxx][j + auxy] == 2 || aux[i + auxx][j + auxy] == 4) && (aux[i + auxx * 2][j + auxy * 2] == 0))
				{
					eat++;
					aux[i + auxx][j + auxx] = 0;
					aux[i + auxx * 2][j + auxy * 2] = aux[i][j];
					aux[i][j] = 0;
					eatCounter(t, i + auxx * 2, j + auxy * 2, eat, aux);
				};
			};
		}
		else if ((aux[i][j] == 4) && (i <ml-2))
		{
			auxx = 1;
			if (j < ml - 2)
			{
				auxy = 1;//direcction de captura
				if ((aux[i + auxx][j + auxy] == 2 || aux[i + auxx][j + auxy] == 4) && (aux[i + auxx * 2][j + auxy * 2] == 0))
				{
					eat++;
					aux[i + auxx][j + auxx] = 0;
					aux[i + auxx * 2][j + auxy * 2] = aux[i][j];
					aux[i][j] = 0;
					eatCounter(t, i + auxx * 2, j + auxy * 2, eat, aux);
				};
			}
			else if (j > 1)
			{
				auxy = -1;
				if ((aux[i + auxx][j + auxy] == 2 || aux[i + auxx][j + auxy] == 4) && (aux[i + auxx * 2][j + auxy * 2] == 0))
				{
					eat++;
					aux[i + auxx][j + auxx] = 0;
					aux[i + auxx * 2][j + auxy * 2] = aux[i][j];
					aux[i][j] = 0;
					eatCounter(t, i + auxx * 2, j + auxy * 2, eat, aux);
				};
			};
		};
	};
};
