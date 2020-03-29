const int ml = 8;
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
