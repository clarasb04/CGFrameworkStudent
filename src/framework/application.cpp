#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 
#include "entity.h"

Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	int w,h;
	SDL_GetWindowSize(window,&w,&h);

	this->mouse_state = 0;
	this->time = 0.f;
	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(nullptr);
	this->framebuffer.Resize(w, h);
	this->border_color = Color::WHITE;
	this->mouse_pressed = FALSE;
	this->num_punts = 0;
	this->property = 0;

	
}

Application::~Application()
{
}


void Application::Init(void)
{
	std::cout << "Initiating app..." << std::endl;
	

	cam = new Camera();
	cam->eye = Vector3(0, 0, -1);
	cam->center = Vector3(0, 0, 0);
	cam->up = Vector3(0, 1, 0);
	cam->fov = 45;
	cam->near_plane = 0.000001;
	cam->far_plane = 100;
	cam->aspect = 1;
	cam->SetPerspective(cam->fov, cam->aspect, cam->near_plane, cam->far_plane);

	cam->LookAt(cam->eye, cam->center, cam->up);
	//cam->SetOrthographic(cam->left, cam->right, cam->top, cam->bottom, cam->near_plane, cam->far_plane);
	Mesh cara1_m;
	cara1_m.LoadOBJ("/meshes/lee.obj");
	Mesh cara2_m;
	cara2_m.LoadOBJ("/meshes/cleo.obj");
	Mesh cara3_m;
	cara3_m.LoadOBJ("/meshes/anna.obj");
	cara1 = Entity(cara1_m, Vector3(0, 0, 2), Vector3(1, 0, 0), Vector3(1, 1, 1), PI/2);
	cara1.malla = cara1_m;
	cara2 = Entity(cara2_m, Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 1, 1), PI/2);
	cara2.malla = cara2_m;
	
	cara4 = Entity(cara1_m, Vector3(1, 0, 1), Vector3(0, 0.5f, 0), Vector3(1, 1, 0), PI/4);
	cara4.malla = cara1_m;
	
	cara3 = Entity(cara3_m, Vector3(0, 0.5f, 0), Vector3(0, 1, 0), Vector3(1, 1, 1), PI/2);
	cara3.malla = cara3_m; 
	
	
}

// Render one frame
void Application::Render(void)
{
	cara4.Render(&framebuffer, cam, Color::BLUE);
	cara2.Render(&framebuffer, cam, Color::PURPLE);
	cara3.Render(&framebuffer, cam, Color::GREEN);


	if (key == 1) {
		//un sol objecte
		cara1.Render(&framebuffer, cam, Color::WHITE);

	}
	if (key == 2) {
		//varis objectes animats
		//pues aqui lo de la animacio
		cara4.Render(&framebuffer, cam, Color::BLUE);
		cara2.Render(&framebuffer, cam, Color::PURPLE);
		cara3.Render(&framebuffer, cam, Color::GREEN);

		//actualitzar les matrius aqui? si volem que cada una sigui diferent no ho podem fer a la funcio update de entity no?
		

	}

	framebuffer.Render();

	
}

// Called after render
void Application::Update(float seconds_elapsed)
{
	cara2.Update(seconds_elapsed);
	cara3.Update(seconds_elapsed);
	cara4.Update(seconds_elapsed);
	

	framebuffer.Fill(Color::BLACK);
}

//keyboard press event 
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{	
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
	switch(event.keysym.sym) {
		case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app

		case SDLK_1: {
			//un objecte
			key = 1;
			break;
		}
		case SDLK_2: {
			//animacions
			key = 2;
			break;
		}
		case SDLK_o: {
			cam->SetOrthographic(cam->left, cam->right, cam->top, cam->bottom, cam->near_plane, cam->far_plane);
			framebuffer.Fill(Color::BLACK);
			break;
		}
		case SDLK_p: {
			cam->SetPerspective(cam->fov, cam->aspect, cam->near_plane, cam->far_plane);
			framebuffer.Fill(Color::BLACK);
			break;
		}
		case SDLK_n: {
			property = 0;
			break;
		}
		case SDLK_f: {
			property = 1;
			break;
		}
		case SDLK_MINUS: {
			if (property == 0) {
				if (cam->near_plane - 1 > 0) {
					cam->near_plane -= 1;
					cam->UpdateViewMatrix();
					cam->UpdateProjectionMatrix();
				}
			}
			else if (property == 1) {
				if (cam->far_plane - 1 > 0) {
					cam->far_plane -= 1;
					cam->UpdateViewMatrix();
					cam->UpdateProjectionMatrix();
				}
			}

		}
		case SDLK_PLUS: {
			if (property == 0) {
				cam->near_plane += 1;
				cam->UpdateViewMatrix();
				cam->UpdateProjectionMatrix();
			}
			else if (property == 1) {
				cam->far_plane += 1;
				cam->UpdateViewMatrix();
				cam->UpdateProjectionMatrix();
			}
		}

					
	}
}

void Application::OnMouseButtonDown( SDL_MouseButtonEvent event )
{
	
	if (event.button == SDL_BUTTON_LEFT) {
		mouse_start_x = mouse_position.x;
		mouse_start_y = mouse_position.y;
		mouse_pressed = TRUE;


	}

	
}

void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {
		mouse_end_x = mouse_position.x;
		mouse_end_y = mouse_position.y;
		mouse_pressed = FALSE;
	}
	switch(key){
	case 1: {
		framebuffer.DrawLineDDA(mouse_start_x, mouse_start_y, mouse_end_x, mouse_end_y, border_color, Border);
		break;
	}
	case 2: {
		framebuffer.DrawRect(mouse_start_x, mouse_start_y, mouse_end_x- mouse_start_x, mouse_end_y- mouse_start_y, border_color, Border, Fill, fill_color);
		break;
	}
	case 3: {
		int dx = mouse_start_x - mouse_end_x;
		int dy = mouse_start_y - mouse_end_y;
		int r = round(sqrt(dx * dx + dy * dy));
		framebuffer.DrawCircle(mouse_start_x, mouse_start_y, r, border_color, Border, Fill, fill_color);
		break;
	}
	case 4: {
		
	}

	}

	
	

	
}

void Application::OnMouseMove(SDL_MouseButtonEvent event)
{ 
	if (mouse_pressed == TRUE && key == 7) {
		
		framebuffer.DrawRect(mouse_position.x, mouse_position.y, Border, Border, Color::BLACK,
			1, TRUE, Color::BLACK);
		

	}
	if (mouse_pressed == TRUE && key == 5) {
		if (Fill == FALSE) {
			framebuffer.DrawRect(mouse_position.x, mouse_position.y, Border, Border, border_color,
				1, TRUE, border_color);
		}
		else {
			framebuffer.DrawLineDDA(mouse_start_x, mouse_start_y, mouse_position.x, mouse_position.y, fill_color, Border);
		}

	}
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