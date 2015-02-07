
#pragma once
#ifndef h_mesh
#define h_mesh

#include "shape.h"
#include "point.h"
#include <iostream>
#include <cmath>
using namespace std;

class Mesh 
{
public:
	Mesh(Shape *shape, int value);

	void GenerateFromShape(Shape *shape, int value);
	void Merge(Mesh* mesh);

	int IsPointInRect(point_t *pt, point_t *A, point_t *B, point_t *C, point_t *D, point_t *E, point_t *F, point_t *G, point_t *H, float angleDeg);
	int IsPointInTri(point_t *pt, point_t *p1, point_t *p2, point_t *p3);
	float CalcTriArea(point_t *p1, point_t *p2, point_t *p3);
	float CalcRectArea(point_t *p1, point_t *p2, point_t *p3, point_t *p4);

	point_t GetOffset();
	int GetWidth();
	int GetHeight();
	Shape* GetShape();

	void TerminalPrintMesh();

	int Min(int a, int b, int c, int d);
	int Max(int a, int b, int c, int d);

private:
	int m_data[1000];
	
	point_t m_offset;
	int m_width;
	int m_height;
	Shape* m_shape;
};


#endif
