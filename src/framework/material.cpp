
#include "material.h"
#include "entity.h"
#include "shader.h"
#pragma once


Material::Material()
{
	this->Ka = 0;
	this->Kd = 0;
	this->Ks = 0;
	this->shinness = 0;
}

Material::~Material()
{
}

void Material::Enable(const sUniformData& u_data) {
	shader->Enable();
	this->shader->SetMatrix44("u_viewprojection", u_data.view_proj_matrix);
	this->shader->SetMatrix44("u_model", u_data.model);
	this->shader->SetTexture("u_textura", textura); //mirar si es el punter a la pract anterior
	this->shader->SetUniform3("u_Ka", Ka);
	this->shader->SetUniform3("u_Kd", Kd);
	this->shader->SetUniform3("u_Ks", Ks);
	this->shader->SetUniform1("u_shinness", shinness);

}

void Material::Disable() {
	this->shader->Disable();
}

