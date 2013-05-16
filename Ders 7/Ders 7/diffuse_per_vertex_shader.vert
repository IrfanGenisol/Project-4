#version 120

// sabit degiskenler
uniform mat4 MVP,ModelView;

// diziden alinacak degiskenler
attribute vec4 Position;
attribute vec3 Normal;

// fragment shader'a aktarilacak veriler
varying vec4 color;

// vertex shader main metodu
void main()
{	
    // camera space position
    vec3 vVertex = vec3(ModelView * Position);
    // camera space normal
    vec3 normal = mat3(ModelView)*Normal;
    
    vec3 lightDir = vec3(gl_LightSource[0].position.xyz - vVertex);
	vec3 eyeVec = -vVertex;
    
    vec3 N = normal;
	vec3 L = normalize(lightDir);
	
	float intensity = dot(N,L);
    
    color = gl_LightSource[0].ambient;
    
    color += gl_LightSource[0].diffuse * intensity;
    
    if(intensity > 0.0)
    {
        vec3 E = normalize(eyeVec);
		vec3 R = reflect(-L, N);
        //float specular = pow( max(dot(R, E), 0.0), 32 );
        //color += gl_LightSource[0].specular * specular;
        
        //Irfan Genisol
        //FRESNEL EFFECT ON GLSL HOMEWORK#3
        
        //Homework#3 changes without bonus
        //Oppositte the camera is red, other sides are blue
        vec4 colorOne=vec4(1.0, 0.0, 0.0, 1.0);  //Red
        vec4 colorTwo=vec4(0.0, 0.0, 1.0, 1.0);  //Blue
        float fresnelWithcosx=max(dot(N,E), 0.0);  //Normal and eyevector dot product result
        vec4 twoColorFresnelEffect=mix(colorOne, colorTwo, fresnelWithcosx);
        color=twoColorFresnelEffect;
        
        
        //
        //        //Homework#3 changes with bonus
        //        vec4 colorOne=vec4(1.0, 0.0, 0.0, 1.0);  //Red
        //        vec4 colorTwo=vec4(0.0, 0.0, 1.0, 1.0);  //Blue
        //        float r0=0.2;  //Fresnel reflectance is random number for meaningfull
        //        float r1=1.5;  //Fresnel power is random number for meaningful
        //
        //        float cosx=dot(N,E);  //Normal and eyevector dot product result
        //        float fresnelWitBonus=( r0 + (1-r0)*pow((1+cosx), r1) );
        //        vec4 twoColorFresnelEffect=mix(colorOne, colorTwo, fresnelWitBonus);
        //        color=twoColorFresnelEffect;
        //

	}
    
    gl_Position = MVP * Position;
}
	
