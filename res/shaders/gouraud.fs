varying vec2 v_uv;
varying vec3 v_world_position;
varying vec3 v_world_normal;
varying vec3 v_color_fin;

uniform sampler2D u_textcara_s;

void main()
{
	// Set the ouput color per pixel
	vec3 color = texture2D(u_textcara_s, v_uv).xyz;

	vec3 final = color*v_color_fin;

	gl_FragColor = vec4( final, 1.0 );
}
