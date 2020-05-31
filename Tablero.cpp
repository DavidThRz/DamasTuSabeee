#include "Tablero.h"
Tablero::Tablero()
{
	turno = true;//empieza negro
	for (int i = 0; i < ml; i++)
	{
		for (int j = 0; j < ml; j++)
		{
			if ((i + j) % 2 == 0) {
				if (j < (ml / 2 - 1))Casillas[i][j]=new Peon(true);//fichas negras
				else if (j > ml / 2)Casillas[i][j]=new Peon(false);//inicializar fichas rojas
				else Casillas[i][j]=new Casilla(); //vacio
			}
			else Casillas[i][j]=new Casilla();//vacio
		};
	};
	//inicializar fichas
};
void Tablero::dibuja()
{
	revisa();
	for (int i = 0; i < ml; i++)for (int j = 0; j < ml; j++)
	{
		glTranslatef(i, j, 0);
		(i + j) % 2 == 0 ? glColor4f(0.1, 0.1, 0.1, 1) : glColor4f(1, 1, 1, 1);//color negro si el impar
		Casillas[i][j]->dibuja();
		glTranslatef(-i, -j, 0);
	};
	//elegido
	if (elegido)
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
		for (int i = 0; i < 4; i++) {
			if (destinox[i] >= 0) {
				glTranslatef(destinox[i], destinoy[i], 0);
				glColor4f(0, 1, 0, 1);
				glBegin(GL_QUADS);
				glVertex3d(-0.5, -0.5, 0.01);
				glVertex3d(0.5, -0.5, 0.01);
				glVertex3d(0.5, 0.5, 0.01);
				glVertex3d(-0.5, 0.5, 0.01);
				glEnd();
				glTranslatef(-destinox[i], -destinoy[i], 0);
			};
		};
	}
	else
	{
		for (int i = 0; i < ml; i++)for (int j = 0; j < ml; j++)
			if (elije(i,j))
			{
				glTranslatef(i, j, 0);
				glColor4f(0, 1, 0, 1);
				glBegin(GL_QUADS);
				glVertex3d(-0.5, -0.5, 0.01);
				glVertex3d(0.5, -0.5, 0.01);
				glVertex3d(0.5, 0.5, 0.01);
				glVertex3d(-0.5, 0.5, 0.01);
				glEnd();
				glTranslatef(-i, -j, 0);
			};
	};
	if (fin)
	{
		glColor4f(1, 1, 0, 1);
		if (turno)DrawString(ml / 2.0f, ml / 2.0f - 0.5, "Red Wins");
		else DrawString(ml / 2.0f, ml / 2.0f - 0.5, "Black Wins");
		glEnable(GL_DEPTH_TEST);
	};
};
void Tablero::revisa()
{
	for (int i = 0; i < ml; i++)
		if (!Casillas[i][0]->getLibre() && !Casillas[i][0]->getColor())Casillas[i][0]->setAcor(true);//acoronar peones rojas

	for (int i = 0; i < ml; i++)
		if (!Casillas[i][ml - 1]->getLibre() && Casillas[i][ml - 1]->getColor())Casillas[i][ml - 1]->setAcor(true);//acoronar peons negras

	int dirx, diry;
	for (int i = 0; i < ml; i++)
	{
		for (int j = 0; j < ml; j++)
		{
			Casillas[i][j]->setCap(false);//inicializar
			Casillas[i][j]->setMov(false);
			if (turno)diry = 1;//hacia arriba si en de color negro
			else diry = -1;// hacia abajo si es de color rojo
			if (Casillas[i][j]->getColor() == turno)
			{
				if ((j + diry) < ml && (j + diry) >= 0)
				{
					dirx = 1;//derecha
					if ((i + dirx) < ml)//condicion para que no producza error
						if (Casillas[i + dirx][j + diry]->getLibre())
							//primero compueba que j+dir no se sale del alcance de la matriz
							Casillas[i][j]->setMov(true);//se puede mover

					if ((i + dirx * 2) < ml && (j + diry * 2) < ml && (j + diry * 2) >= 0)
						if ((Casillas[i + dirx * 2][j + diry * 2]->getLibre()) && turno != Casillas[i + dirx][j + diry]->getColor() && !Casillas[i + dirx][j + diry]->getLibre())
							Casillas[i][j]->setCap(true);
					dirx = -1; //izquierda
					if ((i + dirx) >= 0)//condicion para que no producza error
						if (Casillas[i + dirx][j + diry]->getLibre())
							//primero compueba que j+dir no se sale del alcance de la matriz
							Casillas[i][j]->setMov(true);//se puede mover

					if ((i + dirx * 2) >= 0 && (j + diry * 2) < ml && (j + diry * 2) >= 0)
						if (Casillas[i + dirx * 2][j + diry * 2]->getLibre() && turno != Casillas[i + dirx][j + diry]->getColor() && !Casillas[i + dirx][j + diry]->getLibre())
							Casillas[i][j]->setCap(true);
				};

				diry *= -1;//campnbiar la direccion de eje y, repetir para las fichas acoronadas

				if ((j + diry) >= 0 && Casillas[i][j]->getAcor() == true && (j + diry) < ml)
				{
					dirx = 1;//derecha
					if ((i + dirx) < ml)//condicion para que no producza error
						if (Casillas[i + dirx][j + diry]->getLibre())
							//primero compueba que j+dir no se sale del alcance de la matriz
							Casillas[i][j]->setMov(true);//se puede mover

					if ((i + dirx * 2) < ml && (j + diry * 2) >= 0 && (j + diry * 2) < ml)
						if (Casillas[i + dirx * 2][j + diry * 2]->getLibre() && turno != Casillas[i + dirx][j + diry]->getColor() && !Casillas[i + dirx][j + diry]->getLibre())
							Casillas[i][j]->setCap(true);
					dirx = -1; //izquierda
					if ((i + dirx) >= 0)//condicion para que no producza error
						if (Casillas[i + dirx][j + diry]->getLibre())
							//primero compueba que j+dir no se sale del alcance de la matriz
							Casillas[i][j]->setMov(true);//se puede mover

					if ((i + dirx * 2) >= 0 && (j + diry * 2) >= 0 && (j + diry * 2) < ml)
						if (Casillas[i + dirx * 2][j + diry * 2]->getLibre() && turno != Casillas[i + dirx][j + diry]->getColor() && !Casillas[i + dirx][j + diry]->getLibre())
							Casillas[i][j]->setCap(true);
				};
			};
			if (Casillas[i][j]->getCap())Casillas[i][j]->setMov(true);//capturar tambien cuenta como mover
		};
	};

	fin = true;
	for (int i = 0; i < ml; i++)
		for (int j = 0; j < ml; j++)
			if (Casillas[i][j]->getMov() && !Casillas[i][j]->getLibre())fin = false;//fin de la partida

	
	for (int i = 0; i < ml; i++)
		for (int j = 0; j < ml; j++)
			if (Casillas[i][j]->getLibre() == true) {
				Casilla aux=*Casillas[i][j];
				Casillas[i][j] = new Casilla();
				*Casillas[i][j] = aux;
			}
			else {
				if (Casillas[i][j]->getAcor() == false) {
					Casilla aux = *Casillas[i][j];
					Casillas[i][j] = new Peon(true);
					*Casillas[i][j] = aux;
				}
				else if (Casillas[i][j]->getAcor() == true) {
					Casilla aux = *Casillas[i][j];
					Casillas[i][j] = new Reina(true);
					*Casillas[i][j] = aux;
				};
			};
};
bool Tablero::elije(int x, int y)
{
	if (Casillas[x][y]->getMov() && !Casillas[x][y]->getLibre())
	{
		if (!Casillas[x][y]->getCap())
		{
			for (int i = 0; i < ml; i++)
				for (int j = 0; j < ml; j++)
					if (!Casillas[i][j]->getLibre() && Casillas[i][j]->getColor() == turno && Casillas[i][j]->getCap()) return false;
			chosenx = x;
			choseny = y;
			return true;
		}
		else
		{
			chosenx = x;
			choseny = y;//mueve sin capturar
			return true;
		};
	}
	else return false;// si no se puede mover(ni capturar)
};
bool Tablero::desplaza(int x, int y)
{
	if (!Casillas[x][y]->getLibre()||(x + y) % 2 == 1)return false;
	Casilla aux;
	if ((((x - chosenx) * (y - choseny)) == 4 || ((x - chosenx) * (y - choseny)) == -4) && (Casillas[chosenx][choseny]->getCap()))
	{

		if (((y - choseny) == (turno ? 2 : -2)) || Casillas[chosenx][choseny]->getAcor())//que sea dama o que sigua la direccion del jugador
		{
			if (Casillas[chosenx+(x - chosenx) / 2][choseny+(y - choseny) / 2]->getLibre() == false && Casillas[chosenx+(x - chosenx) / 2][choseny+(y - choseny) / 2]->getColor() != turno) 
			{
				//contener una ficha enemiga en la casilla del medio
				aux = Casillas[x][y];//copiar la casilla vacia
				*Casillas[(x - chosenx) / 2 + chosenx][(y - choseny) / 2 + choseny] = aux;//vaciar la ficha capturada
				*Casillas[x][y] = *Casillas[chosenx][choseny];//mover la ficha al destino
				*Casillas[chosenx][choseny] = aux;//vaciar el origen
				revisa();
				return true;
			}
		};

	}
	else if ((((x - chosenx) * (y - choseny)) == 1 || ((x - chosenx) * (y - choseny)) == -1) && (!Casillas[chosenx][choseny]->getCap()))
	{
		if ((y - choseny) == (turno ? 1 : -1) || Casillas[chosenx][choseny]->getAcor())
		{
			aux = *Casillas[x][y];//casilla vacia
			*Casillas[x][y] = *Casillas[chosenx][choseny];//mover hasta el destino
			*Casillas[chosenx][choseny] = aux;//vaciar el origen
			return true;
		};
	};

	return false;

};
void Tablero::destinos()
{
	for (int i = 0; i < 4; i++)destinox[i] = destinoy[i]=-1;
	Casilla aux[ml][ml];
	int contador = 0;
	for (int i = 0; i < ml; i++)for (int j = 0; j < ml; j++)aux[i][j] = *Casillas[i][j];//guardar el tablero
	for (int i = 0; i < ml; i++)for (int j = 0; j < ml; j++)
		if (desplaza(i, j))
		{
			destinox[contador] = i;
			destinoy[contador] = j;
			contador++;
			for (int i = 0; i < ml; i++)for (int j = 0; j < ml; j++)*Casillas[i][j] = aux[i][j];//resetear el tablero
		};
	revisa();
};
void Tablero::proceso(int x, int y)
{
	// funcionamiento del tablero
	revisa();
	if (elije(x, y))
	{
		elegido = true;
		destinos();
		return;
	};
	if (elegido)
	{
		revisa();
		if (desplaza(x, y))
		{
			elegido = false;
			if (Casillas[x][y]->getCap())turno = !turno;
			turno = !turno;
			revisa();
		};
	};
};
int Tablero::contador()
{
	Casilla aux[ml][ml];
	for (int i = 0; i < ml; i++)for (int j = 0; j < ml; j++)aux[i][j] = *Casillas[i][j];//guardar el tablero
	int contador = 0;
	for (int i = 0; i < ml; i++)for (int j = 0; j < ml; j++)
	{
		if (elije(i, j))
		{
			for (int i = 0; i < ml; i++)for (int j = 0; j < ml; j++)
				if (desplaza(i, j))
				{
					contador++;
					for (int i = 0; i < ml; i++)for (int j = 0; j < ml; j++)*Casillas[i][j] = aux[i][j];//resetear el tablero
				};
		};
	};
	return contador;
};
void Tablero::guardar() {
	FILE* file = fopen("partida.txt", "w");
	for (int i = 0; i < ml; i++)for (int j = 0; j < ml; j++)
	{
		if (Casillas[i][j]->getLibre())fprintf(file, "0 \n");
		else if (!Casillas[i][j]->getAcor()) {
			if (Casillas[i][j]->getColor())fprintf(file, "1 \n");
			else fprintf(file, "2 \n");
		}
		else
		{
			if (Casillas[i][j]->getColor())fprintf(file, "3 \n");
			else fprintf(file, "4 \n");
		};
	};
	if (turno)fprintf(file, "1 \n");
	else fprintf(file, "0 \n");
	fclose(file);
};
void Tablero::leer() {
	FILE* file = fopen("partida.txt", "r");
	char* buffer=new char ;
	for (int i = 0; i < ml; i++)for (int j = 0; j < ml; j++)
	{
		fscanf(file, "%s", buffer);
		if (buffer[0] == '0')Casillas[i][j]->setLibre(true);
		else {
			Casillas[i][j]->setLibre(false);
			if (buffer[0] == '1')
			{
				Casillas[i][j]->setColor(true);
				Casillas[i][j]->setAcor(false);
			}
			else if (buffer[0] == '2')
			{
				Casillas[i][j]->setColor(false);
				Casillas[i][j]->setAcor(false);
			}
			else if (buffer[0] == '3')
			{
				Casillas[i][j]->setColor(true);
				Casillas[i][j]->setAcor(true);
			}
			else if (buffer[0] == '4')
			{
				Casillas[i][j]->setColor(false);
				Casillas[i][j]->setAcor(true);
			}
		};
	};
	fscanf(file, "%s", buffer);
	if (buffer[0] == '1')turno = true;
	else turno = false;
	fclose(file);
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
