#version 330 core

layout(location=0) in vec3 in_position;
layout(location=1) in vec3 in_color;
layout(location=2) in vec2 in_barycentric;

out VS_OUT
{
	vec3 color;
	vec2 barycentric;
} vs_out;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

void main()
{
	mat4 mvp = u_projection * u_view * u_model;
	gl_Position = mvp * vec4(in_position, 1.0);
	vs_out.color = in_color;
	vs_out.barycentric = in_barycentric;
}
