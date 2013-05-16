//
//  SimpleEffect.h
//  Ders 7
//
//  Created by Gurel Erceis on 4/15/13.
//  Copyright (c) 2013 Yogurt3D. All rights reserved.
//



#ifndef Ders_7_SimpleEffect_h
#define Ders_7_SimpleEffect_h
#include "Effect.h"
#include "SOIL.h"

class SimpleEffect: public Effect{
    //
    //Homework#4 changes Irfan Genisol
    //
private:
    //GLuint UniformOffset;
    GLuint UniformTexture;
    GLuint UniformGradient;
public:
    //for loading texture with using SOIL
    GLint LoadGLTexture(const char *filename)
	{
		GLuint _texture;
		_texture = SOIL_load_OGL_texture
		(
		 filename,
		 SOIL_LOAD_AUTO,
		 SOIL_CREATE_NEW_ID,
		 SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		 );
        
		if(_texture == 0) {
			printf( "[ERROR] SOIL loading error: '%s'\n", SOIL_last_result() );
		}
        
		glBindTexture(GL_TEXTURE_2D, _texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		return _texture;
	}
    
    SimpleEffect(int* screen_width, int* screen_height):Effect("effect_simple.frag",screen_width, screen_height){
            
        UniformTexture = glGetUniformLocation(programID, "inTexture");
        UniformGradient = glGetUniformLocation(programID, "gradientTexture");
        
//        //for control binding the textures
//        
//        if (UniformOffset == -1) {
//            fprintf(stderr, "Could not bind attribute %s\n", "offset");
//        }
//        if (UniformTexture == -1) {
//            fprintf(stderr, "Could not bind attribute %s\n", "inTexture");
//        }
//        if (UniformGradient == -1) {
//            fprintf(stderr, "Could not bind attribute %s\n", "gradientTexture");
//        }
        
    }
    
    
    virtual void draw(){
//        GLfloat move = glutGet(GLUT_ELAPSED_TIME) / 1000.0 * 2*3.14159 * .75;  // 3/4 of a wave cycle per second
//		glUniform1f(UniformOffset, move);
        
        glUseProgram(programID);

		glActiveTexture(GL_TEXTURE1); //for the main texture
		LoadGLTexture("/Users/irfangenisol/Desktop/Ders 7/lion.jpg");
        glUniform1i(UniformTexture, 1);
        
		glActiveTexture(GL_TEXTURE2); //for the gradient texture
		LoadGLTexture("/Users/irfangenisol/Desktop/Ders 7/gradientTexture.jpg");
        glUniform1i(UniformGradient, 2);
        
        glActiveTexture(GL_TEXTURE0);  //for the fbo
        Effect::draw();
    }
};

#endif
