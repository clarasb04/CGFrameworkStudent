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

	
}

Application::~Application()
{
}


void Application::Init(void)
{
	std::cout << "Initiating app..." << std::endl;
	

	cam = Camera();
	cam.fov = PI;
	cam.near_plane = 0.01;
	cam.far_plane = 100;
	cam.aspect = 1;
	//cam.SetOrthographic(cam.left, cam.right, cam.top, cam.bottom, cam.near_plane, cam.far_plane);
	cam.SetPerspective(cam.fov, cam.aspect, cam.near_plane, cam.far_plane);
	Mesh prova_m;
	bool fet = prova_m.LoadOBJ("/meshes/lee.obj");
	if (fet) {
		std::cout << "fet " << std::endl;

	}
	prova = Entity();
	prova.malla = prova_m;
	

	
	
	
}

// Render one frame
void Application::Render(void)
{
	prova.Render(&framebuffer, &cam, Color::WHITE);

	framebuffer.Render();

	
}

// Called after render
void Application::Update(float seconds_elapsed)
{

}

//keyboard press event 
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{	
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
	switch(event.keysym.sym) {
		case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app

		case SDLK_1: {
			//Draw Lines
			key = 1;
			break;
		}
		case SDLK_2: {
			//Draw Rectangles
			key = 2;
			break;
		}
		case SDLK_3: {
			//Draw Cercles
			key = 3;

			break;
		}
		case SDLK_4: {
			//Draw Triangles
			key = 4;
	
			break;
		}
		case SDLK_5: {
			//Paint
			key = 5;
			break;
		}
		case SDLK_6: {
			//Animation
			key = 6;
			break;
		}
		case SDLK_f: {
			//Fill Shapes
			if (Fill) {
				Fill = FALSE;
			}
			else {
				Fill = TRUE;
			}
			break;
		}
		case SDLK_PLUS: {
			//Incrase Border
			Border += 1;
			break;
		}
		case SDLK_MINUS: {
			//Decrease Border
			if (Border > 1) {
				Border -= 1;
			}
			break;
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