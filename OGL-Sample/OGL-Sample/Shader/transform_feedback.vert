	#version 420 core 
	uniform mat4 u_model_matrix; 
	uniform mat4 u_projection_view_matrix;
	layout(location = 0) in vec3 v_position; 
	layout(location = 1) in vec3 v_normal; 
	layout(location = 2) in vec2 v_texcoord; 
	out vec4 world_space_position; 
	out vec3 world_space_normal; 
	out vec2 f_texcoord; 
	void main(){ 
		world_space_position=u_model_matrix*vec4(v_position,1.0); 
		world_space_normal=(u_model_matrix*vec4(v_normal,1.0)).xyz; 
		f_texcoord=v_texcoord; 
		gl_Position=u_projection_view_matrix*world_space_position; 
	}