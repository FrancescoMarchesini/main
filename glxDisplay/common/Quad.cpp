#define STB_IMAGE_IMPLEMENTATION
#include "../common/stb_image.h"

#include "Quad.h"

//spefifico i vertici del triangolo nelle cordinate
//"normalized device coordinate"(NDC) 3 punti per ogni vertice
const float Quad::vertices[32]{
             // posizione          // colore           // tcoordinare  texure
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f,  1.0f, // top right
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f,  0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f,  0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f,  1.0f  // top left
};

const GLint Quad::indici[6]{
    0, 1, 3, //primo triangolo
    1, 2, 3
};

Quad::~Quad()
{

}

Quad::Quad()
{
    shader = NULL;
    //vbo = 0;
    //vao = 0;
}

Quad* Quad::create()
{
    Quad * q = new Quad();
    if(!q->init())
    {
         printf("%sErrore a creare l'instanza del quadrato\n", LOG_QUAD_ERROR);
         delete q;
         return NULL;
    }
    return q;
}

bool Quad::initBuffers()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    printf("%sGenerato i buffer VAO, VBO, EBO, TEX\n", LOG_QUAD_INFO);

    //VAO
    glBindVertexArray(vao);
    //VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indici), indici, GL_STATIC_DRAW);
    printf("%sBind dei buffer e copia dati da host a device per VBO EBO VAO TEX\n", LOG_QUAD_INFO);

    //determino come OpenGl interpreta i vertici caricati
    //ovvero come sono stati caricati i dati nell buffer e quindi come sono organizzati
    //0        : layout(postion = 0) quale attributo vogliamo configurazione in questo caso la pos quindi 0
    //3        : il numero di vertici
    //GL_FLOAT : che tipo dato è
    //GL_FALSE : il dato deve essere normalizzato ? in questo caso non in quanto gia normalizzato
    //STRIDE   : ogni vertice è foramto da 4 byte ovvero 12 bit qui si determina come vengono messi in successione
    //           in questo caso tra un ogni vertice è continuo al succesivo senza interruzioni
    //(void*)0 : dove inizia la posizone del buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    printf("%sAttributi della posisione\n", LOG_QUAD_INFO);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    printf("%sAttributi del color\n", LOG_QUAD_INFO);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    printf("%sAttributi della posizone delle textcord\n", LOG_QUAD_INFO);

    return true;
}

bool Quad::initTexture(const char* paths)
{
    //tex
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //setto di rosso i bordi della texture
    float color[] = {1.0f, 1.0f, 0.0f, 1.0f };
    glTextureParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
    //interpolazione lineare dei pixel
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    printf("%sParametri di visualizzazione delle texture\n", LOG_QUAD_INFO);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(paths, &width, &height, &nrChannels, 0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D,  0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("%sFallito a caricare il File\n", LOG_QUAD_ERROR);
    }
    stbi_image_free(data);
    printf("%sCaricaro il file nella texture\n", LOG_QUAD_INFO);

    return true;
}

bool Quad::init()
{
    //init degli shader
    shader = Shader::create("../data/shader/quad.vertexshader", "../data/shader/quad.fragmentshader");
    if(!shader)
    {
        printf("%sFallito a caricare gli shader\n", LOG_QUAD_ERROR);
        return NULL;
    }

    if(!initBuffers())
    {
        printf("%sFallito a caricare uno dei buffer\n", LOG_QUAD_ERROR);
        return NULL;
    }

    if(!initTexture("../data/image/container.jpg"))
    {
        printf("%sFallito a caricare uno dei buffer\n", LOG_QUAD_ERROR);
        return NULL;
    }

    //unbind degli oggetti
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    printf("%sUnBind dei buffer\n", LOG_QUAD_INFO);

    printf("%sInit del Quad Fatto Passo al disegno\n", LOG_QUAD_INFO);
    return true;
}

void Quad::draw()
{

    printf("ok");
    if(tex)
        glBindTexture(GL_TEXTURE_2D, tex);

    // Draw a triangle from the 3 vertices
    shader->use();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Quad::cleanQuad()
{
    printf("%sCancello Tutto\n", LOG_QUAD_INFO);
    shader->deleteShader();
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &ebo);

}
