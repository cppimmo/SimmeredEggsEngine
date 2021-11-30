#ifndef __G_INPUT_H__
#define __G_INPUT_H__

#include "SDL2/SDL.h"
#include "SDL2/SDL_types.h"
#include "u_utility.h"

#include <stdlib.h>

struct mouse_t {
	Sint32 x; // x-coord relative to window
	Sint32 y;
	Sint32 xrel; // relative motion in horizontal direction
	Sint32 yrel;
	boolean button_l; // left button and so on
	boolean button_m; // true if pressed
	boolean button_r;
	boolean button_x1;
	boolean button_x2;
	struct mouse_wheel_t { // postivie=right, negative=left
		Sint32 x; // horizontal scroll
		Sint32 y; // vertical scroll
		Uint32 direction; // see Remarks on SDL_MouseWheelEvent
	} wheel;
};

struct keyboard_t {

};

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

void G_OnMouseMotion(const SDL_MouseMotionEvent *event);
void G_OnMouseButtonDown(const SDL_MouseButtonEvent *event);
void G_OnMouseButtonUp(const SDL_MouseButtonEvent *event);
void G_OnMouseWheel(const SDL_MouseWheelEvent *event);
void G_OnKeyDown(const SDL_Keysym *key);
void G_OnKeyUp(const SDL_Keysym *key);
void G_OnTextEdit(const SDL_TextEditingEvent *event);
void G_OnTextInput(const SDL_TextInputEvent *event);
void G_OnControllerAxisMotion(const SDL_ControllerAxisEvent *event);
void G_OnControllerButtonDown(const SDL_ControllerButtonEvent *event);
void G_OnControllerButtonUp(const SDL_ControllerButtonEvent *event);
void G_OnControllerDeviceAdded(const SDL_ControllerDeviceEvent *event);
void G_OnControllerDeviceRemoved(const SDL_ControllerDeviceEvent *event);
void G_OnControllerDeviceRemapped(const SDL_ControllerDeviceEvent *event);

boolean G_IsKeyDown(void);
boolean G_IsMouseButtonDown(void);
// these functions control buffer input
void G_KeyMark(void);
char *G_KeyPeek(void);
void G_KeyUnmark(void);

#endif
