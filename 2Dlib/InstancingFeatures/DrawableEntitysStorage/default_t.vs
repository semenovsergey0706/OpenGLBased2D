#version 330 core
#extension GL_EXT_texture_array : enable
#extension GL_EXT_bindable_uniform : enable
#extension GL_EXT_gpu_shader4 : enable

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;

bindable uniform vec2 c_texCoord[500];
bindable uniform vec2 size[500];
bindable uniform mat4 transform[500];
bindable uniform vec4 color[500];
bindable uniform vec2 frameID[500];
bindable uniform int renderQ[500];

//vec2 t_pos;

flat out int instID;
out vec2 tCoord;
flat out int indexID;

void main()
{
	//t_pos = size[indexID]*position;
	instID = gl_InstanceID;
	indexID = renderQ[gl_InstanceID];
	//tCoord = texCoord*(c_texCoord[indexID]*frameID[indexID]);	 
	//gl_Position = transform[indexID]*vec4(t_pos, 0.0f, 1.0f);
	gl_Position = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}