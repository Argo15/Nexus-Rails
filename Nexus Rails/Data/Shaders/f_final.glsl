#version 120

uniform sampler2D colorTex;
uniform sampler2D emissionTex;
varying vec2 texCoord;

const float blurSizeX = 1.0/500.0;
const float blurSizeY = 1.0/300.0;

void main() {
	vec4 color = texture2D(colorTex,texCoord);
	vec4 emission = vec4(0.0);
	
	emission += texture2D(emissionTex, vec2(texCoord.x - 4.0*blurSizeX, texCoord.y)) * 0.05;
    emission += texture2D(emissionTex, vec2(texCoord.x - 3.0*blurSizeX, texCoord.y)) * 0.09;
    emission += texture2D(emissionTex, vec2(texCoord.x - 2.0*blurSizeX, texCoord.y)) * 0.12;
    emission += texture2D(emissionTex, vec2(texCoord.x - blurSizeX, texCoord.y)) * 0.15;
    emission += texture2D(emissionTex, vec2(texCoord.x, texCoord.y)) * 0.16;
    emission += texture2D(emissionTex, vec2(texCoord.x + blurSizeX, texCoord.y)) * 0.15;
    emission += texture2D(emissionTex, vec2(texCoord.x + 2.0*blurSizeX, texCoord.y)) * 0.12;
    emission += texture2D(emissionTex, vec2(texCoord.x + 3.0*blurSizeX, texCoord.y)) * 0.09;
    emission += texture2D(emissionTex, vec2(texCoord.x + 4.0*blurSizeX, texCoord.y)) * 0.05;
    
    emission += texture2D(emissionTex, vec2(texCoord.x, texCoord.y - 4.0*blurSizeY)) * 0.05;
	emission += texture2D(emissionTex, vec2(texCoord.x, texCoord.y - 3.0*blurSizeY)) * 0.09;
	emission += texture2D(emissionTex, vec2(texCoord.x, texCoord.y - 2.0*blurSizeY)) * 0.12;
	emission += texture2D(emissionTex, vec2(texCoord.x, texCoord.y - blurSizeY)) * 0.15;
	emission += texture2D(emissionTex, vec2(texCoord.x, texCoord.y)) * 0.16;
	emission += texture2D(emissionTex, vec2(texCoord.x, texCoord.y + blurSizeY)) * 0.15;
	emission += texture2D(emissionTex, vec2(texCoord.x, texCoord.y + 2.0*blurSizeY)) * 0.12;
	emission += texture2D(emissionTex, vec2(texCoord.x, texCoord.y + 3.0*blurSizeY)) * 0.09;
	emission += texture2D(emissionTex, vec2(texCoord.x, texCoord.y + 4.0*blurSizeY)) * 0.05;

	gl_FragColor = emission+color;
} 