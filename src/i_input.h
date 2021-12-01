#ifndef __I_INPUT_H__
#define __I_INPUT_H__

#include "SDL2/SDL.h"
#include "SDL2/SDL_types.h"
#include "u_utility.h"

#include <stdlib.h>

struct mousewheel_t { // positive=right, negative=left
	Sint32 x; // horizontal scroll
	Sint32 y; // vertical scroll
	Uint32 direction; // see Remarks of SDL_MouseWheelEvent
};

struct mouse_t {
	Sint32 x; // x-coord relative to window
	Sint32 y;
	Sint32 xrel; // relative motion in horizontal direction
	Sint32 yrel;
	boolean buttonl; // left button and so on
	boolean buttonm; // true if pressed
	boolean buttonr;
	boolean buttonx1;
	boolean buttonx2; /* SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, SDL_BUTTON_RIGHT,
					     SDL_BUTTON_X1, SDL_BUTTON_X2 */
	struct mousewheel_t wheel;
};

struct keyboard_t {

};

struct controlleraxis_t {
	Uint16 x;
	Uint16 y;
};

struct controller_t { // axis range -32768 to 32767
    struct controlleraxis_t laxis;
	struct controlleraxis_t raxis;
	Uint16 ltrigger;
	Uint16 rtrigger;
	boolean buttons[16];
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

void I_OnMouseMotion(const SDL_MouseMotionEvent *event);
void I_OnMouseButtonDown(const SDL_MouseButtonEvent *event);
void I_OnMouseButtonUp(const SDL_MouseButtonEvent *event);
void I_OnMouseWheel(const SDL_MouseWheelEvent *event);
void I_OnKeyDown(const SDL_Keysym *key);
void I_OnKeyUp(const SDL_Keysym *key);
void I_OnTextEdit(const SDL_TextEditingEvent *event);
void I_OnTextInput(const SDL_TextInputEvent *event);
void I_OnControllerAxisMotion(const SDL_ControllerAxisEvent *event);
void I_OnControllerButtonDown(const SDL_ControllerButtonEvent *event);
void I_OnControllerButtonUp(const SDL_ControllerButtonEvent *event);
void I_OnControllerDeviceAdded(const SDL_ControllerDeviceEvent *event);
void I_OnControllerDeviceRemoved(const SDL_ControllerDeviceEvent *event);
void I_OnControllerDeviceRemapped(const SDL_ControllerDeviceEvent *event);

void I_UpdateKeyboardState(void);
boolean I_IsKeyDown(SDL_Keycode key);
boolean I_IsMouseButtonDown(Uint8 button);
struct mousewheel_t *I_GetMouseWheelState(void);
boolean I_IsControllerButtonDown(SDL_GameControllerButton button);
// these functions control buffer input
void I_KeyMark(void);
char *I_KeyPeek(void);
void I_KeyUnmark(void);

#endif
