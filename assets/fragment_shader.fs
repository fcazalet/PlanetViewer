#version 450 core
out vec4 FragColor;

in float Height;
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  

const vec4 LANDS_1 = vec4( 67.0/255.0, 179.0/255.0,  53.0/255.0, 1.0 );
const vec4 LANDS_2 = vec4( 38.0/255.0, 110.0/255.0, 29.0/255.0, 1.0 );
const vec4 MOUNTAINS = vec4( 1.0, 1.0, 1.0, 1.0 );
const vec4 WATER   = vec4( 0, 0, 1, 1.0 );

float remap( float minval, float maxval, float curval )
{
    return ( curval - minval ) / ( maxval - minval );
}
void main()
{
    float h = (Height + 16)/32.0f;	// shift and scale the height into a grayscale value
    if (h <= 0.0) {
        FragColor = WATER;
    }
    else if (0.0 < h && h < 0.3){
        FragColor = mix( LANDS_1, LANDS_2, remap( 0.0, 0.3, h ) );
    }
    else{
        FragColor = vec4(h, h, h, 1.0);
    }
    // FragColor = vertexColor;
}

