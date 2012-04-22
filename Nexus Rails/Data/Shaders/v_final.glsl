#version 120

uniform mat4 projectionMatrix;
in vec3 v_vertex;
in vec2 v_texture;
varying vec2 texCoord;

void main() {
	gl_Position = projectionMatrix * vec4(v_vertex, 1.0);
	texCoord = vec2(vec4(v_texture,0.0,0.0));
}