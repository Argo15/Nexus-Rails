#version 120

struct Material
{
	vec3 color;
	vec3 emission;
};

uniform sampler2D tex;
uniform Material material;
varying vec2 texCoord;

void main() {
	vec4 texcolor = texture2D(tex,texCoord);
	gl_FragData[0] = vec4(material.color,1.0)*texcolor;
	gl_FragData[1] = vec4(material.emission,1.0);
} 