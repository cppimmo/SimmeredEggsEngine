#include "p_scenegame.h"
#include "u_log.h"

struct vertexarray_t vao;
struct vertexbuffer_t vbo;
struct shaderinfo_t shaders[2] = {
		{GL_VERTEX_SHADER,"assets/shaders/triangle_vs.glsl",0},
		{GL_FRAGMENT_SHADER,"assets/shaders/triangle_fs.glsl",0},
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

boolean P_GameUpdate(GLfloat delta_time) {
	U_LogWrite(LOG_LOG, "Hello Game Scene is working.\n");
	return true;
}

boolean P_GameRender(GLfloat deltatime) {
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

