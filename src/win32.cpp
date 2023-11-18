#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>
#include <Windows.h>
#include <GL/glew.h>
#include <gl/GL.h>

HGLRC hglrc;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    OutputDebugStringW(L"Hello!");
    // Registert the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Learn to Program Windows",
        WS_OVERLAPPEDWINDOW,
        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    HDC hdc = GetDC(hwnd);

    // Run the message loop.
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        if (!SwapBuffers(hdc))
        {
            OutputDebugStringW(L"SwapBuffers failed");
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_PAINT:
    {
        // PAINTSTRUCT ps;
        // HDC hdc = BeginPaint(hwnd, &ps);
        // FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        // EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_CREATE:
    {
        PIXELFORMATDESCRIPTOR pfd =
            {
                sizeof(PIXELFORMATDESCRIPTOR),
                1,
                PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // Flags
                PFD_TYPE_RGBA,                                              // The kind of framebuffer. RGBA or palette.
                32,                                                         // Colordepth of the framebuffer.
                0, 0, 0, 0, 0, 0,
                0,
                0,
                0,
                0, 0, 0, 0,
                24, // Number of bits for the depthbuffer
                8,  // Number of bits for the stencilbuffer
                0,  // Number of Aux buffers in the framebuffer.
                PFD_MAIN_PLANE,
                0,
                0, 0, 0};

        HDC hdc = GetDC(hwnd);
        int iPixelFormat;
        // get the best available match of pixel format for the device context
        iPixelFormat = ChoosePixelFormat(hdc, &pfd);

        if (0 == iPixelFormat)
        {
            return 0;
        }

        // make that the pixel format of the device context
        SetPixelFormat(hdc, iPixelFormat, &pfd);

        // OpenGL Rendering Context
        // type HGLRC, for handle to GL Rendering Context

        // create a rendering context
        hglrc = wglCreateContext(hdc);

        // 現在のレンダリングコンテキストとして設定
        wglMakeCurrent(hdc, hglrc);

        // call OpenGL APIs as desired ...

        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            // Problem: glewInit failed, something is seriously wrong.
            // return 1;
            OutputDebugStringW(L"Error: glewInit failed");
            return 1;
        }
        OutputDebugStringW(L"glewInit success");
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        return 0;
    }
    case WM_DESTROY:
        // when the rendering context is no longer needed ...

        // make the rendering context not current
        wglMakeCurrent(NULL, NULL);

        // delete the rendering context
        wglDeleteContext(hglrc);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}