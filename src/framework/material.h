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
	Light llum[10];
	Vector3 eye;
	Vector3 flags;
	int n_llums;

};



class Material
{
public:
	Shader* shader;
	Texture* textura_s;
	Texture* textura_n;
	Vector3 Ka;
	Vector3 Kd;
	Vector3 Ks;
	float shinness;
	


	Material();
	Material(Shader* shader, Texture* t_s, Texture* t_n, const Vector3& ka, const Vector3& kd, const Vector3& ks, float s);

	void Enable(const sUniformData& u_data, int l);
	void Disable();




};



