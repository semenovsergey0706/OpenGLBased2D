#version 330 core
#extension GL_EXT_texture_array : enable
#extension GL_EXT_bindable_uniform : enable
#extension GL_EXT_gpu_shader4 : enable

flat in int instID;
flat in int indexID;
in vec2 tCoord;

bindable uniform int textureID[500];
//bindable uniform vec4 color[500];

uniform  sampler2D samplers[500];

out vec4 color;
float green;

void main()
{
	green = 0.3 * instID;
	//p_color = texture(samplers[1], tCoord);
	color = vec4(1.0f, green, 0.0f, 1.0f);
	//p_color = color[instID]; 
}