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
	else if(u_mode==5){
		


	}
	
}
