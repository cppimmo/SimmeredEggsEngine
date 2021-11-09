#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

struct mouse_t {
	
};
typedef struct mouse_t Mouse;

struct keyboard_t {

};
typedef struct keyboard_t Keyboard;

// void input_key_down(const SDL_keysym *const keysym);
// void input_key_up(const SDL_keysym *const keysym);
void input_mouse_button();

#endif // INPUT_H
