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
#include <algorithm>

#pragma once

Entity::Entity() {
	matriu = Matrix44();
	malla = Mesh();
}

Entity::Entity(Mesh malla_entr, Vector3 trans, Vector3 rot, Vector3 scale, float deg) {
	malla = malla_entr;
	matriu.SetIdentity();
	scale_m.SetIdentity();
	scale_m.M[0][0] = scale.x;
	scale_m.M[1][1] = scale.y;
	scale_m.M[2][2] = scale.z;
	matriu.Rotate(deg, rot);
	matriu.Translate(trans.x, trans.y, trans.z);
	matriu = scale_m * matriu;
	
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
		
		p1.x = ((p1.x + 1)/2) * (framebuffer->width - 1);
		p2.x = ((p2.x + 1) / 2) * (framebuffer->width - 1);
		p3.x = ((p3.x + 1) / 2) * (framebuffer->width - 1);

		p1.y = ((p1.y + 1) / 2) * (framebuffer->height - 1);
		p2.y = ((p2.y + 1) / 2) * (framebuffer->height - 1);
		p3.y = ((p3.y + 1) / 2) * (framebuffer->height - 1);
		
		

		if (negZ1 || negZ2 || negZ3) {
			continue;
		}

		framebuffer->DrawLineDDA(p1.x, p1.y, p2.x, p2.y, c, 1);
		framebuffer->DrawLineDDA(p3.x, p3.y, p2.x, p2.y, c, 1);
		framebuffer->DrawLineDDA(p1.x, p1.y, p3.x, p3.y, c, 1);
		


	}
	
	
	
	
}

void Entity::Update(float seconds_elapsed) {
	/*
	float velocitat_rotacio = 10.0f;
	matriu.Rotate((velocitat_rotacio * seconds_elapsed ), rot);
	matriu.Translate(trans.x, trans.y, trans.z);
	*/
	float velocitat_rotacio = 1.0f;
	matriu.Rotate(velocitat_rotacio * seconds_elapsed, Vector3(0.0f, 1.0f, 0.0f));



	float velocitat_moviment = 1.0f;  // Ajusta a la velocitat desitjada.
	matriu.Translate(velocitat_moviment * seconds_elapsed, 0.0f, 0.0f);
	/*scale_m.M[0][0] = scale.x;
	scale_m.M[1][1] = scale.y;
	scale_m.M[2][2] = scale.z;
	matriu.Rotate((velocitat_rotacio * seconds_elapsed), rot);
	matriu.Translate(trans.x* seconds_elapsed, trans.y* seconds_elapsed, trans.z* seconds_elapsed);
	matriu = scale_m * matriu;
	*/
	
	
	
	
}

