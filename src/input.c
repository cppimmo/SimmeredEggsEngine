#include "input.h"

#define KEY_BUFFER_SIZE 1024

static bool is_key_mark = false;
static char key_buffer[KEY_BUFFER_SIZE];
static struct mouse_t g_mouse = {
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

static struct keyboard_t g_keyboard;

static struct controller_t g_controller = {
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

static float axis_normalize(const float value, const float min, const float max);
static float axis_deadzone(float value, const float max_value, const float deadzone);

void on_mouse_motion(const SDL_MouseMotionEvent *event)
{
	g_mouse.x = event->x;
	g_mouse.y = event->y;
	g_mouse.xrel = event->xrel;
	g_mouse.yrel = event->yrel;
}

void on_mouse_button_down(const SDL_MouseButtonEvent *event)
{
	g_mouse.x = event->x;
	g_mouse.y = event->y;
	switch (event->button) {
	case SDL_BUTTON_LEFT:
		g_mouse.button_l = true;
		break;
    case SDL_BUTTON_MIDDLE:
		g_mouse.button_m = true;
		break;
	case SDL_BUTTON_RIGHT:
		g_mouse.button_r = true;
		break;
	case SDL_BUTTON_X1:
		g_mouse.button_x1 = true;
		break;
	case SDL_BUTTON_X2:
		g_mouse.button_x2 = true;
		break;
	}
}

void on_mouse_button_up(const SDL_MouseButtonEvent *event)
{
	g_mouse.x = event->x;
	g_mouse.y = event->y;
	switch (event->button) {
	case SDL_BUTTON_LEFT:
		g_mouse.button_l = false;
		break;
    case SDL_BUTTON_MIDDLE:
		g_mouse.button_m = false;
		break;
	case SDL_BUTTON_RIGHT:
		g_mouse.button_r = false;
		break;
	case SDL_BUTTON_X1:
		g_mouse.button_x1 = false;
		break;
	case SDL_BUTTON_X2:
		g_mouse.button_x2 = false;
		break;
	}
}

void on_mouse_wheel(const SDL_MouseWheelEvent *event)
{
	g_mouse.wheel.x = event->x;
	g_mouse.wheel.y = event->y;
	g_mouse.wheel.direction = event->direction;
}

void on_key_down(const SDL_Keysym *key)
{
	if (is_key_mark) {
		if (key->sym == SDLK_BACKSPACE) {
			// remove the last character from the buffer

		} else if (key->sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
			// SDL_SetClipboardText( some const char *);

		} else if (key->sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
			// buffer = SDL_GetClipboardText();

		}
	}
}

void on_key_up(const SDL_Keysym *key)
{

}

void on_text_edit(const SDL_TextEditingEvent *event)
{

}

void on_text_input(const SDL_TextInputEvent *event)
{
	if (!(SDL_GetModState() & KMOD_CTRL && (event->text[0] == 'c' ||
		event->text[0] == 'C' || event->text[0] == 'v' ||
	    event->text[0] == 'V'))) {

	}
}

void on_controller_axis_motion(const SDL_ControllerAxisEvent *event)
{
	switch (event->axis) {
	case SDL_CONTROLLER_AXIS_LEFTX:
		g_controller.axis_l.x = event->value;
		break;
	case SDL_CONTROLLER_AXIS_LEFTY:
		g_controller.axis_l.y = event->value;
		break;
	case SDL_CONTROLLER_AXIS_RIGHTX:
		g_controller.axis_r.x = event->value;
		break;
	case SDL_CONTROLLER_AXIS_RIGHTY:
		g_controller.axis_r.y = event->value;
		break;
	case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
		g_controller.trigger_l = event->value;
		break;
	case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
		g_controller.trigger_r = event->value;
		break;
	case SDL_CONTROLLER_AXIS_MAX:
		break;
	}
}

void on_controller_button_down(const SDL_ControllerButtonEvent *event)
{

}

void on_controller_button_up(const SDL_ControllerButtonEvent *event)
{

}

void on_controller_device_added(const SDL_ControllerDeviceEvent *event)
{

}

void on_controller_device_removed(const SDL_ControllerDeviceEvent *event)
{

}

void on_controller_device_remapped(const SDL_ControllerDeviceEvent *event)
{

}

bool is_key_down()
{
	return true;
}

bool is_mb_down()
{
	return true;
}

// start taking text input
void key_mark()
{
	SDL_StartTextInput();
	is_key_mark = true;
}

// retrieve text input buffer
char *key_peek()
{
	return NULL;
}

// stop taking text input
void key_unmark()
{
	SDL_StopTextInput();
	is_key_mark = false;
}

static float axis_normalize(const float value, const float min, const float max)
{
	const float average = (min + max) / 2.0f;
	const float range = (max - min) / 2.0f;
	return (value - average) / range;
}

#define DEADZONE_MIN(a,b) (((a)<(b))?(a):(b))
#define DEADZONE_MAX(a,b) (((a)>(b))?(a):(b))

static float axis_deadzone(float value, const float max_value,
						   const float deadzone)
{
	if (value < -(deadzone)) {
		value += deadzone;
		// increase negative values to remove deadzone discontinuity
	} else if (value > deadzone) {
		value -= deadzone;
		// decrease positive values to remove deadzone discontinuity
	} else {
		return 0.0f;
	}
	const float normalized = value / (max_value - deadzone);
	return DEADZONE_MAX(-1.0f, DEADZONE_MIN(normalized, 1.0f));
}

