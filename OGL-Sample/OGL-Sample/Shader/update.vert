	#version 420 core
	//#extension GL_EXT_gpu_shader4: enable

	layout(std140, binding = 0)uniform Matrix{
		mat4 u_projection_view_matrix;
		mat4 u_model_matrix;
	};

	layout(location = 0) in vec3 a_position;
	layout(location = 1) in vec3 a_velocity;
	
	out vec3 out_position;
	out vec3 out_velocity;

	float u_time_step=0.02;

	int LFSR_Rand_Gen(in int n)
	{
 	 // <<, ^ and & require GL_EXT_gpu_shader4.
  		n = (n << 13) ^ n; 
 		return (n * (n*n*15731+789221) + 1376312589) & 0x7fffffff;
	}

	float LFSR_Rand_Gen_f( in int n )
	{
 		return float(LFSR_Rand_Gen(n));
	}

	float noise3f(in vec3 p)
	{
	  ivec3 ip = ivec3(floor(p));
	  vec3 u = fract(p);
	  u = u*u*(3.0-2.0*u);

	  int n = ip.x + ip.y*57 + ip.z*113;

	  float res = mix(mix(mix(LFSR_Rand_Gen_f(n+(0+57*0+113*0)),
	                          LFSR_Rand_Gen_f(n+(1+57*0+113*0)),u.x),
	                      mix(LFSR_Rand_Gen_f(n+(0+57*1+113*0)),
	                          LFSR_Rand_Gen_f(n+(1+57*1+113*0)),u.x),u.y),
	                 mix(mix(LFSR_Rand_Gen_f(n+(0+57*0+113*1)),
	                          LFSR_Rand_Gen_f(n+(1+57*0+113*1)),u.x),
	                      mix(LFSR_Rand_Gen_f(n+(0+57*1+113*1)),
	                          LFSR_Rand_Gen_f(n+(1+57*1+113*1)),u.x),u.y),u.z);

	  return 1.0 - res*(1.0/1073741824.0);
	}

	void main(){
		vec3 acceleration =vec3(noise3f(vec3(1.2,0.3,2.0)))*vec3(200.0,1000.0,0.0);
		//vec3 acceleration=vec3(0.0,-1000.0,0.0);
		vec3 new_velocity=a_velocity+acceleration*u_time_step;
		vec3 new_position=a_position+new_velocity*u_time_step;

		out_velocity=new_velocity*0.9999;
		out_position=new_position;
		gl_PointSize=5.0;
		gl_Position=u_projection_view_matrix*u_model_matrix*vec4(a_position,1.0);
	}