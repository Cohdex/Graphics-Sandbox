#version 330 core

layout(location=0) in vec3 in_position;
//layout(location=1) in vec3 in_color;
//layout(location=2) in vec2 in_barycentric;

out VS_OUT
{
	vec3 position;
	vec3 color;
	vec2 barycentric;
} vs_out;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

float rand(vec2 n) { 
	return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453);
}

float noise(vec2 p){
	vec2 ip = floor(p);
	vec2 u = fract(p);
	u = u*u*(3.0-2.0*u);
	
	float res = mix(
		mix(rand(ip),rand(ip+vec2(1.0,0.0)),u.x),
		mix(rand(ip+vec2(0.0,1.0)),rand(ip+vec2(1.0,1.0)),u.x),u.y);
	return res*res;
}

void main()
{
	vec4 worldPos = u_model * vec4(in_position, 1.0);
	worldPos += noise(worldPos.xz / 1.5) / 1.5;
	vs_out.position = worldPos.xyz;
	vs_out.color = vec3(0.5);//in_color;
	vs_out.barycentric = vec2(0.5);//in_barycentric;

	gl_Position = u_projection * u_view * worldPos;
}
