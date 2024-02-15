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
#include <algorithm>

#pragma once

Entity::Entity() {
	matriu = Matrix44();
	malla = Mesh();
	texture = Image();
}

void Entity::setRenderMode(eRenderMode m) {
	mode = m;
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



void Entity::Render(Image* framebuffer, Camera* camera, const Color& c, bool zBuf_flag, FloatImage* zBuf, bool textur) {
	
	for (int i = 0; i < malla.GetVertices().size(); i+=3) {
		Vector3 p1;
		Vector3 p2;
		Vector3 p3;
		p1 = operator *(matriu, malla.GetVertices()[i]);
		p2 = operator *(matriu, malla.GetVertices()[i+1]);
		p3 = operator *(matriu, malla.GetVertices()[i+2]);

		Vector3 dist_p1 = camera->eye - p1;
		Vector3 dist_p2 = camera->eye - p2;
		Vector3 dist_p3 = camera->eye - p3;
		Vector3 zetas = Vector3(sqrt(dist_p1.x * dist_p1.x + dist_p1.y * dist_p1.y + dist_p1.z * dist_p1.z),
			sqrt(dist_p2.x * dist_p2.x + dist_p2.y * dist_p2.y + dist_p2.z * dist_p2.z),
			sqrt(dist_p3.x * dist_p3.x + dist_p3.y * dist_p3.y + dist_p3.z * dist_p3.z));

		bool negZ1, negZ2, negZ3; 
		p1 = camera->ProjectVector(p1, negZ1);
		p2 = camera->ProjectVector(p2, negZ2);
		p3 = camera->ProjectVector(p3, negZ3);
		
		p1.x = ((p1.x + 1)/2) * (framebuffer->width - 1);
		p2.x = ((p2.x + 1) / 2) * (framebuffer->width - 1);
		p3.x = ((p3.x + 1) / 2) * (framebuffer->width - 1);

		p1.y = ((p1.y + 1) / 2) * (framebuffer->height - 1);
		p2.y = ((p2.y + 1) / 2) * (framebuffer->height - 1);
		p3.y = ((p3.y + 1) / 2) * (framebuffer->height - 1);
		
		

		if (negZ1 || negZ2 || negZ3) {
			continue;
		}

		Vector2 uv0 = malla.GetUVs()[i];
		Vector2 uv1 = malla.GetUVs()[i+1];
		Vector2 uv2 = malla.GetUVs()[i+2];
		
		
		

		//framebuffer->DrawTriangleInterpolated(Vector3(p1.x, p1.y, p1.z), Vector3(p2.x, p2.y, p2.z), Vector3(p3.x, p3.y, p3.z ), Color::GREEN, Color::BLUE, Color::RED, zBuf, );
		//framebuffer->DrawLineDDA(p1.x, p1.y, p2.x, p2.y, c, 1);
		//framebuffer->DrawLineDDA(p3.x, p3.y, p2.x, p2.y, c, 1);
		//framebuffer->DrawLineDDA(p1.x, p1.y, p3.x, p3.y, c, 1);
		switch (mode) {
		case eRenderMode::POINTCLOUD:
			framebuffer->SetPixelSafe(p1.x, p1.y, c);
			framebuffer->SetPixelSafe(p2.x, p2.y, c);
			framebuffer->SetPixelSafe(p3.x, p3.y, c);

			break;

		case eRenderMode::WIREFRAME:
			framebuffer->DrawLineDDA(p1.x, p1.y, p2.x, p2.y, c, 1);
			framebuffer->DrawLineDDA(p3.x, p3.y, p2.x, p2.y, c, 1);
			framebuffer->DrawLineDDA(p1.x, p1.y, p3.x, p3.y, c, 1);
			break;

		case eRenderMode::TRIANGLES:
			framebuffer->DrawTriangle(Vector2(p1.x, p1.y), Vector2(p2.x, p2.y), Vector2(p3.x, p3.y), c, 1, TRUE, c);
			break;

		case eRenderMode::TRIANGLES_INTERPOLATED:
			if (textur) {
				framebuffer->DrawTriangleInterpolated(Vector3(p1.x, p1.y, zetas.x), Vector3(p2.x, p2.y, zetas.y), Vector3(p3.x, p3.y, zetas.z), Color::RED, Color::BLUE, Color::GREEN, zBuf, &texture, uv0, uv1, uv2, zBuf_flag);
			}
			else {
				framebuffer->DrawTriangleInterpolated(Vector3(p1.x, p1.y, zetas.x), Vector3(p2.x, p2.y, zetas.y), Vector3(p3.x, p3.y, zetas.z), Color::RED, Color::BLUE, Color::GREEN, zBuf, nullptr, uv0, uv1, uv2, zBuf_flag);
			}
			break;
		}
		
	}
	
	
	
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

