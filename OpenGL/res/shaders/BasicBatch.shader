#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 TexCoord;
layout(location = 3) in float TexIndex;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;

uniform mat4 u_MVP;
uniform float u_Timer;

void main()
{

	mat4 view_frustum = mat4(
		vec4(1.0 / tan(radians(45.0)), 0.0, 0.0, 0.0),
		vec4(0.0, 4.0 / 3.0 / tan(radians(45.0)), 0.0, 0.0),
		vec4(0.0, 0.0, (5.0 + 0.5) / (5.0 - 0.5), 1.0),
		vec4(0.0, 0.0, -2.0 * 5.0 * 0.5 / (5.0 - 0.5), 0.0)
	);

	mat4 translate = mat4(
			vec4(1.0, 0.0, 0.0, 0.0),
			vec4(0.0, 1.0, 0.0, 0.0),
			vec4(0.0, 0.0, 1.0, 0.0),
			vec4(cos(u_Timer), 0.0, 3.0 + sin(u_Timer), 1.0)
		);

	mat4 rotation = mat4(
		vec4(1.0, 0.0, 0.0, 0.0),
		vec4(0.0, cos(u_Timer), sin(u_Timer), 0.0),
		vec4(0.0, -sin(u_Timer), cos(u_Timer), 0.0),
		vec4(0.0, 0.0, 0.0, 1.0)
	);

	gl_Position = view_frustum
		* translate
		* rotation
		* position;
   v_Color = color;
   v_TexCoord = TexCoord;
   v_TexIndex = TexIndex;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

uniform sampler2D u_Textures[2];

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;

void main()
{
	int index = int(v_TexIndex);
	//color = texture(u_Textures[index], v_TexCoord);
	color = v_Color;

};