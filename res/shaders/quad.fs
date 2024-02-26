varying vec2 v_uv;
uniform int u_mode;
uniform int u_tecla;
uniform sampler2D u_texture;
uniform float u_height;
uniform float u_width; 
uniform float u_sec;

void main()
{
	if(u_tecla==1){
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
			
			float cond_x = step(((v_uv.x*10)-floor(v_uv.x*10)), 0.5);
			float cond_y = step(((v_uv.y*10)-floor(v_uv.y*10)), 0.5);
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
	else if(u_tecla==2){
		if(u_mode==1){
			vec3 color = texture2D(u_texture, v_uv).xyz;
			float col_fin = (color.x + color.y + color.z) / 3;
			vec3 fin = vec3(col_fin);
			gl_FragColor = vec4(fin, 1.0);
		}
		else if(u_mode==2){
			vec3 color = texture2D(u_texture, v_uv).xyz;
			vec3 col_fin = vec3(1-color.x, 1-color.y, 1-color.z);
			gl_FragColor = vec4(col_fin, 1.0);
		}
		else if(u_mode==3){
			vec3 color = texture2D(u_texture, v_uv).xyz; 
			float cond = (color.x + color.y) / 2.0;
			vec3 col_fin = vec3(cond, cond, 0.0);
			gl_FragColor = vec4(col_fin, 1.0);
		}
		else if(u_mode==4){
			vec3 color = texture2D(u_texture, v_uv).xyz;
			float cond = step((color.x+color.y+color.z), 1.5);
			vec3 col_fin = vec3(abs(1-cond));
			gl_FragColor = vec4(col_fin, 1.0);
		}
		else if(u_mode==5){
			
			float dist = distance(vec2(0.5,0.5), v_uv);
			vec3 color = texture2D(u_texture, v_uv).xyz;
			float red = clamp( color.r - dist, 0.0, 1.0);
			float green = clamp( color.g - dist, 0.0, 1.0);
			float blue = clamp( color.b - dist, 0.0, 1.0);
			gl_FragColor = vec4(red, green, blue, 1.0);


		}
		else if(u_mode==6){
			vec4 col_fin = vec4(0.0);
			vec2 mida = vec2(u_width, u_height);
			for (float i = -5.0; i <= 5.0; i += 1.0) {
				for (float j = -5.0; j <= 5.0; j += 1.0) {
					
					col_fin += texture(u_texture, v_uv + vec2(i, j) / mida) / 121.0; 
				}
			}
			gl_FragColor = col_fin;
		}
	}
	else if(u_tecla==3){
		if(u_mode==1){
			vec4 color = texture(u_texture, vec2(v_uv.x, clamp(v_uv.y + 0.05*sin(v_uv.x*100+u_sec*2), 0.0, 1.0)));
			gl_FragColor = color;
		}
		if(u_mode==2){
			float p = u_sec;  
			float x_pixel= floor(v_uv.x * p) / p;
			float y_pixel= floor(v_uv.y * p) / p;
			vec4 col_fin = texture(u_texture, vec2(x_pixel, y_pixel));	
			gl_FragColor = col_fin;
		}
	}
	
}
