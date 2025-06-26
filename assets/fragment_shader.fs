#version 450 core
out vec4 FragColor;

in float Height;
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  

void main()
{
    // float h = (Height + 16)/32.0f;	// shift and scale the height into a grayscale value
    // FragColor = vec4(h, h, h, 1.0);
    FragColor = vertexColor;
}

