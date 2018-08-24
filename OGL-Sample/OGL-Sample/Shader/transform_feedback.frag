 	#version 420 core 
	uniform sampler2D s_diffuse; 
	in vec2 f_texcoord; 
	out vec4 r_color; 
	void main(){ 
		r_color = texture(s_diffuse,f_texcoord); 
	}