#version 120

uniform sampler2D diffuse;

varying vec2 uv0;
void main()
{
	gl_FragColor = texture2D(diffuse, uv0);
}