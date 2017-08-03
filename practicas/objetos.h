//**************************************************************************
// Práctica 2 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include <math.h>
#include <string>
#include "jpg_imagen.hpp"

using namespace std;

const float AXIS_SIZE=5000;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void    draw_solido_sombreado_plano(float r, float g, float b);
void    draw_solido_sombreado_suave(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void    calcularNormalesCaras();
void	calcularNormalesVertices();

vector<_vertex3i> caras;
vector<_vertex2f> texturas;
vector<_vertex3f> normalesCaras;
vector<_vertex3f> normalesVertices;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase tetraedro
//*************************************************************************

class _tetraedro: public _triangulos3D
{
public:

	_tetraedro(float tam=1.0);
};

//*************************************************************************
// clase modeloPLY
//*************************************************************************

class _modeloPLY: public _triangulos3D
{
public:
	vector<float> puntos;
	vector<int> faces;

	_modeloPLY(float tam, char * fileName);
	void crearObjetoRevolucion(int n);
	void crearObjetoRevolucionConTexturas(int n);
	void crearObjetoBarrido(float Vx, float Vy, float Vz, float size);
	void usarCarasArchivoPLY();
};

//*************************************************************************
// clase modeloJerarquico
//*************************************************************************

class _modeloJerarquico: public _triangulos3D
{
public:
	int tamTorre;
	int tamPluma;

	_modeloJerarquico(int tam1, int tam2){
		tamTorre=tam1;
		tamPluma=tam2;
	};
	void drawModeloJerarquico(int tamTorre, int tamPluma, float movCarro, float movCable,int angulo);
};

//*************************************************************************
// clase luz
//*************************************************************************
class _luz
{
public:
	int nombre;
	char tipo;
	vector<float> valores;
	vector<float> pos;	

	_luz(int indice, char p, float x, float y, float z, float w){
		nombre=indice;
		tipo=p;
		valores.push_back(x);
		valores.push_back(y);
		valores.push_back(z);
		valores.push_back(w);
	};

	void activarLuzAmbiente();
	//void activarLuzDifusa();
	//void activarLuzEspecular();
	void posicion(float x, float y, float z, float w);
	void mover(int alfa, int beta);
	void desactivarLuzAmbiente();
};

//*************************************************************************
// clase textura
//*************************************************************************
class _textura
{
public:
	jpg::Imagen * pimg; //puntero a imagen
	vector<float> planoS;
	vector<float> planoT;
	vector<float> ambient;	
	vector<float> diffuse;
	vector<float> specular;
	float shininess;
	

	_textura(){
		pimg = NULL;
		planoS.push_back(0.0); planoT.push_back(0.0);
		planoS.push_back(0.0); planoT.push_back(1.0);
		planoS.push_back(1.0); planoT.push_back(0.0);
		planoS.push_back(0.0); planoT.push_back(0.0);
	};

	void cargarImagen(char * nombreImg){pimg = new jpg::Imagen(nombreImg);};
	void activar();
	void activarProcedural();
	void desactivar();
	void desactivarProcedural();
	void definirMaterial();
	void perla();
	void plasticoNegro();
};
