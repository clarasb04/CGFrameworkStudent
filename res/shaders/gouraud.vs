// Global variables from the CPU
uniform mat4 u_model;
uniform mat4 u_viewprojection;
uniform sampler2D u_textura_s;
uniform vec3 u_Ka;
uniform vec3 u_Kd;
uniform vec3 u_Ks;
uniform vec3 u_ia;
uniform float u_shinness;
uniform vec3 u_light;
uniform vec3 u_eye;
uniform vec3 u_is;
uniform vec3 u_id;
uniform int u_num_llum;


// Variables to pass to the fragment shader
varying vec2 v_uv;
varying vec3 v_world_position;
varying vec3 v_world_normal;
varying vec3 v_color_fin;

//here create uniforms for all the data we need here

void main()
{	
	v_uv = gl_MultiTexCoord0.xy;

	// Convert local position to world space
	vec3 world_position = (u_model * vec4( gl_Vertex.xyz, 1.0)).xyz;

	// Convert local normal to world space
	vec3 world_normal = (u_model * vec4( gl_Normal.xyz, 0.0)).xyz;

	// Pass them to the fragment shader interpolated
	v_world_position = world_position;
	v_world_normal = world_normal;

	// Project the vertex using the model view projection matrix
	gl_Position = u_viewprojection * vec4(world_position, 1.0); //output of the vertex shader
	
	// pgonh model ip

	vec3 L = normalize(u_light - v_world_position);
	vec3 N = normalize(v_world_normal);
	vec3 V = normalize(u_eye - v_world_position);
	vec3 R = reflect(-L,N);
	float dist = distance(u_light, v_world_position);

	vec3 ip;

	if(u_num_llum==0){
		ip = u_Ka*u_ia + 1/(dist*dist)*(u_Kd*clamp(dot(L,N),0,1)*u_id + u_Ks* pow(clamp(dot(R,V),0,1), u_shinness)*u_is);
	}
	else{
		ip = 1/(dist*dist)*(u_Kd*clamp(dot(L,N),0,1)*u_id + u_Ks* pow(clamp(dot(R,V),0,1), u_shinness)*u_is);
	}

	

	// ip en varying
	v_color_fin = ip;

}