#version 430

layout (location = 0) in vec3 position;

uniform mat4 wvp;

out vec3 texcoord;

void main() {
	vec4 wvp_pos = wvp * vec4(position, 1.0);
	gl_Position = wvp_pos.xyww;
	texcoord = position;
}
