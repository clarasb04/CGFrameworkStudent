#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 

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

}

Application::~Application()
{
}


void Application::Init(void)
{
	std::cout << "Initiating app..." << std::endl;
	//particleSystem.Init();


	Image* toolbar_img = new Image();
	toolbar_img->LoadPNG("images/toolbar.png");
	






	b1 =  Button(toolbar_img, 0, 0);
	

}

// Render one frame
void Application::Render(void)
{
	// ...
	/*
	int x = 600;
	int y = 400;
	Vector2 p0(200, 200);
	Vector2 p1(500, 400);
	Vector2 p2(600, 600);
	
	framebuffer.Fill(Color::BLACK);
	framebuffer.DrawRect(x, y, 400, 300, Color::GREEN, 15, TRUE);

	

	framebuffer.Render();
	*/
	//particleSystem.Render(&framebuffer);
	framebuffer.DrawImage(*b1.imatge, b1.x, b1.y, FALSE);



	framebuffer.Render();
}

// Called after render
void Application::Update(float seconds_elapsed)
{
	//particleSystem.Update(seconds_elapsed);

}

//keyboard press event 
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
	switch(event.keysym.sym) {
		case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app

		case SDLK_0:;
		/*
		case SDLK_1: framebuffer.DrawLineDDA();
		case SDLK_2: framebuffer.DrawRect();
		case SDLK_3: framebuffer.DrawRect();
		case SDLK_4: framebuffer.DrawTriangle();
		
		*/



		
	}
}

void Application::OnMouseButtonDown( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {

	}
}

void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
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