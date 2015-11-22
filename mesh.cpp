#include "mesh.h"

Mesh::Mesh(Shape* shape, int value) {

	this->GenerateFromShape(shape, value);

}

void Mesh::GenerateFromShape(Shape *shape, int value) {
	this->m_shape = shape;
	int centreX = shape->GetCenter().x;
	int centreY = shape->GetCenter().y;

	//équivalent à instanceOf circle
	Circle* circle = dynamic_cast<Circle*>(shape);
	if(circle != 0) {
		//shape est un cercle
		int radius=circle->GetRadius();

		this->m_height = 2*radius;
		this->m_width = 2*radius;

		//E,F,G,H, contour de la Mesh
		point_t *E = new point_t;
		point_t *F = new point_t;
		point_t *G = new point_t;
		point_t *H = new point_t;

		//Calcul des points contours de la mesh
		E->x = centreX - radius;
		E->y = centreY - radius;
		F->x = centreX + radius;
		F->y = centreY - radius;
		G->x = centreX + radius;
		G->y = centreY + radius;
		H->x = centreX - radius;
		H->y = centreY + radius;

		this->m_offset.x = E->x;
		this->m_offset.y = E->y;

		for(int y=E->y; y<=G->y; y++) {
			for(int x=E->x; x<=G->x; x++) {
				if(sqrt((E->y+radius-y)*(E->y+radius-y)+(E->x+radius-x)*(E->x+radius-x))<=radius) {
					this->m_data[(x-E->x)+((y*this->m_width)-E->y)] = value;
				} else {
					this->m_data[(x-E->x)+((y*this->m_width)-E->y)] = value;
				}
			}
		}

	} else {
		//shape est un rectangle constitué dans le sens horaire, A en haut à gauche, etc
		Rectangle* rectangle = dynamic_cast<Rectangle*>(shape);

		//angleDeg, unknown value
		float angleDeg = rectangle->GetAngle();
		if(angleDeg>=0) {
			while(angleDeg>=360) {
				angleDeg -= 360;
			}
		} else {
			while(angleDeg<=-360) {
				angleDeg += 360;
			}
			angleDeg = -angleDeg;
		}
		//angleDeg, normalized angle from 0 to 360 degrees
		//angleRad from 0 to -2*PI radians
		float angleRad = -angleDeg*M_PI/180;

		int height = rectangle->GetHeight();
		int width = rectangle->GetWidth();
		float diagonaleSur2 = sqrt(height*height+width*width)/2;
		//A,B,C,D, contour de la Shape
		point_t *A = new point_t;
		point_t *B = new point_t;
		point_t *C = new point_t;
		point_t *D = new point_t;
		//E,F,G,H, contour de la Mesh
		point_t *E = new point_t;
		point_t *F = new point_t;
		point_t *G = new point_t;
		point_t *H = new point_t;

		//On calcule les éleménts de rotation pour A
		angleRad+=atan2(height,width);
		float deltaX = diagonaleSur2*cos(angleRad);
		float deltaY = diagonaleSur2*sin(angleRad);
		//On effectue la rotation d'angle a
		A->x = centreX-deltaX;
		A->y = centreY-deltaY;

		//Calcul pour B
		angleRad+=(M_PI-2*atan2(height,width));
		deltaX = diagonaleSur2*cos(angleRad);
		deltaY = diagonaleSur2*sin(angleRad);
		//On effectue la rotation
		B->x = centreX-deltaX;
		B->y = centreY-deltaY;

		//Rotation de C
		angleRad+=2*atan2(height,width);
		deltaX = diagonaleSur2*cos(angleRad);
		deltaY = diagonaleSur2*sin(angleRad);
		//On effectue la rotation
		C->x = centreX-deltaX;
		C->y = centreY-deltaY;

		//Enfin rotation de D
		angleRad+=(M_PI-2*atan2(height,width));
		deltaX = diagonaleSur2*cos(angleRad);
		deltaY = diagonaleSur2*sin(angleRad);
		//On effectue la rotation
		D->x = centreX-deltaX;
		D->y = centreY-deltaY;

		((abs(A->x - C->x)>abs(B->x - D->x)) ? this->m_width=abs(A->x - C->x) : this->m_width=abs(B->x - D->x));
		((abs(A->y - C->y)>abs(B->y - D->y)) ? this->m_height=abs(A->y - C->y) : this->m_height=abs(B->y - D->y));

		this->m_offset.x = Min(A->x, B->x, C->x, D->x);
		this->m_offset.y = Min(A->y, B->y, C->y, D->y);

		//Calcul des points contours de la mesh
		E->x = this->m_offset.x;
		E->y = this->m_offset.y;
		F->x = Max(A->x, B->x, C->x, D->x);
		F->y = this->m_offset.y;
		G->x = F->x;
		G->y = Max(A->y, B->y, C->y, D->y);
		H->x = this->m_offset.x;
		H->y = G->y;

		//Point qui va parcourir la mesh
		point_t *pt = new point_t;
		for(int y=E->y; y<G->y; y++) {
			for(int x=E->x; x<G->x; x++) {
				pt->x=x; pt->y=y;
				if(IsPointInRect(pt,A,B,C,D,E,F,G,H,angleDeg)) {
					this->m_data[(x-E->x)+((y*this->m_width)-E->y)] = value;
				}
			}
		}
	}
}
void Mesh::Merge(Mesh* mesh) {
	//On part du principe que l'on merge la plus petite surface sur la map => this = map, mesh = objet à appliquer !!
	int i, j;
	for(i=0; i<mesh->GetWidth(); i++) {
		for(j=0; j<mesh->GetHeight(); j++) {
			cout<<mesh->m_data[i + mesh->GetWidth()*j];
			this->m_data[mesh->GetOffset().x + this->GetWidth()*mesh->GetOffset().y] = this->m_data[mesh->GetOffset().x + this->GetWidth()*mesh->GetOffset().y] || mesh->m_data[i + mesh->GetWidth()*j];
		}
	}
}

