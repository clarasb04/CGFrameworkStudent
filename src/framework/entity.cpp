#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "GL/glew.h"
#include "../extra/picopng.h"
#include "image.h"
#include "utils.h"
#include "camera.h"
#include "mesh.h"
#include "entity.h"
#include "material.h"
#include "shader.h"
#include <algorithm>

#pragma once

Entity::Entity() {
	matriu = Matrix44();
	malla = Mesh();
	material = Material();
}

Entity::Entity(Mesh malla_entr, Vector3 trans, Vector3 rot, Vector3 scale, float deg) {
	malla = malla_entr;
	matriu.SetIdentity();
	scale_m.SetIdentity();
	scale_m.M[0][0] = scale.x;
	scale_m.M[1][1] = scale.y;
	scale_m.M[2][2] = scale.z;
	matriu.Rotate(deg, rot);
	matriu.Translate(trans.x, trans.y, trans.z);
	matriu = scale_m * matriu;
	
}



void Entity::Render(sUniformData u_data) {
	u_data.model = this->matriu;
	material.Enable(u_data);
	malla.Render();
	material.Disable();
	
}

void Entity::Update(float seconds_elapsed, float deg_s, float scale_max, float trans_s, bool rot_local, Vector3 eix_rot) {
	
	if (deg_s != 0) {
		if (rot_local) {
			matriu.RotateLocal(deg_s * seconds_elapsed, eix_rot);

		}
		else {
			matriu.Rotate(deg_s * seconds_elapsed, eix_rot);

		}
	}

	if (trans_s != 0) {
		matriu.Translate(trans_s * seconds_elapsed, 0.0f, 0.0f);
	}
		
	
	
}

