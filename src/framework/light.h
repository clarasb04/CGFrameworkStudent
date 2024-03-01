#pragma once

#include "framework.h"
#include "shader.h"
#include "texture.h"


#include <cmath> //for sqrt (square root) function
#include <math.h> //atan2
#include <cstring>



class Light
{
public:
	Vector3 position;
	Vector3 Id;
	Vector3 Is;


	Light();
	~Light();

private:

};

