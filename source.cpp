#define _CRT_SECURE_NO_WARNINGS
#include "GL/freeglut.h"
#include<GL/ETSIDI.h>

void OnDraw(void); //esta funcion sera llamada para dibujar
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	
void OnMouseClick(int button,int state,int x, int y);
void DrawString(float x, float y, const char* c, int var = 0, bool v = false);

const int ml = 8;
const float WinSize = 600;
const int MaxStrLen = 100;


class Box
{
public:
	bool free;//false=vacio,true=ocupado
	bool color;//negro=true;rojo==false
	bool capture;//true=se puede capturar en este turno
	bool move;//true=puede mover en este turno
	bool king;//true= acoronado
	Box();//constructor por defecto
	void Draw();
	Box& operator= (const Box&);//operador miembro de asignacion sobrecargado
};
Box::Box()
{
	color = capture = move = king = false;
	free = true;
};
Box& Box::operator= (const Box& a)
{
	free = a.free;
	color = a.color;
	capture = a.capture;
	move = a.move;
	king = a.king;
	return(*this);
};
void Box::Draw() {
	glBegin(GL_QUADS);
	glVertex3d(-0.5, -0.5, 0);
	glVertex3d(0.5, -0.5, 0);
	glVertex3d(0.5, 0.5, 0);
	glVertex3d(-0.5, 0.5, 0);
	glEnd();
	if (!free) {
		color ? glColor4f(1, 1, 1, 1) : glColor4f(1, 0, 0, 1);
		glutSolidSphere(0.4, 20, 20);
	};
	if (king) {
		glTranslatef(0,0,0.5);
		glColor4f(1,1,0,1);
		glutSolidSphere(0.2, 20, 20);
		glTranslatef(0, 0, -0.5);
	}
};