int Mesh::IsPointInRect(point_t *pt, point_t *A, point_t *B, point_t *C, point_t *D, point_t *E, point_t *F, point_t *G, point_t *H, float angleDeg) {
	if((angleDeg==0)||(angleDeg==90)||(angleDeg==180)||(angleDeg==270)) {
		return 1;
	} else if((angleDeg>0)&&(angleDeg<90)) {
		if(IsPointInTri(pt,A,B,E)||IsPointInTri(pt,B,C,F)||IsPointInTri(pt,C,D,G)||IsPointInTri(pt,A,D,H)) {
			return 0;
		} else {
			return 1;
		}
	} else if((angleDeg>90)&&(angleDeg<180)) {
		if(IsPointInTri(pt,A,B,H)||IsPointInTri(pt,B,C,E)||IsPointInTri(pt,C,D,F)||IsPointInTri(pt,A,D,G)) {
			return 0;
		} else {
			return 1;
		}
	} else if((angleDeg>180)&&(angleDeg<270)) {
		if(IsPointInTri(pt,A,B,G)||IsPointInTri(pt,B,C,H)||IsPointInTri(pt,C,D,E)||IsPointInTri(pt,A,D,F)) {
			return 0;
		} else {
			return 1;
		}
	} else if((angleDeg>270)&&(angleDeg<360)) {
		if(IsPointInTri(pt,A,B,F)||IsPointInTri(pt,B,C,G)||IsPointInTri(pt,C,D,H)||IsPointInTri(pt,A,D,E)) {
			return 0;
		} else {
			return 1;
		}
	} else {
		return 0;//throw new RuntimeError("Erreur, l'angle n'est pas compris entre 0 et 360 degrés !");
	}
}
int Mesh::IsPointInTri(point_t *pt, point_t *p1, point_t *p2, point_t *p3) {
	float TotalArea = CalcTriArea(p1,p2,p3);
	float Area1 = CalcTriArea(pt, p1, p2);
	float Area2 = CalcTriArea(pt, p2, p3);
	float Area3 = CalcTriArea(pt, p3, p1);

  if((Area1 + Area2 + Area3) > TotalArea)
    return 0;
  else
    return 1;
}
float Mesh::CalcRectArea(point_t *p1, point_t *p2, point_t *p3, point_t *p4) {
	  float det = 0.0f;
	  //Area = W * L
	  det = sqrt(((p1->x - p2->x) * (p1->x - p2->x)) + ((p1->y - p2->y) * (p1->y - p2->y))) * sqrt(((p3->x - p4->x) * (p3->x - p4->x)) + ((p3->y - p4->y) * (p3->y - p4->y)));
	  return det;
}
float Mesh::CalcTriArea(point_t *p1, point_t *p2, point_t *p3) {
	float det = 0.0f;
	det = ((p2->x - p1->x) * (p3->y - p1->y)) - ((p3->x - p1->x) * (p2->y - p1->y));
	return abs(det / 2.0f);
}

point_t Mesh::GetOffset() {
	return this->m_offset;
}
int Mesh::GetWidth() {
	return this->m_width;
}
int Mesh::GetHeight() {
	return this->m_height;
}
Shape* Mesh::GetShape() {
	return this->m_shape;
}
int* Mesh::GetData() {
	return this->m_data;
}

void Mesh::TerminalPrintMesh() {
	for(int y=this->m_offset.y;y<this->m_offset.y+this->m_height;y++) {
		for(int x=this->m_offset.x;x<this->m_offset.x+this->m_width;x++) {
			cout<<this->m_data[(x-this->m_offset.x)+((y*this->m_width)-m_offset.y)];
		}
		cout<<endl;
	}
}

int Mesh::Min(int a, int b, int c, int d) {
	if(a<b) {
		if(a<c) {
			if(a<d) {
				return a;
			} else {
				return d;
			}
		} else if(c<d) {
			return c;
		} else {
			return d;
		}
	} else if(b>c) {
		if(c>d) {
			return d;
		} else {
			return c;
		}
	} else if(b<d) {
		return b;
	} else {
		return d;
	}
}
int Mesh::Max(int a, int b, int c, int d) {
	if(a>b) {
		if(a>c) {
			if(a>d) {
				return a;
			} else {
				return d;
			}
		} else if(c>d) {
			return c;
		} else {
			return d;
		}
	} else if(b<c) {
		if(c<d) {
			return d;
		} else {
			return c;
		}
	} else if(b>d) {
		return b;
	} else {
		return d;
	}
}







