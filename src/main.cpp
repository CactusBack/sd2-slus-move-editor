#include "ui/MainWindow.h"
#include "ui/UI.h"
#include "data/MoveEntry.h"
#include "renderer/Renderer.h"
#include "data/SlusFile.h"
#include "data/WazaFile.h"

#include <vector>

int main()
{
    // Init renderer
    GLFWwindow* window = InitRenderer();
    if (!window)
        return -1;

    // Init UI
    UIState uiState{};
    InitUI(uiState);

    // Load font
    UpdateFont(uiState);

    // Load move data from SLUS
    SlusFile slus{ .filePath = "SLUS_012.34" };
    std::vector<MoveEntry> moveEntriesOld;
    std::vector<MoveEntry> moveEntriesNew;
    uiState.tabNew = LoadSlus(slus, moveEntriesOld, moveEntriesNew);

    // Parse move names from WAZA
    WazaFile waza{ .filePath = "WAZA.dat" };
    LoadWaza(waza);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwWaitEvents();

        UpdateFont(uiState);

        BeginFrame();

        DrawMainWindow(window, uiState, slus, waza, moveEntriesOld, moveEntriesNew);

        EndFrame(window);
    }

    // Cleanup
    ShutdownRenderer(window);

    return 0;
}