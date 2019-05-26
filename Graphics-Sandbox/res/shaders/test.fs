#version 330 core

in VS_OUT
{
	vec3 color;
	vec2 barycentric;
} fs_in;

out vec4 fragColor;

void main()
{
	vec3 bottomLeftColor = vec3(0.0f, 1.0f, 1.0f);
	vec3 bottomRightColor = vec3(1.0f, 0.5f, 0.0f);
	vec3 topLeftColor = vec3(1.0f, 1.0f, 0.0f);
	vec3 topRightColor = vec3(0.5f, 0.0f, 1.0f);

	vec3 bottomColor = mix(bottomLeftColor, bottomRightColor, smoothstep(0.0, 1.0, fs_in.barycentric.x * 0.5 + 0.5));
	vec3 topColor = mix(topLeftColor, topRightColor, smoothstep(0.0, 1.0, fs_in.barycentric.x * 0.5 + 0.5));

	vec3 color = mix(bottomColor, topColor, smoothstep(0.0, 1.0, fs_in.barycentric.y * 0.5 + 0.5));

	fragColor = vec4(pow(color, vec3(1.0 / 2.2)), 1.0);
}
