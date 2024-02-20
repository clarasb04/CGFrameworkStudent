varying vec2 v_uv;
uniform int u_mode;

void main()
{
	if(u_mode==1){
		vec3 color = mix(vec3(0.0,0.0,1.0), vec3(1.0,0.0,0.0), v_uv.x);
		gl_FragColor = vec4(color, 1.0);		
	}
	else if(u_mode==2){
		vec3 color = vec3(distance(vec2(0.5,0.5), v_uv));
		gl_FragColor = vec4(color, 1.0);
	}
	else if(u_mode==3){
		float red_comp = clamp( sin(v_uv.x*40), 0.0, 1.0);
		float blue_comp = clamp( sin(v_uv.y*40), 0.0, 1.0);
		gl_FragColor = vec4(red_comp, 0.0, blue_comp, 1.0);
	}
	else if(u_mode==4){
		float div_ent_x = v_uv.x*16;
		float pas_x = floor(div_ent_x);
		float div_ent_y = v_uv.y*16;
		float pas_y = floor(div_ent_y);

		vec3 color = vec3(pas_x/16, pas_y/16, 0);
		gl_FragColor = vec4(color, 1.0);


	}
	else if(u_mode==5){
		//aquest crec q el canviare
		vec3 cond_x = vec3(clamp(sin(v_uv.x*100)*4, 0.0, 1.0));
		vec3 cond_y = vec3(clamp(sin(v_uv.y*100)*4, 0.0, 1.0));
		vec3 color = vec3(abs(cond_x-cond_y));
		gl_FragColor = vec4(color, 1.0);


	}
	else if(u_mode==6){
		float resta = v_uv.y - (sin(v_uv.x*6.3)*0.25 + 0.5);
		float zona = step(resta, 0.0);
		vec3 color = mix(vec3(0.0, abs(1-zona), 0.0), vec3(0.0, zona, 0.0), v_uv.y);
		
		gl_FragColor = vec4(color, 1.0);
	}
	
}
