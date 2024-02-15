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
	this->textur = true;
	 
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
	cara1.setRenderMode(Entity::eRenderMode::TRIANGLES_INTERPOLATED);

	cara2 = Entity(cara2_m, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1), 0);
	cara2.setRenderMode(Entity::eRenderMode::TRIANGLES_INTERPOLATED);

	cara3 = Entity(cara3_m, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1), 0);
	cara3.setRenderMode(Entity::eRenderMode::TRIANGLES_INTERPOLATED);

	cara1m = Entity(cara1_m, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1), 0);
	cara1m.setRenderMode(Entity::eRenderMode::TRIANGLES_INTERPOLATED);

	cara2m = Entity(cara2_m, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1), 0);
	cara2m.setRenderMode(Entity::eRenderMode::TRIANGLES_INTERPOLATED);

	cara3m = Entity(cara3_m, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1), 0);
	cara3m.setRenderMode(Entity::eRenderMode::TRIANGLES_INTERPOLATED);
	
	
	Image t1;
	t1.LoadTGA("/textures/lee_color_specular.tga");
	t1.FlipY(); 
	Image t2; 
	t2.LoadTGA("/textures/cleo_color_specular.tga"); 
	t2.FlipY(); 
	Image t3; 
	t3.LoadTGA("/textures/anna_color_specular.tga"); 
	t3.FlipY();

	Image t1_n;
	t1_n.LoadTGA("/textures/lee_normal.tga");
	t1_n.FlipY();
	Image t2_n;
	t2_n.LoadTGA("/textures/cleo_normal.tga");
	t2_n.FlipY();
	Image t3_n;
	t3_n.LoadTGA("/textures/anna_normal.tga");
	t3_n.FlipY();

	cara1.texture = t1;
	cara2.texture = t2;
	cara3.texture = t3;
	cara1m.texture = t1_n;
	cara2m.texture = t2_n;
	cara3m.texture = t3_n;
}

// Render one frame
void Application::Render(void)
{
	zBuffer.Fill(FLT_MAX); 

	cara1.Render(&framebuffer, cam, Color::WHITE, occlusions, &zBuffer, textur);

	framebuffer.Render();

}

// Called after render
void Application::Update(float seconds_elapsed)
{

	framebuffer.Fill(Color::BLACK);
}

//keyboard press event 
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{	
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
	switch(event.keysym.sym) {
		case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app

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
				cara1.setRenderMode(Entity::eRenderMode::TRIANGLES);
				cara2.setRenderMode(Entity::eRenderMode::TRIANGLES);
				cara3.setRenderMode(Entity::eRenderMode::TRIANGLES); 
				cara1m.setRenderMode(Entity::eRenderMode::TRIANGLES); 
				cara2m.setRenderMode(Entity::eRenderMode::TRIANGLES); 
				cara3m.setRenderMode(Entity::eRenderMode::TRIANGLES);
				interpolated = true;
			}
			else {
				cara1.setRenderMode(Entity::eRenderMode::TRIANGLES_INTERPOLATED); 
				cara2.setRenderMode(Entity::eRenderMode::TRIANGLES_INTERPOLATED); 
				cara3.setRenderMode(Entity::eRenderMode::TRIANGLES_INTERPOLATED); 
				cara1m.setRenderMode(Entity::eRenderMode::TRIANGLES_INTERPOLATED); 
				cara2m.setRenderMode(Entity::eRenderMode::TRIANGLES_INTERPOLATED); 
				cara3m.setRenderMode(Entity::eRenderMode::TRIANGLES_INTERPOLATED);  
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
		case SDLK_t: {
			if (!textur) {
				textur = true;
			}
			else {
				textur = false;
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