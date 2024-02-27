#pragma once

#include "framework.h"
#include "shader.h"
#include "texture.h"


#include <cmath> //for sqrt (square root) function
#include <math.h> //atan2
#include <cstring>

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

	void Enable();
	void Disable();



};

Material::Material()
{
}

Material::~Material()
{
}