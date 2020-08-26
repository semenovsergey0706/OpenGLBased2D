#version 330 core
#extension GL_EXT_texture_array : enable
#extension GL_EXT_bindable_uniform : enable
#extension GL_EXT_gpu_shader4 : enable

flat in int instID;
in vec2 tCoord;

bindable uniform vec4 colorData[9];

//uniform sampler2D samplers[2];

uniform  sampler2D samplers[2];
//uniform sampler2D ourTexture;

out vec4 color;

void main()
{
	//color = texture(samplers[instID - (instID/2)*2], tCoord);
	//color =	colorData[instID];
	color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}