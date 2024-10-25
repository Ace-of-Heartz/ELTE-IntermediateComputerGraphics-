#version 430

// pipeline-ból bejövő per-fragment attribútumok
in vec3 vs_out_pos;

out vec4 fs_out_col;

// skybox textúra
uniform samplerCube skyboxTexture;

uniform vec3 ground_col = vec3(.3,.4,.2);
uniform vec3 sky_col = vec3(.2,.2,.7);

void main()
{
//	vec3 dir = normalize(vs_out_pos);
//	vec3 col = mix(ground_col,sky_col,(dir.y + 1.) / 2.);
//	vec3 col = mix(ground_col, sky_col, (sin(dir.y) + 1) / 2.);
	vec3 tex = texture(skyboxTexture,vs_out_pos).xyz;

	fs_out_col = vec4(tex ,1.0);
}