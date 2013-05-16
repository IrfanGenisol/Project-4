#version 120

//
//Homework#4 changes Irfan Genisol
//


//uniform sampler2D fbo_texture;
//uniform float offset;

varying vec2 f_texcoord;
uniform sampler2D inTexture;
uniform sampler2D gradientTexture;


vec4 inColor;  //for input texture color
vec3 outColor; //for output texture color which is changed step by step

void main(void) {
//    vec2 texcoord = f_texcoord;
//    texcoord.x += sin(texcoord.y * 4*2*3.14159 + offset) / 100;
//    gl_FragColor = texture2D(fbo_texture, f_texcoord);
    
    inColor = texture2D(inTexture, f_texcoord);
    outColor.r = texture2D(gradientTexture, vec2(inColor.r, 1)).r;
    outColor.g = texture2D(gradientTexture, vec2(inColor.g, 1)).g;
    outColor.b = texture2D(gradientTexture, vec2(inColor.b, 1)).b;
    gl_FragColor= vec4(outColor, 1.0);
}




  



	