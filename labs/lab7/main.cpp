#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include <csci441/shader.h>
#include <csci441/matrix.h>
#include <csci441/matrix3.h>
#include <csci441/vector.h>
#include <csci441/uniform.h>

#include "shape.h"
#include "camera.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

bool isPressed(GLFWwindow *window, int key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool isReleased(GLFWwindow *window, int key) {
    return glfwGetKey(window, key) == GLFW_RELEASE;
}

Matrix processModel(const Matrix& model, GLFWwindow *window) {
    Matrix trans;

    const float ROT = 1;
    const float SCALE = .05;
    const float TRANS = .01;

    // ROTATE
    if (isPressed(window, GLFW_KEY_U)) { trans.rotate_x(-ROT); }
    else if (isPressed(window, GLFW_KEY_I)) { trans.rotate_x(ROT); }
    else if (isPressed(window, GLFW_KEY_O)) { trans.rotate_y(-ROT); }
    else if (isPressed(window, GLFW_KEY_P)) { trans.rotate_y(ROT); }
    else if (isPressed(window, '[')) { trans.rotate_z(-ROT); }
    else if (isPressed(window, ']')) { trans.rotate_z(ROT); }
    // SCALE
    else if (isPressed(window, '-')) { trans.scale(1-SCALE, 1-SCALE, 1-SCALE); }
    else if (isPressed(window, '=')) { trans.scale(1+SCALE, 1+SCALE, 1+SCALE); }
    // TRANSLATE
    else if (isPressed(window, GLFW_KEY_UP)) { trans.translate(0, TRANS, 0); }
    else if (isPressed(window, GLFW_KEY_DOWN)) { trans.translate(0, -TRANS, 0); }
    else if (isPressed(window, GLFW_KEY_LEFT)) { trans.translate(-TRANS, 0, 0); }
    else if (isPressed(window, GLFW_KEY_RIGHT)) { trans.translate(TRANS, 0, 0); }
    else if (isPressed(window, ',')) { trans.translate(0,0,TRANS); }
    else if (isPressed(window, '.')) { trans.translate(0,0,-TRANS); }

    return trans * model;
}

bool isSpaceEvent(GLFWwindow *window) {
    static bool pressed = false;

    bool trigger = false;
    if (isPressed(window, GLFW_KEY_SPACE)) {
        pressed = true;
    } else if (pressed && isReleased(window, GLFW_KEY_SPACE)) {
        pressed = false;
        trigger = true;
    }
    return trigger;
}

void processInput(Matrix& model, GLFWwindow *window) {
    if (isPressed(window, GLFW_KEY_ESCAPE) || isPressed(window, GLFW_KEY_Q)) {
        glfwSetWindowShouldClose(window, true);
    } else if (isSpaceEvent(window)) {
        /**
         * TODO: PART-6 for demo, add code here to change the mode without
         * having massive flickering
         **/
    }
    model = processModel(model, window);
}

void errorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error: %s\n", description);
}

GLuint createTexture() {
    GLuint textureID;

    /**
     * TODO: Part-2 create the checker texture
     */

    return textureID;
}

GLuint loadTexture(const std::string& path, bool flip=true) {
    GLuint textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(flip);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format = 0;
        switch (nrComponents) {
            case 1: format = GL_RED; break;
            case 3: format = GL_RGB; break;
            case 4: format = GL_RGBA; break;
        }

        /**
         * TODO: Part-3 create a texture map for an image
         */

        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

int main(void) {
    GLFWwindow* window;

    glfwSetErrorCallback(errorCallback);

    /* Initialize the library */
    if (!glfwInit()) { return -1; }

    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CSCI441-lab", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // tell glfw what to do on resize
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // init glad
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return -1;
    }

    // setup camera
    Matrix projection;
    projection.perspective(45, 1, .01, 10);

    Camera camera;
    camera.projection = projection;
    camera.eye = Vector(0, 0, 3);
    camera.origin = Vector(0, 0, 0);
    camera.up = Vector(0, 1, 0);

    // setup the shader
    Shader shader("../vert.glsl", "../frag.glsl");

    /* init the shape */
    Cube shape;
    // Sphere shape(20, 1);

    // copy vertex data
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, shape.size(), shape.data(), GL_STATIC_DRAW);

    // describe vertex layout
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // setup position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /** TODO: Part1 add vertex attribute pointer for texture coordinates */

    // and use z-buffering
    glEnable(GL_DEPTH_TEST);

    // init the model matrix
    Matrix model;

    // setup the textures
    /** TODO: Part2 create and bind the texture. */

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        // process input
        processInput(model, window);

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // render the object
        shader.use();
        Uniform::set(shader.id(), "model", model);
        Uniform::set(shader.id(), "projection", camera.projection);
        Uniform::set(shader.id(), "camera", camera.look_at());
        Uniform::set(shader.id(), "eye", camera.eye);

        // render the cube
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, shape.size());

        /* Swap front and back and poll for io events */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
