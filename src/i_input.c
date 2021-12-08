/* =============================================================================
** SimmeredEggsEngine, file: i_input.c Created 12/6/2021
**
** Copyright 2021 Brian Hoffpauir TX, USA
** All rights reserved.
**
** Redistribution and use of this source file, with or without modification, is
** permitted provided that the following conditions are met:
**
** 1. Redistributions of this source file must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
**
** THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR IMPLIED
** WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
** MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO
** EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
** OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
** ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** =============================================================================
**/
#include "i_input.h"

#define KEY_BUFFER_SIZE 1024

static float AxisNormalize(const float value, const float min, const float max);
static float AxisDeadzone(float value, const float maxval, const float deadzone);

static boolean iskeymark = false;
static char keybuffer[KEY_BUFFER_SIZE];
static Uint8 *keystates;
static size_t keystatelen;
static struct mouse_t mouse = {
	.pos.x = 0,
	.pos.y = 0,
	.pos.xrel = 0,
	.pos.yrel = 0,
	.buttonl = false,
	.buttonm = false,
	.buttonr = false,
	.buttonx1 = false,
	.buttonx2 = false,
	.wheel.x = 0,
	.wheel.y = 0,
	.wheel.direction = 0,
};

static struct keyboard_t keyboard;

static struct controller_t controller = {
	.laxis.x = 0,
	.laxis.y = 0,
	.raxis.x = 0,
	.raxis.y = 0,
	.ltrigger = 0,
	.rtrigger = 0,
	.buttons = {
		SDL_RELEASED,SDL_RELEASED,SDL_RELEASED,
		SDL_RELEASED,SDL_RELEASED,SDL_RELEASED,
		SDL_RELEASED,SDL_RELEASED,SDL_RELEASED,
		SDL_RELEASED,SDL_RELEASED,SDL_RELEASED,
		SDL_RELEASED,SDL_RELEASED,SDL_RELEASED,
		SDL_RELEASED,
	},
};

void I_OnMouseMotion(const SDL_MouseMotionEvent *event) {
	mouse.pos.x = event->x;
	mouse.pos.y = event->y;
	mouse.pos.xrel = event->xrel;
	mouse.pos.yrel = event->yrel;
}

void I_OnMouseButtonDown(const SDL_MouseButtonEvent *event) {
	mouse.pos.x = event->x;
	mouse.pos.y = event->y;
	switch (event->button) {
	case SDL_BUTTON_LEFT:
		mouse.buttonl = true;
		break;
    case SDL_BUTTON_MIDDLE:
		mouse.buttonm = true;
		break;
	case SDL_BUTTON_RIGHT:
		mouse.buttonr = true;
		break;
	case SDL_BUTTON_X1:
		mouse.buttonx1 = true;
		break;
	case SDL_BUTTON_X2:
		mouse.buttonx2 = true;
		break;
	}
}

void I_OnMouseButtonUp(const SDL_MouseButtonEvent *event) {
	mouse.pos.x = event->x;
	mouse.pos.y = event->y;
	switch (event->button) {
	case SDL_BUTTON_LEFT:
		mouse.buttonl = false;
		break;
    case SDL_BUTTON_MIDDLE:
		mouse.buttonm = false;
		break;
	case SDL_BUTTON_RIGHT:
		mouse.buttonr = false;
		break;
	case SDL_BUTTON_X1:
		mouse.buttonx1 = false;
		break;
	case SDL_BUTTON_X2:
		mouse.buttonx2 = false;
		break;
	}
}

void I_OnMouseWheel(const SDL_MouseWheelEvent *event) {
	mouse.wheel.x = event->x;
	mouse.wheel.y = event->y;
	mouse.wheel.direction = event->direction;
}

void I_OnKeyDown(const SDL_Keysym *key) {
	if (iskeymark) {
		if (key->sym == SDLK_BACKSPACE) {
			// remove the last character from the buffer

		} else if (key->sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
			// SDL_SetClipboardText( some const char *);

		} else if (key->sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
			// buffer = SDL_GetClipboardText();

		}
	}
}

void I_OnKeyUp(const SDL_Keysym *key) {

}

