#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 
#include "entity.h"
#include "material.h"

#pragma once


Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	this->mouse_state = 0;
	this->time = 0.f;
	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(nullptr);

	this->mouse_pressed_left = false;
	this->mouse_pressed_right = false;

	this->framebuffer.Resize(w, h);
	this->flags = Vector3(0);
}

Application::~Application()
{
}

void Application::Init(void)
{
	std::cout << "Initiating app..." << std::endl;
	//canviar el nom al fitxer quan els fem

	cam = new Camera();
	cam->eye = Vector3(0, 0, 2);
	cam->center = Vector3(0, 0, 0);
	cam->up = Vector3(0, 1, 0);
	cam->fov = 45;
	cam->near_plane = 0.01;
	cam->far_plane = 100;
	cam->aspect = this->window_height/ this->window_width;
	cam->SetOrthographic(cam->left, cam->right, cam->top, cam->bottom, cam->near_plane, cam->far_plane);
	cam->LookAt(cam->eye, cam->center, cam->up);

	Ia = Vector3(0.5f, 0.5f, 0.5f);

	cara1_m.LoadOBJ("/meshes/lee.obj");
	cara1 = Entity(cara1_m, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(3), 0);



	cara1.material = Material(Shader::Get("shaders/gouraud.vs", "shaders/gouraud.fs") , Texture::Get("/textures/lee_color_specular.tga"), Texture::Get("/textures/lee_normal.tga"), Vector3(0.3f, 0.3f, 0.3f), Vector3(0.8f, 0.8f, 0.8f), Vector3(0.5f, 0.5f, 0.5f), 10.0f );

	l1 = Light(Vector3(1.0f, 0.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
	l2 = Light(Vector3(-1.0, 0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));
	l3 = Light(Vector3(0.0, 0.0f, -1.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(1.0f, 0.0f, 1.0f));
	u_data.n_llums = 1;
	u_data.llum[1] = l2;
	u_data.llum[2] = l1;
	u_data.llum[3] = l3;
}

// Render one frame
void Application::Render(void)
{
	// ...
	
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL); 


	//tmb s'ha de pujar tots les flags de la interactivitat q calgui al shader
	u_data.n_llums = num_llums;
	u_data.Ia = this->Ia;
	u_data.view_proj_matrix = cam->GetViewProjectionMatrix();
	u_data.eye = cam->eye;
	u_data.flags = flags;
	cara1.Render(u_data);
	

	
	
}

// Called after render
void Application::Update(float seconds_elapsed)
{
	time += seconds_elapsed; 
}

//keyboard press event 
void Application::OnKeyPressed(SDL_KeyboardEvent event)
{
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
	switch (event.keysym.sym) {
	case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app

	case SDLK_g: {
		cara1.material = Material(Shader::Get("shaders/gouraud.vs", "shaders/gouraud.fs"), Texture::Get("/textures/lee_color_specular.tga"), Texture::Get("/textures/lee_normal.tga"), Vector3(0.3f, 0.3f, 0.3f), Vector3(0.8f, 0.8f, 0.8f), Vector3(0.5f, 0.5f, 0.5f), 10.0f);
		break;
	}
	case SDLK_p: {
		cara1.material = Material(Shader::Get("shaders/phong.vs", "shaders/phong.fs"), Texture::Get("/textures/lee_color_specular.tga"), Texture::Get("/textures/lee_normal.tga"), Vector3(0.3f, 0.3f, 0.3f), Vector3(0.8f, 0.8f, 0.8f), Vector3(0.5f, 0.5f, 0.5f), 20.0f);
		break;
	}
	case SDLK_n:{
		if (flags.z == 0) {
			flags.z = 1;
		}
		else {
			flags.z = 0;
		}
		break;
	}
	case SDLK_c: {
		if (flags.x == 0) {
			flags.x = 1;
		}
		else {
			flags.x = 0;
		}
		break;
	}
	case SDLK_s: {
		if (flags.y == 0) {
			flags.y = 1;
		}
		else {
			flags.y = 0;
		}
		break;
	}
	case SDLK_1: {
		num_llums = 1;
		break;
	}
	case SDLK_2: {
		num_llums = 2;
		break;
	}
	case SDLK_3: {
		num_llums = 3;
		break;
	}
	case SDLK_4: {
		num_llums = 4;
		break;
	}
	case SDLK_5: {
		num_llums = 5;
		break;
	}
	case SDLK_6: {
		num_llums = 6;
		break;
	}
	case SDLK_7: {
		num_llums = 7;
		break;
	}
	case SDLK_8: {
		num_llums = 8;
		break;
	}
	case SDLK_9: {
		num_llums = 9;
		break;
	}
	case SDLK_0: {
		num_llums = 0;
		break;
	}

	}
	
}

void Application::OnMouseButtonDown(SDL_MouseButtonEvent event)
{
	if (event.button == SDL_BUTTON_LEFT) {
		mouse_pressed_left = true;
		past_mouse = mouse_position;
	}
	if (event.button == SDL_BUTTON_RIGHT) {
		mouse_pressed_right = true; 
		past_mouse = mouse_position;
	}
}

void Application::OnMouseButtonUp(SDL_MouseButtonEvent event)
{
	if (event.button == SDL_BUTTON_LEFT) {
		mouse_pressed_left = false;

	}
	if (event.button == SDL_BUTTON_RIGHT) {
		mouse_pressed_right = false;

	}
}

void Application::OnMouseMove(SDL_MouseButtonEvent event)
{
	if (mouse_pressed_left) {
		Vector2 delt = mouse_position - past_mouse;
		past_mouse = mouse_position;
		cam->Orbit(-delt.x*0.01 , Vector3::UP);
		cam->Orbit(-delt.y*0.01 , Vector3::RIGHT);
	}
	if (mouse_pressed_right) {
		float dx;
		float dy;
		Vector2 delt = mouse_position - past_mouse;
		past_mouse = mouse_position;
		dx = delt.x * 2 / (framebuffer.width * PI); 
		dy = delt.y * 2 / (framebuffer.height * PI); 
		Vector3 mov = cam->GetLocalVector(Vector3(dx, -dy, 0));
		cam->center = operator+(cam->center, mov);
		cam->LookAt(cam->eye, cam->center, cam->up);
	}
}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
	float dy = event.preciseY;
	cam->Zoom(dy < 0 ? 1.1 : 0.9);
}

void Application::OnFileChanged(const char* filename)
{
	Shader::ReloadSingleShader(filename);
}