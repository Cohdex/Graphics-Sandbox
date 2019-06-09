#version 330 core

in VS_OUT
{
	vec3 position;
	vec3 color;
	vec2 barycentric;
} fs_in;

out vec4 fragColor;

uniform float u_time;

const float borderWidth = 0.02;

float rand(vec2 n) { 
	return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453);
}

float noise(vec2 p){
	vec2 ip = floor(p);
	vec2 u = fract(p);
	u = u * u * (3.0 - (2.0 * u));
	
	float res = mix(
		mix(rand(ip), rand(ip + vec2(1.0, 0.0)), u.x),
		mix(rand(ip + vec2(0.0, 1.0)), rand(ip + vec2(1.0, 1.0)), u.x), u.y);
	return res * res;
}

void main()
{
	vec3 borderColor = vec3(0.0);
	//borderColor = vec3(0x54, 0xCC, 0x28) / 255.0; // Green

	float dist = max(abs(fs_in.barycentric.x), abs(fs_in.barycentric.y));
	vec3 tileColor = fs_in.color;// + sin(u_time * (5 + noise(fs_in.position.xz)) + noise(fs_in.position.xz)) * 0.2;
	vec3 color = mix(tileColor, borderColor, smoothstep(1.0 - borderWidth - fwidth(dist), 1.0 - borderWidth, dist));

	fragColor = vec4(pow(color, vec3(1.0 / 2.2)), 1.0);
}