class Board 
{
public:
	bool turn,chosen,end;//0 turno de rojo, 1 turno de negro
	Box Boxs[ml][ml];// casillas del tablero
	int chosenx, choseny;
	Board();
	void Draw();
	void Check();
	bool Chose(int x, int y);
	bool Action(int x, int y);
	void Run(int x, int y);
};
Board::Board() 
{
	turn = true;//empieza negro
	for (int i = 0; i < ml; i++)
	{
		for (int j = 0; j < ml; j++)
		{
			Boxs[i][j].free = false;
			if ((i + j) % 2==0) {
				if (j < (ml / 2 - 1))Boxs[i][j].color = true;//fichas negras
				else if (j > ml / 2)Boxs[i][j].color = false;//inicializar fichas rojas
				else Boxs[i][j].free = true;
			}
			else Boxs[i][j].free = true;;//vacio
		};
	};
	//inicializar fichas
};
void Board::Check() 
{
	int dirx, diry;
	for (int i = 0; i < ml; i++)
	{
		for (int j = 0; j < ml; j++) 
		{
			Boxs[i][j].capture = false;//inicializar
			Boxs[i][j].move = false;
			if (turn)diry = 1;//hacia arriba si en de color negro
			else diry = -1;// hacia abajo si es de color rojo
			if (Boxs[i][j].color==turn)
			{
				if ((j + diry )< ml&&(j+diry)>=0)
				{
					dirx = 1;//derecha
					if ((i + dirx) < ml)//condicion para que no producza error
						if (Boxs[i + dirx][j + diry].free)
							//primero compueba que j+dir no se sale del alcance de la matriz
							Boxs[i][j].move = true;//se puede mover

					if ((i + dirx * 2) < ml && (j + diry * 2) < ml && (j + diry*2) >= 0)
						if ((Boxs[i + dirx * 2][j + diry * 2].free) && turn != Boxs[i + dirx][j + diry].color && !Boxs[i + dirx][j + diry].free)
							Boxs[i][j].capture = true;
					dirx = -1; //izquierda
					if ((i + dirx) >= 0)//condicion para que no producza error
						if (Boxs[i + dirx][j + diry].free)
							//primero compueba que j+dir no se sale del alcance de la matriz
							Boxs[i][j].move = true;//se puede mover

					if ((i + dirx * 2) >= 0 && (j + diry * 2)<ml && (j + diry*2) >= 0)
						if (Boxs[i + dirx * 2][j + diry * 2].free && turn != Boxs[i + dirx][j + diry].color && !Boxs[i + dirx][j + diry].free)
							Boxs[i][j].capture = true;
				};
				
				diry *= -1;//campnbiar la direccion de eje y, repetir para las fichas acoronadas

				if ((j + diry) >=0 && Boxs[i][j].king==true && (j + diry ) <ml)
				{
					dirx = 1;//derecha
					if ((i + dirx) < ml)//condicion para que no producza error
						if (Boxs[i + dirx][j + diry].free)
							//primero compueba que j+dir no se sale del alcance de la matriz
							Boxs[i][j].move = true;//se puede mover

					if ((i + dirx * 2) < ml && (j + diry * 2)>=0 && (j + diry * 2) <ml)
						if (Boxs[i + dirx * 2][j + diry * 2].free && turn != Boxs[i + dirx][j + diry].color && !Boxs[i + dirx][j + diry].free)
							Boxs[i][j].capture = true;
					dirx = -1; //izquierda
					if ((i + dirx) >= 0)//condicion para que no producza error
						if (Boxs[i + dirx][j + diry].free)
							//primero compueba que j+dir no se sale del alcance de la matriz
							Boxs[i][j].move = true;//se puede mover

					if ((i + dirx * 2) >= 0 && (j + diry * 2)>=0 && (j + diry * 2) < ml)
						if (Boxs[i + dirx * 2][j + diry * 2].free && turn != Boxs[i + dirx][j + diry].color && !Boxs[i + dirx][j + diry].free)
							Boxs[i][j].capture = true;
				};
			};
			if (Boxs[i][j].capture)Boxs[i][j].move = true;//capturar tambien cuenta como mover
		};
	};

	end = true;
	for (int i = 0; i < ml; i++)for (int j = 0; j < ml; j++)if (Boxs[i][j].move && !Boxs[i][j].free)end = false;//fin de la partida
	for (int i = 0; i < ml; i++)if (!Boxs[i][0].free && !Boxs[i][0].color)Boxs[i][0].king = true;//acoronar peones rojas
	for (int i = 0; i < ml; i++)if (!Boxs[i][ml-1].free && Boxs[i][ml-1].color)Boxs[i][ml-1].king = true;//acoronar peons negras
};
bool Board::Chose(int x, int y) 
{
	if (Boxs[x][y].move&&!Boxs[x][y].free) 
	{
		if (!Boxs[x][y].capture)
		{
			for (int i = 0; i < ml; i++)
				for (int j = 0; j < ml; j++)
					if (!Boxs[i][j].free&&Boxs[i][j].color==turn&&Boxs[i][j].capture) return false;
			chosenx = x;
			choseny = y;//mueve sin capturar
			return true;
		}
		else
		{
			chosenx = x;
			choseny = y;//mueve sin capturar
			return true;
		};
	}
	else return false;// si no se puede mover(incluye capturar)
};
bool Board::Action(int x, int y) 
{
	if (!Boxs[x][y].free)return false;
	Box aux;
	if ((((x - chosenx) * (y - choseny)) == 4 || ((x - chosenx) * (y - choseny)) == -4) && (Boxs[chosenx][choseny].capture))
	{
		
		if (((y - choseny) == (turn ? 2 : -2)) || Boxs[chosenx][choseny].king)//que sea dama o que sigua la direccion del jugador
		{
			aux = Boxs[x][y];//copiar la casilla vacia
			Boxs[(x - chosenx) / 2 + chosenx][(y - choseny) / 2 + choseny] = aux;//vaciar la ficha capturada
			Boxs[x][y] = Boxs[chosenx][choseny];//mover la ficha al destino
			Boxs[chosenx][choseny] = aux;//vaciar el origen
			Check();
			return true;
		};

	}
	else if ((((x - chosenx) * (y - choseny)) == 1 || ((x - chosenx) * (y - choseny)) == -1) && (!Boxs[chosenx][choseny].capture))
	{
		if ((y - choseny) == (turn ? 1 : -1)||Boxs[chosenx][choseny].king)
		{
			aux=Boxs[x][y];//casilla vacia
			Boxs[x][y] = Boxs[chosenx][choseny];//mover hasta el destino
			Boxs[chosenx][choseny] = aux;//vaciar el origen
			return true;
		};
	};

	return false;
	
};
void Board::Draw()
{
	for (int i = 0; i < ml; i++)for (int j = 0; j < ml; j++)
	{
		glTranslatef(i, j, 0);
		(i + j) % 2 == 0 ? glColor4f(0.1, 0.1, 0.1, 1) : glColor4f(1, 1, 1, 1);//color negro si el impar
		Boxs[i][j].Draw();
		glTranslatef(-i, -j, 0);
	};
	//elegido
	if (chosen)
	{
		glTranslatef(chosenx, choseny, 0);
		glColor4f(0, 0, 1, 1);
		glBegin(GL_QUADS);
		glVertex3d(-0.5, -0.5, 0.01);
		glVertex3d(0.5, -0.5, 0.01);
		glVertex3d(0.5, 0.5, 0.01);
		glVertex3d(-0.5, 0.5, 0.01);
		glEnd();
		glTranslatef(-chosenx, -choseny, 0);
	};
	if (end)
	{
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("dialogue.png").id);
		glTranslatef((ml / 2 - 0.5), (ml / 2 - 0.5), 0);
		glBegin(GL_POLYGON);
		glColor4f(1, 1, 1, 1);
		glTexCoord2d(0, 1);	glVertex3f(1, 0.5, 0);
		glTexCoord2d(1, 1);	glVertex3f(1, -0.5, 0);
		glTexCoord2d(1, 0);	glVertex3f(-1,-0.5, 0);
		glTexCoord2d(0, 0);	glVertex3f(-1, 0.5, 0);
		glEnd(); 
		glTranslatef((-ml / 2 - 0.5), -(ml / 2 - 0.5), 0);
		glDisable(GL_TEXTURE_2D);
		glColor4f(0,0,0,1);
		if (turn)DrawString(ml/2.0f,ml/2.0f-0.5,"Red Wins");
		else DrawString(ml / 2.0f, ml / 2.0f-0.5, "Black Wins");
		glEnable(GL_DEPTH_TEST);
	};
};
void Board::Run(int x, int y)
{
	// funcionamiento del tablero
	Check();
	if (Chose(x, y))
	{
		chosen = true;
		return;
	};
	if (chosen)
	{
		Check();
		if (Action(x, y))
		{
			chosen = false;
			if (Boxs[x][y].capture)turn = !turn;
			turn = !turn;
			Check();
		};
	};
};

