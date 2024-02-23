#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 
#include "entity.h"

Shader* shader;
Mesh quad;
Mesh cara1_m;
Entity cara1;

int mode=1;
int tecla=1;

Camera* cam;
Matrix44 model_m;
Matrix44 viewproject_m;

Texture* textura; 





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

	this->framebuffer.Resize(w, h);
}

Application::~Application()
{
}

void Application::Init(void)
{
	std::cout << "Initiating app..." << std::endl;
	quad.CreateQuad();
	shader = Shader::Get("shaders/quad.vs", "shaders/quad.fs");

	cam = new Camera();
	cam->eye = Vector3(0, 0, 2);
	cam->center = Vector3(0, 0, 0);
	cam->up = Vector3(0, 1, 0);
	cam->fov = 45;
	cam->near_plane = 0.01;
	cam->far_plane = 100;
	cam->aspect = 1;
	cam->SetOrthographic(cam->left, cam->right, cam->top, cam->bottom, cam->near_plane, cam->far_plane);
	cam->LookAt(cam->eye, cam->center, cam->up);

	
	cara1_m.LoadOBJ("/meshes/lee.obj");
	cara1 = Entity(cara1_m, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1), 0);



	//model_m.SetIdentity();
	//viewproject_m.
	textura = Texture::Get("images/fruits.png");
}

// Render one frame
void Application::Render(void)
{
	// ...
	
	shader->Enable();
	shader->SetUniform1("u_mode", mode);
	shader->SetUniform1("u_tecla", tecla);
	shader->SetFloat("u_height", this->window_height);
	shader->SetFloat("u_width", this->window_width);
 

	//shader->SetMatrix44("u_modelmatrix", model_m);
	//shader->SetMatrix44("u_viewprojection")
	shader->SetTexture("u_texture", textura);
	quad.Render();
	shader->Disable();
}

// Called after render
void Application::Update(float seconds_elapsed)
{

}

//keyboard press event 
void Application::OnKeyPressed(SDL_KeyboardEvent event)
{
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
	switch (event.keysym.sym) {
	case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app

	case SDLK_1: {
		tecla = 1;
		break;
	}
	case SDLK_2: {
		tecla = 2;
		break;
	}
	case SDLK_3: {
		tecla = 3;

		break;
	}
	case SDLK_4: {
		tecla = 4;

		break;
	}
	case SDLK_a: {
		mode = 1;

		break;
	}
	case SDLK_b: {
		mode = 2;

		break;
	}
	case SDLK_c: {
		mode = 3;

		break;
	}
	case SDLK_d: {
		mode = 4;

		break;
	}
	case SDLK_e: {
		mode = 5;

		break;
	}
	case SDLK_f: {
		mode = 6;

		break;
	}

		
	}
	
}

void Application::OnMouseButtonDown(SDL_MouseButtonEvent event)
{
	if (event.button == SDL_BUTTON_LEFT) {

	}
}

void Application::OnMouseButtonUp(SDL_MouseButtonEvent event)
{
	if (event.button == SDL_BUTTON_LEFT) {

	}
}

void Application::OnMouseMove(SDL_MouseButtonEvent event)
{

}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
	float dy = event.preciseY;

	// ...
}

void Application::OnFileChanged(const char* filename)
{
	Shader::ReloadSingleShader(filename);
}