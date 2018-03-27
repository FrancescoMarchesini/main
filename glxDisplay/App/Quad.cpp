#include "Quad.h"

//spefifico i vertici del triangolo nelle cordinate
//"normalized device coordinate"(NDC) 3 punti per ogni vertice
const float Quad::vertices[12]{
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
   -0.5f, -0.5f, 0.0f,  // bottom left
   -0.5f,  0.5f, 0.0f   // top left
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


bool Quad::init()
{
    //init degli shader
    shader = Shader::create("../data/shader/quad.vertexshader", "../data/shader/quad.fragmentshader");
    if(!shader)
    {
        printf("%sFallito a caricare gli shader\n", LOG_QUAD_ERROR);
        return NULL;
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    printf("%sGenerato i buffer VAO, VBO, EBO\n", LOG_QUAD_INFO);

    //VAO
    glBindVertexArray(vao);
    //VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indici), indici, GL_STATIC_DRAW);
    printf("%sBind dei buffer e copia dati da host a device per VBO EBO VAO\n", LOG_QUAD_INFO);

    //determino come OpenGl interpreta i vertici caricati
    //ovvero come sono stati caricati i dati nell buffer e quindi come sono organizzati
    //0        : layout(postion = 0) quale attributo vogliamo configurazione in questo caso la pos quindi 0
    //3        : il numero di vertici
    //GL_FLOAT : che tipo dato è
    //GL_FALSE : il dato deve essere normalizzato ? in questo caso non in quanto gia normalizzato
    //STRIDE   : ogni vertice è foramto da 4 byte ovvero 12 bit qui si determina come vengono messi in successione
    //           in questo caso tra un ogni vertice è continuo al succesivo senza interruzioni
    //(void*)0 : dove inizia la posizone del buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    printf("%sSpecificato la struttura dati e attivato gli attributi\n", LOG_QUAD_INFO);

    //unbind degli oggetti
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    printf("%sUnBind dei buffer\n", LOG_QUAD_INFO);

    printf("%sInit del Quad Fatto Passo al disegno\n", LOG_QUAD_INFO);
    return true;
}

void Quad::draw()
{
    // Draw a triangle from the 3 vertices
    shader->use();
    glBindVertexArray(vao);
    //esendo che non disegno i vertici ma gli indici uso la seguente funzione
    //glDrawArrays(GL_TRIANGLES, 0, 3);
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
