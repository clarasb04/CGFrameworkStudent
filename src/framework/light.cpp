#include "light.h"


Light::Light()
{
	position=0;
	Id=0;
	Is=0;
}

Light::Light(const Vector3& p, const Vector3& id, const Vector3& is)
{
	this->position = p;
	this->Id = id;
	this->Is = is;
}