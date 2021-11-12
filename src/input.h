#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

struct mouse_t {
	struct mouse_wheel_t {

	} wheel;
};
typedef struct mouse_t Mouse;

struct keyboard_t {

};
typedef struct keyboard_t Keyboard;

struct controller_t {

};
typedef struct controller_t Controller;

void on_mouse_motion(const SDL_MouseMotionEvent *event);
void on_mouse_button_down(const SDL_MouseButtonEvent *event);
void on_mouse_button_up(const SDL_MouseButtonEvent *event);
void on_mouse_wheel(const SDL_MouseWheelEvent *event);
void on_key_down(const SDL_Keysym *key);
void on_key_up(const SDL_Keysym *key);
void on_controller_axis_motion(const SDL_ControllerAxisEvent *event);
void on_controller_button_down(const SDL_ControllerButtonEvent *event);
void on_controller_button_up(const SDL_ControllerButtonEvent *event);
void on_controller_device_added(const SDL_ControllerDeviceEvent *event);
void on_controller_device_removed(const SDL_ControllerDeviceEvent *event);
void on_controller_device_remapped(const SDL_ControllerDeviceEvent *event);

#endif // INPUT_H
