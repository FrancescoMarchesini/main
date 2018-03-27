#include "../common/openGLText2D.h"

openGLText::~openGLText()
{
    //qui dovrebbe andarci
    //glDeleteTextures(1,&textureID);
    //e forse cneh tutto il resto della funzione cleanUP... ??
}

openGLText::openGLText()
{
   // textureID       = 0;
   // vertexBufferID  = 0;
   // UVBufferID      = 0;
    shader          = NULL;
   // Uniform2DID     = 0;
}

openGLText* openGLText::create(const char *texturePath)
{
    openGLText * tex = new openGLText();
    if(!tex->init(texturePath))
    {
        printf("%sfallito a creare l'instanza della classe\n", LOG_TEXT_ERRORE);
        delete tex;
        return NULL;
    }

    return tex;
}


bool openGLText::init(const char *texturePath)
{
    textureID = loadDDS(texturePath);
    printf("%sCaricato image.DDS e creato la texture\n", LOG_TEXT_INFO);

    //inizializzo gli shader
    shader = Shader::create("./data/shader/text2d.vertexshader", "./data/shader/text2d.fragmentshader" );
    if(!shader)
    {
        printf("%sfallito caricare gli shader\n", LOG_TEXT_ERRORE);
        return NULL;
    }
    printf("%sCaricato gli shader\n", LOG_TEXT_INFO);

    Uniform2DID = glGetUniformLocation(shader->getID(), "myTextureSampler" );

    //Initiliazzo il vertex buffer object
    glGenBuffers(1, &vertexBufferID);
    //inizializzo il buffer per le coordinate UV
    glGenBuffers(1, &UVBufferID);

    return true;
}

bool openGLText::drawTexture(const std::vector<vec2> &vertici, const std::vector<vec2> &UVs)
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, vertici.size() * sizeof(glm::vec2), &vertici[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, UVBufferID);
    glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);
  //printf("%sUpload dati da host to Device\n", LOG_TEXT_INFO);

    shader->use();
  //printf("%sAttivato lo shader\n", LOG_TEXT_INFO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glUniform1i(Uniform2DID, 0);
  //printf("%sBind della texture\n", LOG_TEXT_INFO);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
  //printf("%sSettato la struttura dati del buffer ed attivato gli attrib pos\n", LOG_TEXT_INFO);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, UVBufferID);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
  //printf("%sSettato la struttura dati del buffer ed attivato gli attrib pos\n", LOG_TEXT_INFO);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //printf("%sAttivato funzioni gl per bland\n", LOG_TEXT_INFO);

    glDrawArrays(GL_TRIANGLES, 0, vertici.size());
  //printf("%sDisegno\n", LOG_TEXT_INFO);

    glDisable(GL_BLEND);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
  //printf("%sCancellato il buffer\n", LOG_TEXT_INFO);
}

void openGLText::printText(const char *text, int x, int y, int size)
{
    unsigned int lenght = strlen(text);
    //printf("%slunghezza del testo :%d\n", LOG_TEXT_INFO, lenght);

    //un quadrato di 4 vertici contenete la lettera, formato da due triangoli
    std::vector<glm::vec2> vertici;
    //la mappatura dei vertici in cordinate normalizzate per gli shader
    std::vector<glm::vec2> UVs;

    //Per ogni carattere presente nella texture caricate carico nel vertices i 4 vertici
    //di ogni quadrato contente la lettere
    //allo stesso modo per ogni quadrato creao due triangoli rappresentati delle coordinate UV
    for(unsigned int i=0; i<lenght; i++)
    {
        glm::vec2 vertice_alto_sinistra     = glm::vec2( x+i*size        , y+size);
        glm::vec2 vertice_alto_destra       = glm::vec2( x+i*size+size   , y+size);
        glm::vec2 vertice_basso_destra      = glm::vec2( x+i*size+size   , y     );
        glm::vec2 vertice_basso_sinistra    = glm::vec2( x+i*size        , y     );

        //carico i vertice del traingolo alto nel vettore
        vertici.push_back(vertice_alto_sinistra);
        vertici.push_back(vertice_basso_sinistra);
        vertici.push_back(vertice_alto_destra);

        //carico i vertice del triangolo basso nel vettore
        vertici.push_back(vertice_basso_destra);
        vertici.push_back(vertice_alto_destra);
        vertici.push_back(vertice_basso_sinistra);
        //printf("%sAbbiamo il quadrato numero = %d\n", LOG_TEXT_INFO, i);

        //calcolo delle cordinate UV per ogni lettera
        char character = text[i];
       // printf("%smappo in UV la lettera = %d\n", LOG_TEXT_INFO, text[i]);
        //character è la rabbresentazione in asci delle lettere A = 65 .. Z = 58
        //tramite il modulo di 16 la A concide con 1 la B con 2 e cosi via sia per la x che y
        //divido per 16 in modo da mappare le cordinate tra [0.0-1.0]
        //in tal modo a partire dalla texture o la posizione dei caratteri ??
        float uv_x = (character%16)/16.0f;
        float uv_y = (character/16)/16.0f;
       // printf("%suv_x = %.3f X uv_y = %.3f\n", LOG_TEXT_INFO, uv_x, uv_y);

        //calcolo il triangolo alto a destra nelle cordinate UV
        glm::vec2 uv_alto_sinistra = glm::vec2(uv_x             , uv_y);
        glm::vec2 uv_alto_destra   = glm::vec2(uv_x+1.0f/16.0f  , uv_y);
        glm::vec2 uv_basso_destra  = glm::vec2(uv_x+1.0f/16.0f  , (uv_y + 1.0f/16.0f));
        glm::vec2 uv_basso_sinistra = glm::vec2(uv_x             , (uv_y + 1.0f/16.0f));

        //carico i vertici appena creati nel nel vettore triangolo alto destra
        UVs.push_back(uv_alto_sinistra);
        UVs.push_back(uv_basso_sinistra);
        UVs.push_back(uv_alto_destra);

        //carico i vertici appena creati nel nel vettore triangolo alto destra
        UVs.push_back(uv_basso_destra);
        UVs.push_back(uv_alto_destra);
        UVs.push_back(uv_basso_sinistra);
       // printf("%sAbbiamo il quadrato Nelle cordinate UV  = %d\n", LOG_TEXT_INFO, i);

    }

    drawTexture(vertici, UVs);

}

void openGLText::cleanupText2D()
{
    printf("%sCancello buffer shader e texture\n", LOG_TEXT_INFO);
    glDeleteBuffers(1, &vertexBufferID);
    glDeleteBuffers(1, &UVBufferID);
    glDeleteTextures(1,&textureID);
    shader->deleteShader();
}