class Game 
{
public:
	Board MyBoard;
	Game();
	bool menu;
	void Mouse(int x, int y);
	void Draw();
};
Game::Game()
{
};
void Game::Mouse(int x, int y) 
{
	if (!menu) {
		int i, j;
		i = x / WinSize * ml;
		j = (WinSize - y) / WinSize * ml;//convertir pixeles a casillas
		MyBoard.Run(i, j);
	};


};
void Game::Draw() 
{
	MyBoard.Draw();
	
};


Game MyGame;

int main(int argc, char* argv[])
{
	FreeConsole();
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(WinSize, WinSize);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Minidamas");

	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, WinSize / (float)WinSize, 0.1, 150);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	float aux = ml / 2.0f - 0.5;//en el medio
	gluLookAt(aux, aux, aux * 3.2, aux, aux + 1e-8, 0.0,      // hacia que punto mira  (0,0,0) 
		0.0, 0.0, 1.0);      // definimos hacia arriba (eje Y)    

	MyGame.Draw();
	glutSwapBuffers();
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	glutPostRedisplay();
}
void OnTimer(int value)
{
	glutPostRedisplay();
}
void OnMouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT && state == GLUT_DOWN) {
		MyGame.Mouse(x, y);
	};
	glutPostRedisplay();
};


void DrawString(float x, float y, const char* c, int var, bool v) {
	char ch[MaxStrLen];
	strcpy(ch, c);
	if (v) {
		char cha[MaxStrLen];
		int cifras = 0;
		int aux = var;
		while (aux / 10 > 0) {
			cifras++;
			aux /= 10;
		};
		aux = var;
		cha[cifras + 1] = '\0';
		while (cifras >= 0) {
			cha[cifras] = 48 + aux % 10;
			aux /= 10;
			cifras--;
		};
		strcat(ch, cha);
	};
	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char*>(ch));
};
