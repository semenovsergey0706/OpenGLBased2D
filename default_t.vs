#version 330 core
#extension GL_EXT_texture_array : enable
#extension GL_EXT_bindable_uniform : enable
#extension GL_EXT_gpu_shader4 : enable

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;

bindable uniform vec2 c_texCoord[500];
bindable uniform vec2 m_size[500];
bindable uniform mat4 transform[500];
//bindable uniform vec4 color[500];
bindable uniform vec2 frameID[500];
bindable uniform int renderQ[500];

flat out int instID;
out vec2 tCoord;
flat out int indexID;

vec2 mpos;

void main()
{
	instID = gl_InstanceID;
	indexID = renderQ[gl_InstanceID];
	mpos = position*m_size[gl_InstanceID];
	//mpos = position*vec2(64, 64);
	//tCoord = (texCoord*c_texCoord[indexID ])*frameID[indexID];
	tCoord = texCoord;	 
	gl_Position = vec4(mpos.xy + vec2(0.2*gl_InstanceID, -0.2*gl_InstanceID), 0.0f, 1.0f);
	//gl_Position = transform[indexID]*vec4(mpos.xy, 0.0f, 1.0f);
	//gl_Position = vec4(mpos.xy, 0.0f, 1.0f);
	//gl_Position = vec4(position.x, position.y, 0.0f, 1.0f);
	
}