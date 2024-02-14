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
	this->mouse_pressed_left = FALSE;
	this->mouse_pressed_right = FALSE;
	this->num_punts = 0;
	this->property = 0;

	this->occlusions = true;
	this->interpolated = true;
	this->mesh = true;
	 
	this->zBuffer.Resize(w, h);

	
}

Application::~Application()
{
}


void Application::Init(void)
{
	std::cout << "Initiating app..." << std::endl;
	

	cam = new Camera();
	cam->eye = Vector3(0, 0, 2);
	cam->center = Vector3(0, 0, 0);
	cam->up = Vector3(0, 1, 0);
	cam->fov = 45;
	cam->near_plane = 0.000001;
	cam->far_plane = 100;
	cam->aspect = 1;
	//holaaaaaaa
	perspective = true;
	cam->SetPerspective(cam->fov, cam->aspect, cam->near_plane, cam->far_plane);
	cam->LookAt(cam->eye, cam->center, cam->up);
	
	Mesh cara1_m;
	cara1_m.LoadOBJ("/meshes/lee.obj");
	Mesh cara2_m;
	cara2_m.LoadOBJ("/meshes/cleo.obj");

	Mesh cara3_m;
	cara3_m.LoadOBJ("/meshes/anna.obj");
	cara1 = Entity(cara1_m, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1), 0);
	cara22 = Entity(cara2_m, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1), 0);
	cara22.setRenderMode(Entity::eRenderMode::TRIANGLES_INTERPOLATED);
	cara2 = Entity(cara2_m, Vector3(0, -0.5f, 0), Vector3(0, 1, 0), Vector3(1.5, 1.5, 1.5), PI/2);

	cara3 = Entity(cara3_m, Vector3(0, 0.5f, 0), Vector3(0, 1, 0), Vector3(1, 1, 1), PI/2);
	
	cara4 = Entity(cara1_m, Vector3(0, 0, 0.25f), Vector3(0, 0.5f, 0), Vector3(1, 1, 0), PI/4);
	
	Image t1;
	t1.LoadTGA("/textures/lee_color_specular.tga");
	t1.FlipY(); 
	cara1.texture = t1;

	Image t2;
	t2.LoadTGA("/textures/cleo_color_specular.tga");
	t2.FlipY();
	cara22.texture = t2;
	
}

// Render one frame
void Application::Render(void)
{
	zBuffer.Fill(1000000.0f);

	if (key == 1) {
		//un sol objecte
		cara22.Render(&framebuffer, cam, Color::WHITE, TRUE, &zBuffer);

	}
	if (key == 2) {
		//varis objectes animats
		cara4.Render(&framebuffer, cam, Color::BLUE, FALSE, &zBuffer);
		cara2.Render(&framebuffer, cam, Color::PURPLE, FALSE, &zBuffer);
		cara3.Render(&framebuffer, cam, Color::GREEN, FALSE, &zBuffer);
	}

	framebuffer.Render();

	
}

// Called after render
void Application::Update(float seconds_elapsed)
{
	cara2.Update(seconds_elapsed, 1.0f, 0, 0, true, Vector3(0.0f, 1.0f, 0.0f));
	cara3.Update(seconds_elapsed, 1.5f, 0 ,1.0f, false, Vector3(0.0f, 1.0f, 0.0f));
	cara4.Update(seconds_elapsed, 2,0,0, false, Vector3(1.0f, 0.0f, 0.0f));

	framebuffer.Fill(Color::BLACK);
}

