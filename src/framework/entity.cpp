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
	mesh = Mesh();
}

Entity::Entity(Mesh malla_entr, Matrix44 matriu_entr) {
	malla = malla_entr;
	matriu = matriu_entr;
}

void Entity::Render(Image* framebuffer, Camera* camera, const Color& c) {
	std::vector<Vector3>& vert = malla.GetVertices();
	for (int i = 0; i < vert.size(); i++) {
		malla.GetVertices()[i] = matriu * vert[i];
	}
}

