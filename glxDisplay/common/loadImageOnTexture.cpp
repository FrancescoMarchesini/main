#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII


GLuint createDDSTexture(unsigned int format, unsigned char* buffer, unsigned int mipMapCount, unsigned int width, unsigned int height)
{
    //creo un texture OpenGL
    GLuint textureID;
     // @brief glGenTextures genereazione della texture
    // @param int numero di texture che si vogliono creare
     // @param texture un array di unsigned int nel quale memorizzare la texture stessa
    glGenTextures(1, &textureID);
    //bind della texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    //determino come i pixel vengano caricati nel buffer GPU iniziare ogni pixel come colonne(row)
    //in questo caso "1" : byte-alignament
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //determino la block size in base al formato dell'immagine caricata
    unsigned int blocksize = (format ==  GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
     printf("[LOG_IMAGE ] block size = %d \n", blocksize);
    unsigned int offset = 0;

    //carico le mimmaps iterando in tutti i livelli delle mipMap per la loro grandezza
    for(unsigned int level = 0; level  < mipMapCount && (width || height); ++level)
    {
        unsigned int size = ((width+3)/4) * ((height+3)/4) * blocksize;
        printf("[LOG_IMAGE ] H=%d W=%d size=%d\n", width, height, size);
        //genero la texture dall'immagine compressa dds
        printf("[LOG_IMAGE ] format =%d \n", format);
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);

        //alloco un array di pixel uno dopo l'altro quindi swifto della size ogni volta
        offset += size;
        //la grandezza ad ogni mipmap viene dimezzata
        width /= 2;
        height /= 2;
        //quando arrivo all'ultima mipmap tengo la w e h ad 1
        if(width < 1 ) width = 1;
        if(height < 1 ) height = 1;
    }

    //libero il buffer
    free(buffer);

    return textureID;
}


GLuint loadDDS(const char* imagePath)
{
    printf("[LOG_IMAGE ] carico Font\n");

    unsigned char header[124];

    FILE *fp;

  //try to open the file
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
        return 0;
    }

    //leggo il file
    fread(&header, 124, 1, fp);

    //estraggo le inforamazioni necessarie
    unsigned int height = *(unsigned int*)&(header[8]);
    unsigned int width = *(unsigned int*)&(header[12]);
    unsigned int linearSize = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC = *(unsigned int*)&(header[80]);

    printf("[LOG_IMAGE ] height = %d width = %d \n[LOG_IMAGE ] linearSize = %d mipMapCount = % d fourCC = %d \n", height,  width, linearSize, mipMapCount, fourCC);

    unsigned char * buffer;
    unsigned int bufsize;

    //mipMap sono secuenza di immagini pre-caclolate ed ottimizzate, ognuna delle quali ha progressivamente
    //una risuluzione minore della stessa immagine
    // es image size = 256 X 256
    //    mipMap = 128×128 pixels, 64×64, 32×32, 16×16, 8×8, 4×4, 2×2, 1×1
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    printf("[LOG_IMAGE ] buffersize = %d\n", bufsize);
    fread(buffer, 1, bufsize, fp);

    fclose(fp);
    printf("[LOG_IMAGE ] caricato file in ram, lo chiudo\n");

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

     printf("[LOG_IMAGE ] format = %d \n", format);
     return createDDSTexture(format, buffer, mipMapCount, width, height);

}

