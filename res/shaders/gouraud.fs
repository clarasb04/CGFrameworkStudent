varying vec2 v_uv;
varying vec3 v_world_position;
varying vec3 v_world_normal;
varying vec3 v_color_fin;

uniform sampler2D u_textcara;

void main()
{
	// Set the ouput color per pixel
	vec3 color = texture2D(u_textcara, v_uv).xyz;

	gl_FragColor = vec4( v_color_fin, 1.0 );
}
