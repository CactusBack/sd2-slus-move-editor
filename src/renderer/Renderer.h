#pragma once

struct GLFWwindow;

GLFWwindow* InitRenderer(
    int width = 800,
    int height = 800,
    const char* title = "SD2 SLUS Move Editor");

void BeginFrame();
void EndFrame(GLFWwindow* window);
void ShutdownRenderer(GLFWwindow* window);