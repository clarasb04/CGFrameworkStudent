
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

Material::Material(Shader* sh, Texture* t, const Vector3& ka, const Vector3& kd, const Vector3& ks, float s)
{
	this->shader = sh;
	this->textura = t;
	this->Ka = ka;
	this->Kd = kd;
	this->Ks = ks;
	this->shinness = s;
}

void Material::Enable(const sUniformData& u_data) {
	this->shader->Enable();
	this->shader->SetMatrix44("u_viewprojection", u_data.view_proj_matrix);
	this->shader->SetMatrix44("u_model", u_data.model);
	this->shader->SetUniform3("u_ia", u_data.Ia);
	this->shader->SetUniform3("u_id", u_data.llum.Id);
	this->shader->SetUniform3("u_is", u_data.llum.Is);
	this->shader->SetUniform3("u_eye", u_data.eye);
	this->shader->SetUniform3("u_light", u_data.llum.position);
	this->shader->SetTexture("u_textura", textura);
	this->shader->SetUniform3("u_Ka", Ka);
	this->shader->SetUniform3("u_Kd", Kd);
	this->shader->SetUniform3("u_Ks", Ks);
	this->shader->SetUniform1("u_shinness", shinness);

}

void Material::Disable() {
	this->shader->Disable();
}

