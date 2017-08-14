#version 330 core

in vec2 fragmentUV;
in vec4 fragmentColor;

uniform sampler2D text;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture2D(text, fragmentUV).r);
	gl_FragColor = fragmentColor * sampled;
}