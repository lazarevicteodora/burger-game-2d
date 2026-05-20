#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

int endProgram(std::string message);
unsigned int createShader(const char* vsSource, const char* fsSource);
unsigned loadImageToTexture(const char* filePath);
GLFWcursor* loadImageToCursor(const char* filePath);

// Nove funkcije
unsigned int createQuad();
void drawTexture(unsigned int texture, float x, float y, float width, float height,
    float alpha = 1.0f, float rTint = 1.0f, float gTint = 1.0f, float bTint = 1.0f);
void drawRect(float x, float y, float width, float height, float r, float g, float b, float a = 1.0f);
void setShaderProgram(unsigned int program);