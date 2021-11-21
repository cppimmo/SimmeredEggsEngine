#version 420 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 color;

out vec4 out_color;
	
void main() {
	gl_Position = position;
	out_color = vec4(color, 1.0);
}
