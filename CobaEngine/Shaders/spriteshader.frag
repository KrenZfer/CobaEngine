#version 330 core

in vec4 fragmentColor;
in vec2 fragmentUV;


uniform sampler2D mySampler;

void main () {

	vec4 textureColor = texture(mySampler, fragmentUV);

	gl_FragColor = fragmentColor * textureColor;

}