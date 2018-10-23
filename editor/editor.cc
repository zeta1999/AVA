#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
// About OpenGL function loaders: modern OpenGL doesn't have a standard header file and requires individual function pointers to be loaded manually. 
// Helper libraries are often used for this purpose! Here we are supporting a few common ones: gl3w, glew, glad.
// You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif
#include <algorithm>
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <math.h>

/*
#include "engine.h"
*/
#define SHAPE_C
#include "render/render_shape.c"
#define EXPORT __declspec(dllexport)
#include <assert.h>
#define ASSERT assert
#include <stdint.h>
#define GL(...) __VA_ARGS__


#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include "imgui.h"
#include "imgui_internal.h"

// incl render/set_render
#include "imgui/imgui_videorec.cpp"

// legacy api stub
#define IsHovered(rect, id) \
    !!(ImGui::IsMouseHoveringRect(rect.Min, rect.Max) && ImGui::ItemHoverable(rect, id))

#include "imgui/imgui_config.cpp"
#include "imgui/imgui_fonts.cpp"
#include "imgui/imgui_palette.cpp"
#include "imgui/imgui_theme.cpp"
#include "imgui/imgui_dsl.cpp"
// --
#include "imgui/imgui_icons.cpp"
#include "imgui/imgui_pangram.cpp"

// menubar
#include "imgui/imgui_utils.cpp"
#include "imgui/imgui_menubar.cpp"

using namespace ImGui;

#include "imgui/gists/bitfield.cpp"
#include "imgui/gists/hexedit.cpp"
#include "imgui/gists/ip_entry.cpp"
#include "imgui/gists/knob.cpp" // fresh ideas here: https://www.g200kg.com/en/webknobman/gallery.php
#include "imgui/gists/toggle.cpp"

#include "imgui/gists/imgui_browser.cpp"
#include "imgui/gists/imgui_disabled.cpp"
#include "imgui/gists/imgui_combofilter.cpp"
#include "imgui/gists/imgui_bezier.cpp"
#include "imgui/gists/imgui_curve.cpp"

#include "imgui/gists/spinner.cpp"
#include "imgui/gists/table.cpp"
#include "imgui/gists/multiplot.cpp"
#include "imgui/gists/plotvar.cpp"

#include "imgui/gists/gizmo.h"
#include "imgui/gists/gizmo.cpp"

#include "imgui/gists/sequencer.h"
#include "imgui/gists/sequencer.cpp"

#ifdef GLSL
#undef GLSL
#endif
#include "imgui/gists/textedit.h"
#include "imgui/gists/textedit.cpp"

#ifdef UNREFERENCED_PARAMETER
#undef UNREFERENCED_PARAMETER
#endif
#include "imgui/gists/nodes.h" //v1
#include "imgui/gists/nodes.cpp" //v1

#define YAP_ENABLE
#define YAP_IMPL
#define YAP_IMGUI
#include "imgui/gists/profiler.cpp"

#include "imgui/gists/orient.h"
#include "imgui/gists/orient.cpp"

#include "imgui/gists/imgui_im3d.cpp"

#include "imgui/imgui_property.cpp"



void imgui_dockspace() {
    // config dockspace
    {
        // https://github.com/ocornut/imgui/issues/2109
        // This is how to create an invisible dockspace covering the whole screen:
        bool open = 1, *p_open = &open;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::SetNextWindowBgAlpha(0.0f);

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", p_open, window_flags);
        ImGui::PopStyleVar(3);

        ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
        ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruDockspace;
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
}

void imgui_dockspace_end() {
    ImGui::End();
}

void profiler2_demo() {
    float msBegin[4] = { 0, 1, 2, 3 };
    float msEnd[4] = { 1, 3, 5, 7 };
    const char *label[4] = { "a", "b", "c", "d" };
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1.0f, 1.0f));
    for( int i = 0; i < 4; ++i ) {
        float hue = i / 4.f;
        ImGui::PushStyleColor(ImGuiCol_Button, ImColor::HSV(hue, 0.6f, 0.6f).Value);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor::HSV(hue, 0.7f, 0.7f).Value);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImColor::HSV(hue, 0.8f, 0.8f).Value);
        ImGui::SetCursorPosX(msBegin[i] * 40.0f);
        ImGui::Button(label[i], ImVec2((msEnd[i] - msBegin[i]) * 40.0f, 0.0f));
        ImGui::PopStyleColor( 3 );
        ImGui::Separator();
    }
    ImGui::PopStyleVar(2);
}

#if 0
overlay

    bool p_open = 1;
    ImGui::SetNextWindowPos(ImVec2(x + 10, y + 10));
    // Demonstrate creating a simple static window with no decoration.
    ImGui::Begin("Fixed Overlay", &p_open, ImVec2(0,0), 0.90f /*opacity*/, ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoSavedSettings);
    ImGui::End();

