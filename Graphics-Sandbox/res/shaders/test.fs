#version 330 core

in VS_OUT
{
	vec3 position;
	vec3 normal;
	vec3 color;
	vec2 barycentric;
} fs_in;

out vec4 fragColor;

const float borderWidth = 0.02;

const vec3 GREEN = vec3(0x54, 0xCC, 0x28) / 255.0;
const vec3 BLUE = vec3(0x29, 0x99, 0xD8) / 255.0;

void main()
{
	vec3 borderColor = vec3(0.0);

	float dist = max(abs(fs_in.barycentric.x), abs(fs_in.barycentric.y));
	vec3 tileColor = vec3(1.0);
	vec3 color = mix(tileColor, borderColor, smoothstep(1.0 - borderWidth - fwidth(dist), 1.0 - borderWidth, dist));

	color *= mix(vec3(0.0), BLUE, smoothstep(0.0, 1.0, dist));

	color = vec3(1.0) * pow(dot(normalize(fs_in.normal), normalize(vec3(1.0, 1.0, 0.5))), 2.0);

	fragColor = vec4(pow(color, vec3(1.0 / 2.2)), 1.0);
}
