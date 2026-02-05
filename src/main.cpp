#include "ui/AppState.h"
#include "ui/MainWindow.h"
#include "data/MoveEntry.h"
#include "renderer/Renderer.h"
#include "data/SlusFile.h"
#include "data/WazaFile.h"

#include <vector>

int main()
{
    // Setup renderer
    GLFWwindow* window = InitRenderer();
    if (!window)
        return -1;

    // Init app state
    AppState appState{ true, true};

    // Load move data from SLUS
    SlusFile slus{ .filePath = "SLUS_012.34" };
    std::vector<MoveEntry> moveEntriesOld;
    std::vector<MoveEntry> moveEntriesNew;
    appState.tabNew = LoadSlus(slus, moveEntriesOld, moveEntriesNew);

    // Parse move names from WAZA
    WazaFile waza{ .filePath = "WAZA.dat" };
    LoadWaza(waza);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwWaitEvents();

        BeginFrame();

        DrawMainWindow(window, appState, slus, waza, moveEntriesOld, moveEntriesNew);

        EndFrame(window);
    }

    // Cleanup
    ShutdownRenderer(window);

    return 0;
}