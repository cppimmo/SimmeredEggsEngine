#ifndef INPUT_H
#define INPUT_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_types.h"
#include <stdlib.h>
#include <stdbool.h>

struct mouse_t {
	Sint32 x; // x-coord relative to window
	Sint32 y;
	Sint32 xrel; // relative motion in horizontal direction
	Sint32 yrel;
	bool button_l; // left button and so on
	bool button_m; // true if pressed
	bool button_r;
	bool button_x1;
	bool button_x2;
	struct mouse_wheel_t { // postivie=right, negative=left
		Sint32 x; // horizontal scroll
		Sint32 y; // vertical scroll
		Uint32 direction; // see Remarks on SDL_MouseWheelEvent
	} wheel;
};
typedef struct mouse_t Mouse;

struct keyboard_t {

};
typedef struct keyboard_t Keyboard;

struct controller_axis_t {
	Uint16 x;
	Uint16 y;
};

struct controller_t { // axis range -32768 to 32767
    struct controller_axis_t axis_l;
	struct controller_axis_t axis_r;
	Uint16 trigger_l;
	Uint16 trigger_r;
	Uint8 button[16];
	/* SDL_CONTROLLER_BUTTON_INVALID 0, SDL_CONTROLLER_BUTTON_A 1
	 SDL_CONTROLLER_BUTTON_B 2, SDL_CONTROLLER_BUTTON_X 3
	 SDL_CONTROLLER_BUTTON_Y 4, SDL_CONTROLLER_BUTTON_BACK 5
	 SDL_CONTROLLER_BUTTON_GUIDE 6, SDL_CONTROLLER_BUTTON_START 7
	 SDL_CONTROLLER_BUTTON_LEFTSTICK 8, SDL_CONTROLLER_BUTTON_RIGHTSTICK 9
	 SDL_CONTROLLER_BUTTON_LEFTSHOULDER 10, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER 11
	 SDL_CONTROLLER_BUTTON_DPAD_UP 12, SDL_CONTROLLER_BUTTON_DPAD_DOWN 13
	 SDL_CONTROLLER_BUTTON_DPAD_LEFT 14, SDL_CONTROLLER_BUTTON_DPAD_RIGHT 15
	 SDL_CONTROLLER_BUTTON_MAX */
};
typedef struct controller_t Controller;

void on_mouse_motion(const SDL_MouseMotionEvent *event);
void on_mouse_button_down(const SDL_MouseButtonEvent *event);
void on_mouse_button_up(const SDL_MouseButtonEvent *event);
void on_mouse_wheel(const SDL_MouseWheelEvent *event);
void on_key_down(const SDL_Keysym *key);
void on_key_up(const SDL_Keysym *key);
void on_text_edit(const SDL_TextEditingEvent *event);
void on_text_input(const SDL_TextInputEvent *event);
void on_controller_axis_motion(const SDL_ControllerAxisEvent *event);
void on_controller_button_down(const SDL_ControllerButtonEvent *event);
void on_controller_button_up(const SDL_ControllerButtonEvent *event);
void on_controller_device_added(const SDL_ControllerDeviceEvent *event);
void on_controller_device_removed(const SDL_ControllerDeviceEvent *event);
void on_controller_device_remapped(const SDL_ControllerDeviceEvent *event);

bool is_key_down();
bool is_mb_down();
// these functions control buffer input
void key_mark();
char *key_peek();
void key_unmark();

#endif // INPUT_H
