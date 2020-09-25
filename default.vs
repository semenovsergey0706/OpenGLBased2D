#version 330 core
#extension GL_EXT_texture_array : enable
#extension GL_EXT_bindable_uniform : enable
#extension GL_EXT_gpu_shader4 : enable

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

bindable uniform float shiftData[18];

flat out int instID;

out vec2 tCoord;

void main()
{
	tCoord = texCoord;
	instID = gl_InstanceID; 
	//gl_Position = vec4(position.x + shiftData[gl_InstanceID*2], position.y+shiftData[gl_InstanceID*2+1], position.z, 1.0f);
	gl_Position.xy = position.xy*2;
}