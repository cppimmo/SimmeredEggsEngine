#version 430

in vec3 texcoord;

out vec4 fragcolor;

uniform samplerCube cubemap_texture;

void main() {
	fragcolor = texture(cubemap_texture, texcoord);
}
