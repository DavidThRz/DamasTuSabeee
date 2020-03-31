#include "GL/glut.h"
#include<GL/ETSIDI.h>
void OnDraw(void); //esta funcion sera llamada para dibujar
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	
void OnMouseClick(int button,int state,int x, int y);
void eatCounter(bool t, int& eat, int aux[8][8], int i, int j, int auxx=0, int auxy=0, bool eatable=false);
const int ml = 8;
const int WinSize = 800;
class Box {
public:
	int prop;//0 vacia, 1 roja , 2 negra, 3 reina roja, 4 reina negra
	int eat;//fichas que se puede capturar en este turno

};

class Board {
public:
	bool turn;//0 turno de rojo, 1 turno de negro
	Box Boxs[ml][ml];// casillas del tablero
	Box Chosen;
	void NewBoard();
	void Draw();
	void CheckEat();
	bool Chose(int x, int y);
	void Action(int x, int y);
};
void Board::NewBoard() {
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
bool Board::Chose(int x, int y) {
	for (int i = 0; i < ml; i++)
	{
		for (int j = 0; j < ml; j++) {
			if (Boxs[x][y].eat < Boxs[i][j].eat) {
				return false;
			};
		};
	};
	Chosen = Boxs[x][y];
	return true;
};
void Board::Action(int x, int y) {
	
};

class Game {
public:
	Board MyBoard;
	bool menu,chosen;
	void NewGame();
	void Mouse(int x, int y);
	void Draw();
};
void Game::NewGame(){
	MyBoard.NewBoard();
};
void Game::Mouse(int x, int y) {
	if (!menu) {
		int i, j;
		i = x / WinSize * 0.8;
		j = y / WinSize * 0.8;
		if (!chosen)chosen = MyBoard.Chose(i, j);
		else MyBoard.Action(i,j);
	};
};
void Game::Draw() {

};


Game MyGame;

int main(int argc, char* argv[])
{
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("MiJuego");

	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25, OnTimer, 0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);
	glutMouseFunc(OnMouseClick);

	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();

	return 0;
}
void OnDraw(void)
{
	//Borrado de la pantalla	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glOrtho(0,WinSize,0,WinSize,0,0.01);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	MyGame.Draw();

	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{

}
void OnTimer(int value)
{

}
void OnMouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT && state == GLUT_DOWN) {
		MyGame.Mouse(x, y);
	};
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
	};
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
					eatCounter(t, eat, aaux, i + auxx * 2, j + auxy * 2, auxx, auxy, true);// vuelve a llamar la funcion
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