#endif

void stats_demo() {
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Text("Mouse Position: (%.1f,%.1f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);

    ImGui::Separator();

    {
        static float fps_history[60] = {0};
        static float cpu_history[60] = {0};
        static float mem_history[60] = {0};
        static double left = 0;
        left -= ImGui::GetIO().DeltaTime;
        if( left <= 0 ) { // every sec
            left += 1.0;
            for( int i = 1; i < 60; ++i ) fps_history[i - 1] = fps_history[i];
            fps_history[59] = ImGui::GetIO().Framerate;
            for( int i = 1; i < 60; ++i ) cpu_history[i - 1] = cpu_history[i];
            cpu_history[59] = 1.00; //cpu_usage();
            for( int i = 1; i < 60; ++i ) mem_history[i - 1] = mem_history[i];
            mem_history[59] = 1024; //memory_usage();
        }

        char buf[256]; sprintf(buf, "fps:%6.2f cpu:%6.2f%% mem:%d/%d ##PERF", fps_history[59], cpu_history[59], (int)mem_history[59], (int)mem_history[59] );
        const char* label = buf;
        const char* names[] = { "FPS", "CPU", "MEM" };
        const ImColor colors[] = { PURPLE, GREEN, CYAN }; // also: blue, yellow; do not use { green, orange, red }
        const void * const datas[] = { fps_history, cpu_history, mem_history };
        int num_datas = sizeof(datas)/sizeof(datas[0]);
        int values_count = 60;
        float scale_min = 1;
        float scale_max = 100;
        ImVec2 graph_size( 315, 25 );

        ImGui::PlotMultiLines(
            label,
            num_datas,
            names,
            colors,
            [](const void* data, int idx) -> float { return ((float *)data)[idx]; },
            datas,
            values_count,
            scale_min,
            scale_max,
            graph_size);
    }
}

// -----------------

void editor_init() {
    imgui_config();
    imgui_fonts();

    imgui_theme_cherry();
    imgui_style_framework();
}

void editor_tick()
{}

void editor_draw() {
    // menu bar
    imgui_menubar();

    // dockspace
    imgui_dockspace();

#if 1
    int flags = ImGui::IsMouseDown(0) ? 0 : ImGuiWindowFlags_NoMove;
    ImGui::Begin("3d", NULL, flags);
    ImGuizmo::SetDrawlist();
//    ImGuizmo::BeginFrame(0,0,300,300);
    gizmo_demo2();
    ImGui::End();
#else
    gizmo_demo();
#endif

    // windowed content
        imgui_pangram();
        imgui_icons();
        sequencer_demo();
        profiler_demo();
        im3d_demo();
        browser_demo();


        static ImGui::Nodes nodes_;
        ImGui::Begin("Nodes");
        nodes_.ProcessNodes();
        ImGui::End();

        // alt, monospaced font
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
            static int init = (texteditor_demo_init(),1); 
            texteditor_demo_draw();

            static MemoryEditor mem_edit_1;                                            // store your state somewhere
            char *mem_block = "oh lala"; size_t mem_block_size = strlen(mem_block) + 1;
            mem_edit_1.DrawWindow("Memory Editor", mem_block, mem_block_size, 0x0000); // create a window and draw memory editor (if you already have a window, use DrawContents())
        ImGui::PopFont();

    // floating content
        ImGui::Begin("demo 1");
            extern bool show_demo_window; ImGui::Checkbox("Demo Window", &show_demo_window);
            static bool rec = 0; if( ImGui::Checkbox("Record", &rec) ) set_render('rec0', (double)!!rec);
            property_demo();
            spinner_demo();
        ImGui::End();

        ImGui::Begin("demo2");

            PlotVar("fps", ImGui::GetIO().Framerate); // if(t>60s) PlotVarFlushOldEntries(), t = 0;

            stats_demo();

            if( 1/*app('load')*/ ) {
                ImGui::Separator();
                ImGui::Text("loading");
                //ImGui::PushStyleColor(ImGuiCol_PlotHistogram, (ImVec4)ImColor::HSV(0/7.0f, 0.5f, 0.5f));
                ImGui::ProgressBar(0.5f, ImVec2(-1/*100%*/,2/*px*/), "loading");
                //ImGui::PopStyleColor();

                ImGui::Separator();
            }

            profiler2_demo();

            curve_demo();
            table_demo();

            orient_demo();

            bezier_demo();

        ImGui::End();

    // dockspace space
    // ...

    imgui_dockspace_end();

    // overlay space
    // ...
}

void editor_drop()
{}

int imgui_main(int, char**);

EXPORT
int main(int argc, char **argv) {
    return imgui_main(argc, argv);
}
