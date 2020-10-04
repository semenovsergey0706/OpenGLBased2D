#version 330 core
#extension GL_EXT_texture_array : enable
#extension GL_EXT_bindable_uniform : enable
#extension GL_EXT_gpu_shader4 : enable

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;

bindable uniform vec2 m_rectSize[360];
bindable uniform mat3 m_transform[360];
bindable uniform int m_renderID[360];
bindable uniform vec2 m_frameRatio[360];
bindable uniform vec2 m_frameIndexes[360];

out vec2 TexCoord;
flat out int e_id;

void main()
{	
	e_id = m_renderID[gl_InstanceID];
	TexCoord = texCoord * m_frameRatio[e_id] + m_frameRatio[e_id]*m_frameIndexes[e_id];
	gl_Position.xyz = m_transform[e_id]*vec3(position*m_rectSize[e_id], 1.0f);
}