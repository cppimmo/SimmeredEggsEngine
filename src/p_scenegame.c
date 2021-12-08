/* =============================================================================
** SimmeredEggsEngine, file: p_scenegame.c Created 12/6/2021
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
#include "p_scenegame.h"
#include "u_log.h"
#include "u_screenshot.h"

struct vertexarray_t vao;
struct vertexbuffer_t vbo;
struct shaderinfo_t shaders[2] = {
		{GL_VERTEX_SHADER,"triangle_vs.glsl",0},
		{GL_FRAGMENT_SHADER,"triangle_fs.glsl",0},
};
GLuint program;

boolean P_GameStart(void) {
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	static const GLfloat vertices[6][5] = {
		{-0.90f,-0.90f, 1.0f, 0.0f, 0.0f},
		{ 0.85f,-0.90f, 0.0f, 1.0f, 0.0f},
		{-0.90f, 0.85f, 0.0f, 0.0f, 1.0f},
		{ 0.90f,-0.85f, 1.0f, 0.0f, 0.0f},
		{ 0.90f, 0.90f, 0.0f, 1.0f, 0.0f},
		{-0.85f, 0.90f, 0.0f, 0.0f, 1.0f},
	};

	if (!R_CreateVertexArray(&vao))
		U_LogWrite(LOG_LOG, "FAILED TO CREATE VAO");
	if (!R_CreateVertexBuffer(&vbo, GL_ARRAY_BUFFER, GL_FALSE))
		U_LogWrite(LOG_LOG, "FAILED TO CREATE VBO");
    R_VertexBufferStorage(&vbo, sizeof(vertices), vertices);

	R_CreateProgram(&program, shaders, 2);
    R_UseProgram(program);

	R_BindVertexArray(&vao);
	R_BindVertexBuffer(&vbo);

	R_VertexAttribPtr(&vao, &vbo, 0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, BUFFER_OFFSET(0, GLfloat));
	R_VertexAttribEnable(0);
	R_VertexAttribPtr(&vao, &vbo, 1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, BUFFER_OFFSET(2, GLfloat));
	R_VertexAttribEnable(1);
	return true;
}

boolean P_GameUpdate(GLfloat deltatime) {
	I_UpdateKeyboardState();
	if (I_IsKeyDown(SDL_SCANCODE_A)) {
		U_LogWrite(LOG_LOG, "Pressed key A.\n");
	}
	if (I_IsMouseButtonDown(SDL_BUTTON_LEFT)) {
		U_LogWrite(LOG_LOG, "Clicked left mouse button.\n");
	}
	if (I_IsControllerButtonDown(SDL_CONTROLLER_BUTTON_X)) {
		U_LogWrite(LOG_LOG, "Pressed controller button X.\n");
	}
 	static boolean screenshotpress = false;
	if (I_IsKeyDown(SDL_SCANCODE_S) && screenshotpress == false) {
		U_TakeScreenshot();
		screenshotpress = true;
	}
	SDL_GameController *ctrl = SDL_GameControllerOpen(0);
	SDL_Joystick *joy = SDL_GameControllerGetJoystick(ctrl);
	SDL_GameControllerRumble(ctrl, 2000, 3000, 20);
	return true;
}

boolean P_GameRender(GLfloat deltatime) {
	/* static const GLfloat clear_color[] = { 1.0f, 1.0f, 0.0f, 0.0f };
	   GLint drawbuf_id = 0;
	   glGetIntegerv(GL_FRAMEBUFFER_BINDING, &drawbuf_id);
	   glClearBufferfv(GL_COLOR, 0, clear_color); */
	static const GLfloat color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	R_Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	R_ClearColor(color);

	R_BindVertexArray(&vao);
	R_Wireframe(false);
	R_LineWidth(1.0f);
	R_DrawArrays(GL_TRIANGLES, 0, 3);

	R_Wireframe(true);
	R_LineWidth(5.0f);
	R_DrawArrays(GL_TRIANGLES, 3, 6);
	return true;
}

boolean P_GameDestroy(void) {
	R_DeleteProgram(program);
	R_DeleteVertexArray(&vao);
	R_DeleteVertexBuffer(&vbo);
	return true;
}

