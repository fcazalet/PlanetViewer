#version 450 core  // 420, 330 core , compatibility
//layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
in vec4 position
layout(location = 7) uniform mat4 view_matrix;
out vec4 vertexColor; // specify a color output to the fragment shader

void main()
{
    gl_Position = view_matrix * position; // see how we directly give a vec3 to vec4's constructor
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
}
