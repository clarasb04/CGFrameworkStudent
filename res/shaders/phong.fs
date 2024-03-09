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
uniform sampler2D u_textcara_s;
uniform sampler2D u_textcara_n;
uniform vec3 u_flags;
uniform int u_num_llum;

void main()
{
	// Set the ouput color per pixel
	vec3 color = texture2D(u_textcara_s, v_uv).xyz;
	vec3 Ks = u_Ks;
	vec3 Ka = u_Ka;
	vec3 Kd = u_Kd;
	if(u_flags.y==1){
		Ks = vec3(texture2D(u_textcara_s, v_uv).a);
	}
		
	if(u_flags.x==1){
		Kd = color;
		Ka = u_Ka * color;
	}

	vec3 final_normal = v_world_normal;
	if(u_flags.z==1){
		vec3 normals = texture2D(u_textcara_n, v_uv).xyz;
		vec3 comp_normals = vec3((normals.x-0.5)*2, (normals.y-0.5)*2, (normals.z-0.5)*2);
		float mix_factor = 0.5;
		final_normal = mix(v_world_normal, comp_normals, mix_factor);
	}


	
	vec3 L = normalize(u_light - v_world_position);
	vec3 N = normalize(final_normal);
	vec3 V = normalize(u_eye - v_world_position);
	vec3 R = reflect(-L,N);
	float dist = distance(u_light, v_world_position);
	
	vec3 ip;

	if(u_num_llum==0){
		 ip = Ka*u_ia + 1/(dist*dist)*(Kd*clamp(dot(L,N),0,1)*u_id + Ks* pow(clamp(dot(R,V),0,1), u_shinness)*u_is);
	}
	else{
		ip = 1/(dist*dist)*(Kd*clamp(dot(L,N),0,1)*u_id + Ks* pow(clamp(dot(R,V),0,1), u_shinness)*u_is);
	}

	

	gl_FragColor = vec4(ip, 1.0 );
}
