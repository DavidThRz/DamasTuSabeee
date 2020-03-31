void eatCounter(bool t, int& eat, int aux[8][8], int i, int j, int auxx=0, int auxy=0, bool eatable=false);
const int ml = 8;
class Box {
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
Board::Board() {//constructor
	turn = true;//empieza rojo
	for (int i = 0; i < ml; i++)
	{
		for (int j = 0; j < ml; j++)
		{
			if (i + j % 2) {
				if (i < (ml / 2 - 1))Boxs[i][j].prop = 2;//fichas negras
				else if (i > ml / 2)Boxs[i][j].prop = 1;//inicializar fichas rojas
			}
			else Boxs[i][j].prop = 0;//vacio
		};
	};
	//inicializar fichas
};

void Board::CheckEat() {
	int aux[ml][ml];
	for (int i = 0; i < ml; i++)for (int j = 0; j < ml; j++)aux[i][j] = Boxs[i][j].prop;//copiar la matriz
	for (int i = 0; i < ml; i++)for (int j = 0; j < ml; j++)eatCounter(turn, Boxs[i][j].eat,aux,i, j);//iniciar arbol para cada ficha
};

void eatCounter(bool t, int& eat, int aux[8][8], int i, int j, int auxx, int auxy, bool eatable)
{
	int aaux[ml][ml];//matriz auxiliar para no afcetar a la original
	for (int i = 0; i < ml; i++)for (int j = 0; j < ml; j++)aaux[i][j] = aux[i][j];//copiar la matriz
	if (eatable) {
		eat++; //contador aumenta
		aaux[i + auxx][j + auxx] = 0;//desaparece la ficha que ha sido capturada
		aaux[i + auxx * 2][j + auxy * 2] = aux[i][j];//en la distancia dos pone la ficha "comedor"
		aaux[i][j] = 0;//pone vacio en la posicion original de la ficha comedor
	}
	int auxx, auxy;//para las distintas direcciones
	if (t) {//turno de rojas
		if ((aux[i][j] == 1 || aux[i][j] == 3) && (i < ml - 2))
		{
			auxx = 1;//hacia arriba
			if (j < ml - 2)//verificar si va a salir del tablero
			{
				auxy = 1;//derecha
				if ((aux[i + auxx][j + auxy] == 2 || aux[i + auxx][j + auxy] == 4) && (aux[i + auxx * 2][j + auxy * 2] == 0))
				{
					//si es reina o peon de rojas(2 o 4) y en la direccion con distancia 1 es una ficha enemiga
					//y el direccion con distancia 2 esta vacia hace lo siguiente:
					eatCounter(t, eat,aaux,i + auxx * 2, j + auxy * 2, auxx, auxy,true);// vuelve a llamar la funcion
				};
			}
			else if (j > 1)
			{
				auxy = -1;
				if ((aux[i + auxx][j + auxy] == 2 || aux[i + auxx][j + auxy] == 4) && (aux[i + auxx * 2][j + auxy * 2] == 0))
				{
					eatCounter(t, eat, aaux, i + auxx * 2, j + auxy * 2, auxx, auxy, true);
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
					eatCounter(t, eat, aaux, i + auxx * 2, j + auxy * 2, auxx, auxy, true);
				};
			}
			else if (j > 1)
			{
				auxy = -1;
				if ((aux[i + auxx][j + auxy] == 2 || aux[i + auxx][j + auxy] == 4) && (aux[i + auxx * 2][j + auxy * 2] == 0))
				{
					eatCounter(t, eat, aaux, i + auxx * 2, j + auxy * 2, auxx, auxy, true);
				};
			};
		};
	}
	else
	{
		if ((aux[i][j] == 2 || aux[i][j] == 4) && (i > 1))
		{
			auxx = -1;
			if (j < ml - 2)//dentro del tablero
			{
				auxy = 1;//direcction de captura
				if ((aux[i + auxx][j + auxy] == 2 || aux[i + auxx][j + auxy] == 4) && (aux[i + auxx * 2][j + auxy * 2] == 0))
				{
					eatCounter(t, eat, aaux, i + auxx * 2, j + auxy * 2, auxx, auxy, true);
				};
			}
			else if (j > 1)
			{
				auxy = -1;
				if ((aux[i + auxx][j + auxy] == 2 || aux[i + auxx][j + auxy] == 4) && (aux[i + auxx * 2][j + auxy * 2] == 0))
				{
					eatCounter(t, eat, aaux, i + auxx * 2, j + auxy * 2, auxx, auxy, true);
				};
			};
		}
		else if ((aux[i][j] == 4) && (i < ml - 2))
		{
			auxx = 1;
			if (j < ml - 2)
			{
				auxy = 1;//direcction de captura
				if ((aux[i + auxx][j + auxy] == 2 || aux[i + auxx][j + auxy] == 4) && (aux[i + auxx * 2][j + auxy * 2] == 0))
				{
					eatCounter(t, eat, aaux, i + auxx * 2, j + auxy * 2, auxx, auxy, true);
				};
			}
			else if (j > 1)
			{
				auxy = -1;
				if ((aux[i + auxx][j + auxy] == 2 || aux[i + auxx][j + auxy] == 4) && (aux[i + auxx * 2][j + auxy * 2] == 0))
				{
					eatCounter(t, eat, aaux, i + auxx * 2, j + auxy * 2, auxx, auxy, true);
				};
			};
		};
	};
};
