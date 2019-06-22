#version 330 core

in VS_OUT
{
	vec3 position;
	vec2 texcoord;
	vec3 normal;
	vec3 colorUL;
	vec3 colorUR;
	vec3 colorLL;
	vec3 colorLR;
} fs_in;

out vec4 fragColor;

uniform sampler2D u_texture;

void main()
{
	float diffuse = pow(dot(normalize(fs_in.normal), normalize(vec3(1.0, 1.0, 0.5))), 2.0);

	vec3 texColor = texture(u_texture, fs_in.texcoord).rgb;

	vec3 colorUpper = mix(fs_in.colorUL, fs_in.colorUR, smoothstep(0.0, 1.0, fs_in.texcoord.x));
	vec3 colorLower = mix(fs_in.colorLL, fs_in.colorLR, smoothstep(0.0, 1.0, fs_in.texcoord.x));
	vec3 color = mix(colorUpper, colorLower, smoothstep(0.0, 1.0, fs_in.texcoord.y));

	color = texColor;

	fragColor = vec4(pow(color, vec3(1.0 / 1.0)), 1.0);
}
