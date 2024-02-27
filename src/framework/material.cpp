
#include "material.h"
#include "entity.h"
#include "shader.h"
#pragma once

void Material::Enable() {
	this->shader->Enable();
}

void Material::Disable() {
	this->shader->Disable();
}

