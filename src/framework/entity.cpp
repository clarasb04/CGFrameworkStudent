#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "GL/glew.h"
#include "../extra/picopng.h"
#include "image.h"
#include "utils.h"
#include "camera.h"
#include "mesh.h"
#include "entity.h"

#pragma once

Entity::Entity() {
	matriu = Matrix44();
	malla = Mesh();
}

Entity::Entity(Mesh malla_entr, Matrix44 matriu_entr) {
	malla = malla_entr;
	matriu = matriu_entr;
}

void Entity::Render(Image* framebuffer, Camera* camera, const Color& c) {
	
	for (int i = 0; i < malla.GetVertices().size(); i+=3) {
		Vector3 p1;
		Vector3 p2;
		Vector3 p3;
		p1 = operator *(matriu, malla.GetVertices()[i]);
		p2 = operator *(matriu, malla.GetVertices()[i+1]);
		p3 = operator *(matriu, malla.GetVertices()[i+2]);


		bool negZ1, negZ2, negZ3; 
		p1 = camera->ProjectVector(p1, negZ1);
		p2 = camera->ProjectVector(p2, negZ2); 
		p3 = camera->ProjectVector(p3, negZ3);

		if (negZ1 && negZ2 && negZ3) {
			framebuffer->DrawLineDDA(p1.x, p1.y, p2.x, p2.y, c, 1);
			framebuffer->DrawLineDDA(p3.x, p3.y, p2.x, p2.y, c, 1);
			framebuffer->DrawLineDDA(p1.x, p1.y, p3.x, p3.y, c, 1);
		}


	}
	
	
	
	
}

