/*  
	+ This class encapsulates the application, is in charge of creating the data, getting the user input, process the update and render.
*/

#pragma once

#include "main/includes.h"
#include "framework.h"
#include "image.h"

class Application
{
public:

	int key;
	int mouse_start_x = 0;
	int mouse_start_y = 0;
	int mouse_end_x = 0;
	int mouse_end_y = 0;
	bool Fill = false;
	int Border = 1;
	Vector2 punt[3] = { {0,0},{0,0},{0,0} };
	int num_punts;
	Color border_color;
	Color fill_color;


	// Window

	SDL_Window* window = nullptr;
	int window_width;
	int window_height;

	float time;

	// Input
	const Uint8* keystate;
	int mouse_state; // Tells which buttons are pressed
	Vector2 mouse_position; // Last mouse position
	Vector2 mouse_delta; // Mouse movement in the last frame

	void OnKeyPressed(SDL_KeyboardEvent event);
	void OnMouseButtonDown(SDL_MouseButtonEvent event);
	void OnMouseButtonUp(SDL_MouseButtonEvent event);
	void OnMouseMove(SDL_MouseButtonEvent event);
	void OnWheel(SDL_MouseWheelEvent event);
	void OnFileChanged(const char* filename);

	// CPU Global framebuffer
	Image framebuffer;

	// Constructor and main methods
	Application(const char* caption, int width, int height);
	~Application();

	void Init( void );
	void Render( void );
	void Update( float dt );

	// Other methods to control the app
	void SetWindowSize(int width, int height) {
		glViewport( 0,0, width, height );
		this->window_width = width;
		this->window_height = height;
	}

	Vector2 GetWindowSize()
	{
		int w,h;
		SDL_GetWindowSize(window,&w,&h);
		return Vector2(float(w), float(h));
	}
	Button b_save;
	Button b_load;
	Button b_clear;
	Button b_eraser;
	Button b_line;
	Button b_rect;
	Button b_circle;
	Button b_triang;
	Button b_black;
	Button b_white;
	Button b_pink;
	Button b_yell;
	Button b_red;
	Button b_blue;
	Button b_cyan;
	Button b_green;
	Button b_pintar;
	Button b_fill;

	bool mouse_pressed;

	ParticleSystem particleSystem;
};
