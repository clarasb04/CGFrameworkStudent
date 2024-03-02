varying vec2 v_uv;
varying vec3 v_world_position;
varying vec3 v_world_normal;


uniform vec3 u_Ka;
uniform vec3 u_Kd;
uniform vec3 u_Ks;
uniform vec3 u_ia;
uniform float u_shinness;
uniform vec3 u_light;
uniform vec3 u_eye;
uniform vec3 u_is;
uniform vec3 u_id;
uniform sampler2D u_textcara;

void main()
{
	// Set the ouput color per pixel
	vec3 color = texture2D(u_textcara, v_uv).xyz;

	
	vec3 L = normalize(u_light - v_world_position);
	vec3 N = normalize(v_world_normal);
	vec3 V = normalize(u_eye - v_world_position);
	vec3 R = reflect(-L,N);
	float dist = distance(u_light, v_world_position);

	vec3 ip = u_Ka*u_ia + 1/(dist*dist)*(u_Kd*clamp(dot(L,N),0,1)*u_id + u_Ks* pow(clamp(dot(R,V),0,1), u_shinness)*u_is);

	vec3 final = color*ip;

	gl_FragColor = vec4( final, 1.0 );
}
