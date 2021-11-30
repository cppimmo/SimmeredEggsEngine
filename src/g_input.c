#include "g_input.h"

#define KEY_BUFFER_SIZE 1024

static float AxisNormalize(const float value, const float min, const float max);
static float AxisDeadzone(float value, const float maxval, const float deadzone);

static boolean iskeymark = false;
static char keybuffer[KEY_BUFFER_SIZE];
static struct mouse_t mouse = {
	.x = 0,
	.y = 0,
	.xrel = 0,
	.yrel = 0,
	.button_l = false,
	.button_m = false,
	.button_r = false,
	.button_x1 = false,
	.button_x2 = false,
	.wheel.x = 0,
	.wheel.y = 0,
	.wheel.direction = 0,
};

static struct keyboard_t keyboard;

static struct controller_t controller = {
	.axis_l.x = 0,
	.axis_l.y = 0,
	.axis_r.x = 0,
	.axis_r.y = 0,
	.trigger_l = 0,
	.trigger_r = 0,
	.button = {
		SDL_RELEASED,SDL_RELEASED,SDL_RELEASED,
		SDL_RELEASED,SDL_RELEASED,SDL_RELEASED,
		SDL_RELEASED,SDL_RELEASED,SDL_RELEASED,
		SDL_RELEASED,SDL_RELEASED,SDL_RELEASED,
		SDL_RELEASED,SDL_RELEASED,SDL_RELEASED,
		SDL_RELEASED,
	},
};

void G_OnMouseMotion(const SDL_MouseMotionEvent *event) {
	mouse.x = event->x;
	mouse.y = event->y;
	mouse.xrel = event->xrel;
	mouse.yrel = event->yrel;
}

void G_OnMouseButtonDown(const SDL_MouseButtonEvent *event) {
	mouse.x = event->x;
	mouse.y = event->y;
	switch (event->button) {
	case SDL_BUTTON_LEFT:
		mouse.button_l = true;
		break;
    case SDL_BUTTON_MIDDLE:
		mouse.button_m = true;
		break;
	case SDL_BUTTON_RIGHT:
		mouse.button_r = true;
		break;
	case SDL_BUTTON_X1:
		mouse.button_x1 = true;
		break;
	case SDL_BUTTON_X2:
		mouse.button_x2 = true;
		break;
	}
}

void G_OnMouseButtonUp(const SDL_MouseButtonEvent *event) {
	mouse.x = event->x;
	mouse.y = event->y;
	switch (event->button) {
	case SDL_BUTTON_LEFT:
		mouse.button_l = false;
		break;
    case SDL_BUTTON_MIDDLE:
		mouse.button_m = false;
		break;
	case SDL_BUTTON_RIGHT:
		mouse.button_r = false;
		break;
	case SDL_BUTTON_X1:
		mouse.button_x1 = false;
		break;
	case SDL_BUTTON_X2:
		mouse.button_x2 = false;
		break;
	}
}

void G_OnMouseWheel(const SDL_MouseWheelEvent *event) {
	mouse.wheel.x = event->x;
	mouse.wheel.y = event->y;
	mouse.wheel.direction = event->direction;
}

void G_OnKeyDown(const SDL_Keysym *key) {
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

void G_OnKeyUp(const SDL_Keysym *key) {

}

void G_OnTextEdit(const SDL_TextEditingEvent *event) {

}

void G_OnTextInput(const SDL_TextInputEvent *event) {
	if (!(SDL_GetModState() & KMOD_CTRL && (event->text[0] == 'c' ||
		event->text[0] == 'C' || event->text[0] == 'v' ||
	    event->text[0] == 'V'))) {

	}
}

void G_OnControllerAxisMotion(const SDL_ControllerAxisEvent *event) {
	switch (event->axis) {
	case SDL_CONTROLLER_AXIS_LEFTX:
		controller.axis_l.x = event->value;
		break;
	case SDL_CONTROLLER_AXIS_LEFTY:
		controller.axis_l.y = event->value;
		break;
	case SDL_CONTROLLER_AXIS_RIGHTX:
		controller.axis_r.x = event->value;
		break;
	case SDL_CONTROLLER_AXIS_RIGHTY:
		controller.axis_r.y = event->value;
		break;
	case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
		controller.trigger_l = event->value;
		break;
	case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
		controller.trigger_r = event->value;
		break;
	case SDL_CONTROLLER_AXIS_MAX:
		break;
	}
}

void G_OnControllerButtonDown(const SDL_ControllerButtonEvent *event) {

}

void G_OnControllerButtonUp(const SDL_ControllerButtonEvent *event) {

}

void G_OnControllerDeviceAdded(const SDL_ControllerDeviceEvent *event) {

}

void G_OnControllerDeviceRemoved(const SDL_ControllerDeviceEvent *event) {

}

void G_OnControllerDeviceRemapped(const SDL_ControllerDeviceEvent *event) {

}

boolean G_IsKeyDown(void) {
	return true;
}

boolean G_IsMouseButtonDown(void) {
	return true;
}

// start taking text input
void G_KeyMark(void) {
	SDL_StartTextInput();
	iskeymark = true;
}

// retrieve text input buffer
char *G_KeyPeek(void) {
	return NULL;
}

// stop taking text input
void G_KeyUnmark(void) {
	SDL_StopTextInput();
	iskeymark = false;
}

static float AxisNormalize(const float value, const float min,
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
	} else {
		return 0.0f;
	}
	const float normalized = value / (maxval - deadzone);
	return DEADZONE_MAX(-1.0f, DEADZONE_MIN(normalized, 1.0f));
}

