
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

Material::Material(Shader* sh, Texture* t_s, Texture* t_n, const Vector3& ka, const Vector3& kd, const Vector3& ks, float s)
{
	this->shader = sh;
	this->textura_s = t_s;
	this->textura_n = t_n;
	this->Ka = ka;
	this->Kd = kd;
	this->Ks = ks;
	this->shinness = s;
}

void Material::Enable(const sUniformData& u_data, int l) {
	this->shader->Enable();
	this->shader->SetMatrix44("u_viewprojection", u_data.view_proj_matrix);
	this->shader->SetMatrix44("u_model", u_data.model);
	this->shader->SetUniform3("u_ia", u_data.Ia);
	this->shader->SetUniform3("u_id", u_data.llum[l].Id);
	this->shader->SetUniform3("u_is", u_data.llum[l].Is);
	this->shader->SetUniform3("u_eye", u_data.eye);
	this->shader->SetUniform3("u_light", u_data.llum[l].position);
	this->shader->SetTexture("u_textura_s", textura_s);
	this->shader->SetTexture("u_textura_n", textura_n);
	this->shader->SetUniform3("u_Ka", Ka);
	this->shader->SetUniform3("u_Kd", Kd);
	this->shader->SetUniform3("u_Ks", Ks);
	this->shader->SetUniform1("u_shinness", shinness);
	this->shader->SetUniform3("u_flags", u_data.flags);
	this->shader->SetUniform1("u_num_llum", l);
}

void Material::Disable() {
	this->shader->Disable();
}

