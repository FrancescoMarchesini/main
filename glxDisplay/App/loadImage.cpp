#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

GLuint loadDDS(const char* imagePath)
{
    printf("[LOG_IMAGE ] carico Font\n");

    unsigned char header[124];

    FILE *fp;

   /* try to open the file */
   fp = fopen(imagePath, "rb");
   if (fp == NULL)
       return 0;

      //verfico il tipo di file
      char filecode[4];
      fread(filecode, 1, 4, fp);
      //strncmp fa una comparazione carattere per carattere tra string 1 e string 2
      //se i caratteri corrispondono passa al successivo
      if (strncmp(filecode, "DDS ", 4) != 0) {
          fclose(fp);
          printf("[LOG_IMAGE ] file NON corretto chiudo ed esco\n");
          return -1;
      }

    //leggo il file
    fread(&header, 124, 1, fp);

    //estraggo le inforamazioni necessarie
    unsigned int height = *(unsigned int*)&(header[8]);
    unsigned int width = *(unsigned int*)&(header[12]);
    unsigned int linearSize = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC = *(unsigned int*)&(header[80]);

    printf("[LOG_IMAGE ] height = %d width = %d \n[LOG_IMAGE ] linearSize = %d mipMapCount = % d fourCC = %d \n ", height,  width, linearSize, mipMapCount, fourCC);

    unsigned char * buffer;
    unsigned int bufsize;

    //mipMap sono secuenza di immagini pre-caclolate ed ottimizzate, ognuna delle quali ha progressivamente
    //una risuluzione minore della stessa immagine
    // es image size = 256 X 256
    //    mipMap = 128×128 pixels, 64×64, 32×32, 16×16, 8×8, 4×4, 2×2, 1×1
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    printf("[LOG_IMAGE ] bufferzie = %d \n", bufsize);
    fread(buffer, 1, bufsize, fp);

    fclose(fp);
    printf("[LOG_IMAGE ] caricamento in RAM del file, lo chiudo\n");

    //Converto i flag FourCC in un formato comprensibile da openGL
    //il FOURCC è il formato dei pixel per il file DDS
    unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;
    switch(fourCC)
        {
        case FOURCC_DXT1:
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case FOURCC_DXT3:
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case FOURCC_DXT5:
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            break;
        default:
            free(buffer);
            return 0;
        }

}
