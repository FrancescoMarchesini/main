#ifndef __LOAD_IMAGE_H
#define __LOAD_IMAGE_H

//dds è un file compresso che è direttamente compatibile con la GPU
//e quindi non vi è necessita di fare la conversione a run time che
//riduce le prestazioni

/**
 * @brief loadDDS carica file imaggine compresso dds
 * @param imagePath path del file
 * @return
 */
GLuint loadDDS(const char* imagePath);

GLuint createDDSTexture(unsigned int format,  unsigned char * buffer, unsigned int mipMapCount, unsigned int width, unsigned int height);



#endif
