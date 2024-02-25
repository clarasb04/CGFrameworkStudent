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
Shader* raster;
Matrix44 model_m;
Matrix44 viewproject_m;

Texture* textura; 
Texture* text_cara;





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
}

Application::~Application()
{
}

void Application::Init(void)
{
	std::cout << "Initiating app..." << std::endl;
	quad.CreateQuad();
	shader = Shader::Get("shaders/quad.vs", "shaders/quad.fs");
	raster = Shader::Get("shaders/raster.vs", "shaders/raster.fs");

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

	

	cara1_m.LoadOBJ("/meshes/lee.obj");
	cara1 = Entity(cara1_m, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(3), 0);

	textura = Texture::Get("images/fruits.png");
	text_cara = Texture::Get("/textures/lee_color_specular.tga");
	cara1.textura = text_cara;

}

// Render one frame
void Application::Render(void)
{
	// ...
	if (tecla == 1 || tecla == 2 || tecla==3) {
		shader->Enable();
		shader->SetUniform1("u_mode", mode);
		shader->SetUniform1("u_tecla", tecla);
		shader->SetFloat("u_height", this->window_height);
		shader->SetFloat("u_width", this->window_width);
		shader->SetFloat("u_sec", time);

	
		shader->SetTexture("u_texture", textura);
		quad.Render();
		shader->Disable();
	}
	else {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL); 

		raster->Enable();
		raster->SetMatrix44("u_viewprojection", cam->viewprojection_matrix);
		cara1.Render(raster);
		raster->Disable();

	}
	
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
	case SDLK_DOWN: {
		cam->Orbit(-0.25, Vector3::RIGHT);
		break;
	}
	case SDLK_UP: {
		cam->Orbit(0.25, Vector3::RIGHT);
		break;
	}
	case SDLK_RIGHT: {
		cam->Orbit(-0.25, Vector3::UP);
		break;
	}
	case SDLK_LEFT: {
		cam->Orbit(0.25, Vector3::UP);
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
	// ...
}

void Application::OnFileChanged(const char* filename)
{
	Shader::ReloadSingleShader(filename);
}