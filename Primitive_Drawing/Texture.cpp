
#include "texture.h"
#include <string>
#include <iostream>

using namespace std;




	Texture::Texture(const std::string& fileName, int texUnit_)
	{
		
	
	
		unsigned char* data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);
		texUnit = texUnit_;
		if (data == NULL)
			cout << "Unable to load texture: " << fileName << endl;

		// 1- generate
		glGenTextures(1, &m_texture);
		// 2- bind
		glActiveTexture(texUnit);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		// 3- specifying parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		// 4- allocation
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 1);

		stbi_image_free(data);
	}



	Texture::Texture(unsigned char* data, int width, int height, int numComponents, int texUnit_)
	{

		// 1- generate
		glGenTextures(1, &m_texture);
		// 2- bind
		glActiveTexture(texUnit);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		// 3- specifying parameters
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// 4- allocation
		glTexImage2D(GL_TEXTURE_CUBE_MAP, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}
	void Texture::Bind()
	{
		glActiveTexture(texUnit);
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_texture);
	}




//GLuint Texture::loadBMP_custom(const char * imagepath)
//{
//	// Data read from the header of the BMP file
//unsigned char header[54]; // Each BMP file begins by a 54-bytes header
//unsigned int dataPos;     // Position in the file where the actual data begins
//
//unsigned int imageSize;   // = width*height*3
//// Actual RGB data

//
//// Open the file
//FILE * file = fopen(imagepath,"rb");
//if (!file)                              {printf("Image could not be opened\n"); return 0;}
//
//if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
//    printf("Not a correct BMP file\n");
//    return false;
//}
//if ( header[0]!='B' || header[1]!='M' ){
//    printf("Not a correct BMP file\n");
//    return 0;
//}
//// Read ints from the byte array
//dataPos    = *(int*)&(header[0x0A]);
//imageSize  = *(int*)&(header[0x22]);
//width      = *(int*)&(header[0x12]);
//height     = *(int*)&(header[0x16]);
//// Some BMP files are misformatted, guess missing information
//if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
//if (dataPos==0)      dataPos=54; // The BMP header is done that way
//// Create a buffer
//data = new unsigned char [imageSize];
// 
//// Read the actual data from the file into the buffer
//fread(data,1,imageSize,file);
// 
////Everything is in memory now, the file can be closed
//fclose(file);
//}