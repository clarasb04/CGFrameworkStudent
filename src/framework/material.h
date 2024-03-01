#pragma once

#include "framework.h"
#include "shader.h"
#include "texture.h"
#include "light.h"


#include <cmath> //for sqrt (square root) function
#include <math.h> //atan2
#include <cstring>
struct sUniformData
{
	Matrix44 view_proj_matrix;
	Matrix44 model;
	Vector3 Ia;

};



class Material
{
public:
	Shader* shader;
	Texture* textura;
	Vector3 Ka;
	Vector3 Kd;
	Vector3 Ks;
	float shinness;


	Material();
	~Material();

	void Enable(const sUniformData& u_data);
	void Disable();




};

Material::Material()
{
}

Material::~Material()
{
}

