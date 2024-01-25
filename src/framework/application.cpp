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
	this->border_color = Color::WHITE;

	
}

Application::~Application()
{
}


void Application::Init(void)
{
	std::cout << "Initiating app..." << std::endl;
	
	
	particleSystem.Init();
	
	

	
	Image* save = new Image();
	save->LoadPNG("images/save.png");
	Image* black = new Image();
	black->LoadPNG("images/black.png");
	Image* blue = new Image();
	blue->LoadPNG("images/blue.png");
	Image* circle = new Image();
	circle->LoadPNG("images/circle.png");
	Image* clear = new Image();
	clear->LoadPNG("images/clear.png");
	Image* cyan = new Image();
	cyan->LoadPNG("images/cyan.png");
	Image* eraser = new Image();
	eraser->LoadPNG("images/eraser.png");
	Image* green = new Image();
	green->LoadPNG("images/green.png");
	Image* line = new Image();
	line->LoadPNG("images/line.png");
	Image* load = new Image();
	load->LoadPNG("images/load.png");
	Image* pink = new Image();
	pink->LoadPNG("images/pink.png");
	Image* rect = new Image();
	rect->LoadPNG("images/rectangle.png");
	Image* red = new Image();
	red->LoadPNG("images/red.png");
	Image* white = new Image();
	white->LoadPNG("images/white.png");
	Image* triang = new Image();
	triang->LoadPNG("images/triangle.png");
	Image* yell = new Image();
	yell->LoadPNG("images/yellow.png");


	b_clear =  Button(clear, 10, 10);
	b_load = Button(load, 52, 10);
	b_save = Button(save, 94, 10);
	b_eraser = Button(eraser, 136, 10);
	b_line = Button(line, 178, 10);
	b_rect = Button(rect, 220, 10);
	b_circle = Button(circle, 262, 10);
	b_triang = Button(triang, 304, 10);
	b_black = Button(black, 346, 10);
	b_white = Button(white, 388, 10);
	b_pink = Button(pink, 430, 10);
	b_yell = Button(yell, 472, 10);
	b_green = Button(green, 514, 10);
	b_red = Button(red, 556, 10);
	b_blue = Button(blue, 598, 10);
	b_cyan = Button(cyan, 640, 10);
	
	
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
	


	framebuffer.DrawRect(0, 0,1280, 52, Color::GRAY, 1, TRUE, Color::GRAY); 
	framebuffer.DrawImage(*b_save.imatge, b_save.x, b_save.y, FALSE);  
	framebuffer.DrawImage(*b_load.imatge, b_load.x, b_load.y, FALSE); 
	framebuffer.DrawImage(*b_clear.imatge, b_clear.x, b_clear.y, FALSE);  
	framebuffer.DrawImage(*b_eraser.imatge, b_eraser.x, b_eraser.y, FALSE); 
	framebuffer.DrawImage(*b_line.imatge, b_line.x, b_line.y, FALSE); 
	framebuffer.DrawImage(*b_rect.imatge, b_rect.x, b_rect.y, FALSE); 
	framebuffer.DrawImage(*b_circle.imatge, b_circle.x, b_circle.y, FALSE); 
	framebuffer.DrawImage(*b_triang.imatge, b_triang.x, b_triang.y, FALSE); 
	framebuffer.DrawImage(*b_black.imatge, b_black.x, b_black.y, FALSE); 
	framebuffer.DrawImage(*b_white.imatge, b_white.x, b_white.y, FALSE); 
	framebuffer.DrawImage(*b_pink.imatge, b_pink.x, b_pink.y, FALSE); 
	framebuffer.DrawImage(*b_yell.imatge, b_yell.x, b_yell.y, FALSE); 
	framebuffer.DrawImage(*b_green.imatge, b_green.x, b_green.y, FALSE); 
	framebuffer.DrawImage(*b_red.imatge, b_red.x, b_red.y, FALSE); 
	framebuffer.DrawImage(*b_blue.imatge, b_blue.x, b_blue.y, FALSE);  
	framebuffer.DrawImage(*b_cyan.imatge, b_cyan.x, b_cyan.y, FALSE); 



	framebuffer.Render();
	
	switch (key) {
	
	case 6: {
		particleSystem.Render(&framebuffer);
		break;
	}
	}
	

	
}

// Called after render
void Application::Update(float seconds_elapsed)
{
	particleSystem.Update(seconds_elapsed); 

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
			particleSystem.Init();
			break;
		}
		case SDLK_f: {
			//Fill Shapes
			Fill = true;
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

		if (b_clear.IsMouseInside(mouse_position)) {
			for (int i = 0; i < 1280; i++) {
				for (int j = 0; j < 720; j++) {
					framebuffer.SetPixelSafe(i, j, Color::BLACK);
				}
			}
		}
		else if(b_load.IsMouseInside(mouse_position)){

		}
		else if (b_save.IsMouseInside(mouse_position)) {
			framebuffer.SaveTGA("images/dibuix_sense_titol.tga");
		}
		else if (b_load.IsMouseInside(mouse_position)) {
			framebuffer.LoadTGA("images/dibuix_sense_titol.tga");
		}



		else if (b_black.IsMouseInside(mouse_position)) {
			border_color = Color::BLACK;
		}
		else if (b_white.IsMouseInside(mouse_position)) {
			border_color = Color::WHITE;
		}
		else if (b_pink.IsMouseInside(mouse_position)) {
			border_color = Color::PURPLE;
		}
		else if (b_yell.IsMouseInside(mouse_position)) {
			border_color = Color::YELLOW;
		}
		else if (b_green.IsMouseInside(mouse_position)) {
			border_color = Color::GREEN;
		}
		else if (b_red.IsMouseInside(mouse_position)) {
			border_color = Color::RED;
		}
		else if (b_blue.IsMouseInside(mouse_position)) {
			border_color = Color::BLUE;
		}
		else if (b_cyan.IsMouseInside(mouse_position)) {
			border_color = Color::CYAN;
		}
		else if (b_line.IsMouseInside(mouse_position)) {
			key = 1;
		}
		else if (b_rect.IsMouseInside(mouse_position)) {
			key = 2;
		}
		else if (b_circle.IsMouseInside(mouse_position)) {
			key = 3;
		}
		else if (b_triang.IsMouseInside(mouse_position)) {
			key = 4;
		}


		else if (key == 4) {
			punt[0] = Vector2(mouse_start_x, mouse_start_y);
			punt[1] = Vector2(event.x, event.y); //no ho agafa beeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee		
		}

	}
	
}

void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {
		mouse_end_x = mouse_position.x;
		mouse_end_y = mouse_position.y;
	}
	switch(key){
	case 1: {
		framebuffer.DrawLineDDA(mouse_start_x, mouse_start_y, mouse_end_x, mouse_end_y, border_color, Border);
		break;
	}
	case 2: {
		framebuffer.DrawRect(mouse_start_x, mouse_start_y, mouse_end_x- mouse_start_x, mouse_end_y- mouse_start_y, border_color, Border, Fill, Color::RED);
		break;
	}
	case 3: {
		framebuffer.DrawCircle(mouse_start_x, mouse_start_y, (mouse_start_x - mouse_end_x), border_color, Border, Fill, Color::RED);
		break;
	}
	case 4: {
		punt[2] = Vector2(event.x, event.y);
		framebuffer.DrawTriangle(punt[0], punt[1], punt[2], border_color, Border, Fill, Color::GREEN);
		break;
	}

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