void I_OnTextEdit(const SDL_TextEditingEvent *event) {

}

void I_OnTextInput(const SDL_TextInputEvent *event) {
	if (!(SDL_GetModState() & KMOD_CTRL && (event->text[0] == 'c' ||
		event->text[0] == 'C' || event->text[0] == 'v' ||
	    event->text[0] == 'V'))) {

	}
}

void I_OnControllerAxisMotion(const SDL_ControllerAxisEvent *event) {
	switch (event->axis) {
	case SDL_CONTROLLER_AXIS_LEFTX:
		controller.laxis.x = event->value;
		break;
	case SDL_CONTROLLER_AXIS_LEFTY:
		controller.laxis.y = event->value;
		break;
	case SDL_CONTROLLER_AXIS_RIGHTX:
		controller.raxis.x = event->value;
		break;
	case SDL_CONTROLLER_AXIS_RIGHTY:
		controller.raxis.y = event->value;
		break;
	case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
		controller.ltrigger = event->value;
		break;
	case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
		controller.rtrigger = event->value;
		break;
	case SDL_CONTROLLER_AXIS_MAX:
		break;
	}
}

inline void I_OnControllerButtonDown(const SDL_ControllerButtonEvent *event) {
	controller.buttons[event->button] = true;
}

inline void I_OnControllerButtonUp(const SDL_ControllerButtonEvent *event) {
	controller.buttons[event->button] = false;
}

void I_OnControllerDeviceAdded(const SDL_ControllerDeviceEvent *event) {

}

void I_OnControllerDeviceRemoved(const SDL_ControllerDeviceEvent *event) {

}

void I_OnControllerDeviceRemapped(const SDL_ControllerDeviceEvent *event) {

}

inline void I_UpdateKeyboardState(void) {
	keystates = SDL_GetKeyboardState(&keystatelen);
}

inline boolean I_IsKeyDown(SDL_Keycode key) {
	//if (key < 0 || key > keystatelen - 1)
	//	return false;
	return keystates[key];
}

inline boolean I_IsMouseButtonDown(Uint8 button) {
	switch (button) {
	case SDL_BUTTON_LEFT:
		return mouse.buttonl;
		break;
	case SDL_BUTTON_MIDDLE:
		return mouse.buttonm;
		break;
	case SDL_BUTTON_RIGHT:
		return mouse.buttonr;
		break;
	case SDL_BUTTON_X1:
		return mouse.buttonx1;
		break;
	case SDL_BUTTON_X2:
		return mouse.buttonx2;
		break;
	default:
		return false;
	}
}

inline struct mousewheel_t *I_GetMouseWheelState(void) {
	return &mouse.wheel;
}

inline struct mousepos_t *I_GetMousePos(void) {
	return &mouse.pos;
}

inline boolean I_IsControllerButtonDown(SDL_GameControllerButton button) {
	return controller.buttons[button];
}

// start taking text input
inline void I_KeyMark(void) {
	SDL_StartTextInput();
	iskeymark = true;
}

// retrieve text input buffer
char *I_KeyPeek(void) {
	return NULL;
}

// stop taking text input
inline void I_KeyUnmark(void) {
	SDL_StopTextInput();
	iskeymark = false;
}

inline static float AxisNormalize(const float value, const float min,
								  const float max) {
	const float average = (min + max) / 2.0f;
	const float range = (max - min) / 2.0f;
	return (value - average) / range;
}

#define DEADZONE_MIN(a,b) (((a)<(b))?(a):(b))
#define DEADZONE_MAX(a,b) (((a)>(b))?(a):(b))

static float AxisDeadzone(float value, const float maxval,
						  const float deadzone) {
	if (value < -(deadzone)) {
		value += deadzone;
		// increase negative values to remove deadzone discontinuity
	} else if (value > deadzone) {
		value -= deadzone;
		// decrease positive values to remove deadzone discontinuity
	} else
		return 0.0f;
	const float normalized = value / (maxval - deadzone);
	return DEADZONE_MAX(-1.0f, DEADZONE_MIN(normalized, 1.0f));
}

