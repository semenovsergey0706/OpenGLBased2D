#version 330 core
#extension GL_EXT_texture_array : enable
#extension GL_EXT_bindable_uniform : enable
#extension GL_EXT_gpu_shader4 : enable

in vec2 TexCoord;
flat in int e_id;

bindable uniform vec4 m_color[360];

uniform sampler2D m_samplers[360];
//uniform sampler2D ourTexture;

out vec4 color;

void main()
{
	color = texture(m_samplers[e_id], TexCoord);
	//if (t_color.a == 0) discard;
	//color =	t_color;
	//color = m_color[e_id];
}