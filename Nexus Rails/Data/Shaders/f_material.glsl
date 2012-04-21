#version 150

struct Material
{
	vec3 color;
	vec3 emission;
};

uniform sampler2D tex;
uniform Material material;
in vec2 texCoord;
out vec4 fragColor;

void main() {
	vec4 texcolor = texture2D(tex,texCoord);
	fragColor = vec4(material.emission,1.0)+vec4(material.color,1.0)*texcolor;
} 