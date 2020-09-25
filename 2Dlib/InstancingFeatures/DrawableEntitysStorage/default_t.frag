#version 330 core
#extension GL_EXT_texture_array : enable
#extension GL_EXT_bindable_uniform : enable
#extension GL_EXT_gpu_shader4 : enable

flat in int instID;
flat in int indexID;
//in vec2 tCoord;

bindable uniform int textureID[500];

uniform  sampler2D samplers[500];

out vec4 color;

void main()
{
	color = texture(samplers[textureID[indexID]], tCoord);
}