//keyboard press event 
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{	
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
	switch(event.keysym.sym) {
		case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app

		case SDLK_1: {
			key = 1;
			break;
		}
		case SDLK_2: {
			key = 2;
			break;
		}
		case SDLK_o: {
			perspective = false;
			cam->SetOrthographic(cam->left, cam->right, cam->top, cam->bottom, cam->near_plane, cam->far_plane);
			framebuffer.Fill(Color::BLACK);
			break;
		}
		case SDLK_p: {
			perspective = true;
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
		case SDLK_v: {
			if (cam->fov > 1.0f) {
				cam->fov -= 0.01;
				cam->SetPerspective(cam->fov, cam->aspect, cam->near_plane, cam->far_plane); 

			}
			break;
		}
		case SDLK_b: {
			if (cam->fov < 150.0f) {
				cam->fov += 0.01;
				cam->SetPerspective(cam->fov, cam->aspect, cam->near_plane, cam->far_plane); 

			}
			break;
		}
		case SDLK_MINUS:{
			if (property == 0) {
				cam->near_plane = cam->near_plane - 0.25f;
				if (perspective) {
					cam->SetPerspective(cam->fov, cam->aspect, cam->near_plane, cam->far_plane);
				}
				else {
					cam->SetOrthographic(cam->left, cam->right, cam->top, cam->bottom, cam->near_plane, cam->far_plane);
				}
			}
			else if (property == 1) {
				cam->far_plane -= 0.25f;
				if (perspective) {
					cam->SetPerspective(cam->fov, cam->aspect, cam->near_plane, cam->far_plane);
				}
				else {
					cam->SetOrthographic(cam->left, cam->right, cam->top, cam->bottom, cam->near_plane, cam->far_plane);
				}
				
			}
			break;
		}
		case SDLK_PLUS:{
			if (property == 0) {
				cam->near_plane += 0.25f;
				if (perspective) {
					cam->SetPerspective(cam->fov, cam->aspect, cam->near_plane, cam->far_plane);
				}
				else {
					cam->SetOrthographic(cam->left, cam->right, cam->top, cam->bottom, cam->near_plane, cam->far_plane);
				}
			}
			else if (property == 1) {
				cam->far_plane += 0.25f;
				if (perspective) {
					cam->SetPerspective(cam->fov, cam->aspect, cam->near_plane, cam->far_plane);
				}
				else {
					cam->SetOrthographic(cam->left, cam->right, cam->top, cam->bottom, cam->near_plane, cam->far_plane);
				}
			}
			break;
		}
		case SDLK_c: {
			if (!interpolated) {

				interpolated = true;
			}
			else {

				interpolated = false;
			}
			break;
		}
		case SDLK_z: {
			if (!occlusions) {

				occlusions = true;
			}
			else {

				occlusions = false;
			}
			break;
		}
		case SDLK_i: {
			if (!mesh) {

				mesh = true;
			}
			else {

				mesh = false;
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
		mouse_pressed_left = TRUE;
	}
	if (event.button == SDL_BUTTON_RIGHT) {
		mouse_start_x = mouse_position.x;
		mouse_start_y = mouse_position.y;
		mouse_pressed_right = TRUE;
	}

	
}

void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {
		mouse_end_x = mouse_position.x;
		mouse_end_y = mouse_position.y;
		mouse_pressed_left = FALSE;

	}
	if (event.button == SDL_BUTTON_RIGHT) {
		mouse_end_x = mouse_position.x;
		mouse_end_y = mouse_position.y;
		mouse_pressed_right = FALSE;
		
	}
	

	
	

	
}

void Application::OnMouseMove(SDL_MouseButtonEvent event)
{ 
	if (mouse_pressed_left) {
		float dx;
		float dy;
		dx = mouse_delta.x * 4 / (framebuffer.width * PI);
		dy = mouse_delta.y * 4 / (framebuffer.height * PI);
		Matrix44 rotate_eye_x, rotate_eye_y;
		Matrix44 translation_center; 
		translation_center.SetTranslation(-cam->center.x,-cam->center.y, -cam->center.z );
		rotate_eye_x.SetRotation(-dx, Vector3(0, 1.0f, 0));
		rotate_eye_y.SetRotation(-dy, Vector3(1.0f, 0, 0));
		
		cam->eye = operator*(translation_center, cam->eye);
		cam->eye = operator*(rotate_eye_x, cam->eye);
		cam->eye = operator*(rotate_eye_y, cam->eye);

		translation_center.SetTranslation(cam->center.x, cam->center.y, cam->center.z);
		cam->eye = operator*(translation_center, cam->eye);

		cam->LookAt(cam->eye, cam->center, cam->up);
	}
	if (mouse_pressed_right) {
		float dx;
		float dy;
		dx = mouse_delta.x * 2 / (framebuffer.width * PI); 
		dy = mouse_delta.y * 2 / (framebuffer.height * PI);
		Vector3 mov = cam->GetLocalVector(Vector3(dx, -dy, 0)); 
		cam->center = operator+(cam->center, mov);
		cam->LookAt(cam->eye, cam->center, cam->up); 
		
		
	}
}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
	float dy = event.preciseY;
	Vector3 dir = operator-(cam->center, cam->eye);
	dir = operator*(0.1f * dy, dir);
	Matrix44 translation_zoom;
	translation_zoom.SetTranslation(dir.x, dir.y, dir.z);
	cam->eye = operator*(translation_zoom, cam->eye);
	cam->LookAt(cam->eye, cam->center, cam->up);

}

void Application::OnFileChanged(const char* filename)
{ 
	Shader::ReloadSingleShader(filename);
}