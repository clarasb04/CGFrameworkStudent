#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 

Shader* shader;
Mesh quad;
int mode;
int tecla;

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
	//model_m.SetIdentity();
	//viewproject_m.
	textura = Texture::Get("images/fruits.png");
}

// Render one frame
void Application::Render(void)
{
	// ...
	mode = 5;
	tecla = 2;
	
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