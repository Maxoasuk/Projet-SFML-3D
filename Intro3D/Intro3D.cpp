// Intro3D.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.

#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"
#include "Object.h"
#include "Texture.h"

// Points of triangle
float vertices[] = {
    //Face avant
     0.5f, -0.5f, 0.5f, 1.f, 1.f, // R-D
     0.5f,  0.5f, 0.5f, 1.f, 0.f, // R-T
    -0.5f, -0.5f, 0.5f, 0.f, 1.f, // L-D
    -0.5f, -0.5f, 0.5f, 0.f, 1.f, // L-D
     0.5f,  0.5f, 0.5f, 1.f, 0.f, // R-T
    -0.5f,  0.5f, 0.5f, 0.f, 0.f, // 
    //Face droite
    0.5f, -0.5f,  0.5f, 0.f, 1.f,
    0.5f,  0.5f,  0.5f, 0.f, 0.f,
    0.5f,  0.5f, -0.5f, 1.f, 0.f,
    0.5f, -0.5f,  0.5f, 0.f, 1.f,
    0.5f, -0.5f, -0.5f, 1.f, 1.f,
    0.5f,  0.5f, -0.5f, 1.f, 0.f,
    //Face gauche
    -0.5f, -0.5f,  0.5f, 1.f, 1.f,
    -0.5f,  0.5f,  0.5f, 1.f, 0.f,
    -0.5f,  0.5f, -0.5f, 0.f, 0.f, 
    -0.5f, -0.5f,  0.5f, 1.f, 1.f, 
    -0.5f, -0.5f, -0.5f, 0.f, 1.f, 
    -0.5f,  0.5f, -0.5f, 0.f, 0.f,
    //Face haute
    -0.5f, 0.5f,  0.5f, 0.f, 1.f,
     0.5f, 0.5f,  0.5f, 1.f, 1.f,
    -0.5f, 0.5f, -0.5f, 0.f, 0.f,
     0.5f, 0.5f,  0.5f, 1.f, 1.f,
     0.5f, 0.5f, -0.5f, 1.f, 0.f,
    -0.5f, 0.5f, -0.5f, 0.f, 0.f,
    //Face basse
    -0.5f, -0.5f,  0.5f, 0.f, 0.f,
     0.5f, -0.5f,  0.5f, 1.f, 0.f,
    -0.5f, -0.5f, -0.5f, 0.f, 1.f,
     0.5f, -0.5f,  0.5f, 1.f, 0.f,
     0.5f, -0.5f, -0.5f, 1.f, 1.f,
    -0.5f, -0.5f, -0.5f, 0.f, 1.f,
    // Face arrière
     0.5f, -0.5f, -0.5f, 1.f, 1.f,
     0.5f,  0.5f, -0.5f, 1.f, 0.f,
    -0.5f, -0.5f, -0.5f, 0.f, 1.f,
    -0.5f, -0.5f, -0.5f, 0.f, 1.f,
     0.5f,  0.5f, -0.5f, 1.f, 0.f,
    -0.5f,  0.5f, -0.5f, 0.f, 0.f,
};

//Constants
const unsigned int WIDTH_SCREEN = 800;
const unsigned int HEIGHT_SCREEN = 800;

int main()
{
    
    Window window;
    window.init();
    if (!window.create(WIDTH_SCREEN, HEIGHT_SCREEN, "coursOpenGL")) {
        std::cout << "The window cannot be created" << std::endl;
        return -1;
    };
    

    Shader shader("./vertexShader.shader", "./fragmentShader.shader");
    window.setShader(&shader);

    Shader shaderLight("vertexLight.shader", "fragmentLight.shader");
    glm::vec3 lightPosition(2, 2, -2);

    Object object = Object("./teapot.obj");
    object.SetVertexAttribute(0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    //object.SetVertexAttribute(1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    object.SetVertexAttribute(2, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    Object light = Object((void*)vertices, sizeof(vertices));
    light.SetVertexAttribute(0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);

    Camera* camera = window.getCamera();
    camera->setPosition(0.0f, 0.0f, 5.0f);
    camera->setRotation(180.f, 0.f);
    //glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)WIDTH_SCREEN / (float)HEIGHT_SCREEN, 0.1f, 100.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));

    shader.Use();
    shader.SetInt("tex", 0);
    shader.SetVector3("lightColor", 1.0f, 1.0f, 1.0f);
    shader.SetVector3("objectColor", 1.0f, 1.0f, 1.0f);
    shader.SetFloat("ambientStrength", 0.3f);
    shader.SetVector3("lightPos", lightPosition);
    shader.SetVector3("viewPos", 0.0f, 0.0f, 5.0f);
    shader.SetMatrix4("projection", projection);
    shader.SetMatrix4("view", window.getCamera()->getView());
    shader.SetMatrix4("model", model);

    shaderLight.Use();

    shaderLight.SetMatrix4("projection", projection);
    shaderLight.SetMatrix4("view", window.getCamera()->getView());
    glm::mat4 modelLight = glm::mat4(1.0f);
    modelLight = glm::translate(modelLight, lightPosition);
    modelLight = glm::scale(modelLight, glm::vec3(0.2f, 0.2f, 0.2f));
    shaderLight.SetMatrix4("model", modelLight);
   
    Texture tex;
    tex.load("./cat.jpg");

    double currentFrame = glfwGetTime();
    double lastFrame = currentFrame;
    double deltaTime;
    /*Texture roche;
    roche.load("./roche.png");*/
    float angle = 1.0f;
    while (window.isOpen()) {
        if (window.isKeyPressed(GLFW_KEY_ESCAPE)) {
            window.close();
            break;
        }

        window.pollEvents();
        window.clear(0.2f, 0.2f, 0.2f);
        shader.Use();
        
        model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.SetMatrix4("model", model);
        shader.SetMatrix4("view", window.getCamera()->getView());
        //tex.active();
        object.draw(GL_TRIANGLES, 0, 5000000);

        shaderLight.Use();
        shaderLight.SetMatrix4("view", window.getCamera()->getView());
       
        light.draw(GL_TRIANGLES, 0, 36);

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        window.update(deltaTime);
        window.getCamera()->udpate(&window, deltaTime);
    }

    shader.Shutdown();
    shaderLight.Shutdown();
    //tex.desactive();

    return 0; 
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
