	#version 420 core 
	layout(std140, binding = 0)uniform Matrix{
		mat4 u_projection_view_matrix;
		mat4 u_model_matrix;
	};

	layout(location = 0) in vec3 v_position; 
	out vec3 world_space_position; 
	void main(){ 
		vec4 world_position=u_model_matrix*vec4(v_position,1.0); 
		world_space_position=v_position.xyz;
		gl_Position=u_projection_view_matrix*world_position; 
	}