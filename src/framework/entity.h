#pragma once

#include "framework.h"
#include "mesh.h"
#include "main/includes.h"
#include "image.h"

class Entity {
	
public:
	Mesh malla;
	Matrix44 matriu;
	//constructor
	Entity();
	Entity(Mesh malla_entr, Matrix44 matriu_entr);

	void Render(Image* framebuffer, Camera* camera, const Color& c);
	void Update(float seconds_elapsed);
};