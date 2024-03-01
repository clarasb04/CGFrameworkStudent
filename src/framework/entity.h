#pragma once

#include "framework.h"
#include "mesh.h"
#include "main/includes.h"
#include "image.h"
#include "shader.h"
#include "texture.h"
#include "material.h"

class Entity {
	
public:
	Vector3 scale;
	Vector3 rot;
	Vector3 trans;
	float deg;
	Matrix44 scale_m;

	Shader* shader;
	
	Mesh malla;
	Matrix44 matriu;
	Material material;
	//constructor
	Entity();
	Entity(Mesh malla_entr, Vector3 trans, Vector3 rot, Vector3 scale, float deg);

	void Render(sUniformData u_data);
	void Update(float seconds_elapsed, float deg_s, float scale_max, float trans_s, bool rot_local, Vector3 eix_rot);
};