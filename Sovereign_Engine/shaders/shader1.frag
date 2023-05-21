#version 330 core

in vec3 color;
out vec4 FragColor;


void main()
{
	vec2 resolution = vec2(800, 600);
	vec2 uv = gl_FragCoord.xy / resolution;
	
	if(uv.x < 0.5) {
		FragColor = vec4(color, 1.f);
	}
	else {
	
		FragColor = vec4(color.z, -color.y, color.x, 1.0f);
	}

}