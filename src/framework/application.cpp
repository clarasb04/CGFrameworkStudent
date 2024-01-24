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


	Image* save = new Image();
	save->LoadPNG("images/save.png");
	/*Image* black = new Image();
	//black->LoadPNG("images/black.png");
	Image* blue = new Image();
	//blue->LoadPNG("images/blue.png");
	Image* circle = new Image();
	//circle->LoadPNG("images/circle.png");
	Image* clear = new Image();
	clear->LoadPNG("images/clear.png");
	Image* cyan = new Image();
	//cyan->LoadPNG("images/cyan.png");
	Image* eraser = new Image();
	//eraser->LoadPNG("images/eraser.png");
	Image* green = new Image();
	//green->LoadPNG("images/green.png");
	Image* line = new Image();
	//line->LoadPNG("images/line.png");
	Image* load = new Image();
	load->LoadPNG("images/load.png");
	Image* pink = new Image();
	//pink->LoadPNG("images/pink.png");
	Image* rect = new Image();
	//rect->LoadPNG("images/rectangle.png");
	Image* red = new Image();
	//red->LoadPNG("images/red.png");


	b_clear =  Button(clear, 10, 10);
	b_load = Button(load, 52, 10);
	*/
	

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
	framebuffer.DrawImage(*b_save.imatge, b_save.x, b_save.y, FALSE);
	//framebuffer.DrawImage(*b_load.imatge, b_load.x, b_load.y, FALSE);




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