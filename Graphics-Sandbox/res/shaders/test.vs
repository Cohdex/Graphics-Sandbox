#version 330 core

layout(location=0) in vec3 in_position;
layout(location=1) in vec2 in_texcoord;
layout(location=2) in vec3 in_colorUL;
layout(location=3) in vec3 in_colorUR;
layout(location=4) in vec3 in_colorLL;
layout(location=5) in vec3 in_colorLR;

out VS_OUT
{
	vec3 position;
	vec2 texcoord;
	vec3 normal;
	vec3 colorUL;
	vec3 colorUR;
	vec3 colorLL;
	vec3 colorLR;
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

	worldPos.y += noise(worldPos.xz / 1.5) / 1.5;
	float offset = 0.001;
	vec3 dx = worldPos.xyz + vec3(offset, 0.0, 0.0);
	dx.y += noise(dx.xz / 1.5) / 1.5;
	vec3 dz = worldPos.xyz + vec3(0.0, 0.0, offset);
	dz.y += noise(dz.xz / 1.5) / 1.5;

	vec3 normal = normalize(cross(dz, dx));

	vs_out.position = worldPos.xyz;
	vs_out.texcoord = in_texcoord;
	vs_out.normal = normal;
	vs_out.colorUL = in_colorUL;
	vs_out.colorUR = in_colorUR;
	vs_out.colorLL = in_colorLL;
	vs_out.colorLR = in_colorLR;

	gl_Position = u_projection * u_view * worldPos;
}
