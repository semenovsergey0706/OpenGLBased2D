#version 330 core
#extension GL_EXT_texture_array : enable
#extension GL_EXT_bindable_uniform : enable
#extension GL_EXT_gpu_shader4 : enable

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;

bindable uniform vec2 m_rectSize[360];
bindable uniform mat3 m_transform[360];

out vec2 TexCoord;
flat out int e_id;

void main()
{
	TexCoord = texCoord;
	e_id = gl_InstanceID;
	//gl_Position.xy = position*m_rectSize[gl_InstanceID];
	//gl_Position.xyz = vec4(m_transform[gl_InstanceID]*vec3(position*m_rectSize[gl_InstanceID], 0.0f), 1.0f);
	//gl_Position.xyz = m_transform[1]*vec3(position*m_rectSize[gl_InstanceID], 0.0f);
	gl_Position.xyz = m_transform[gl_InstanceID]*vec3(position*m_rectSize[gl_InstanceID], 1.0f);
	//gl_Position.xyz = (vec3(vec2(0.0,0.0)+position*m_rectSize[gl_InstanceID], 1.0f)*m_transform[gl_InstanceID]);
	//gl_Position.xy += vec2(0.5, -0.5);
	//gl_Position.xy = m_transform[gl_InstanceID]*(position*m_rectSize[gl_InstanceID]);
	//gl_Position.xy =  position;	
}