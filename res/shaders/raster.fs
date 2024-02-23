// This variables comes from the vertex shader
// They are baricentric interpolated by pixel according to the distance to every vertex
varying vec2 v_uv;
varying vec3 v_world_position;
varying vec3 v_world_normal;

uniform sampler2D u_textcara;

void main()
{
	// Set the ouput color per pixel
	vec3 color = texture2D(u_textcara, v_uv).xyz;

	gl_FragColor = vec4( color, 1.0 );
}
