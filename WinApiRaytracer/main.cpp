#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <iostream>
#include <cstdint>
#include <cmath>
#include "headers\settings.h"
#include "headers\renderer.h"
#include "headers\objects.h"

void InitWorld();
void Start();
void Update();

OBJObject *OBJPool[OBJPoolSize + 1] {0};
int OBJObjectCount = 0;

float HPixelStep;
float VPixelStep;

OBJCamera* Camera;
OBJSun* Sun;

bool STisRunning;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{   
    
    #if DEBUG
        AllocConsole();
        FILE* dummy;
        freopen_s(&dummy, "CONOUT$", "w", stdout);
        freopen_s(&dummy, "CONOUT$", "w", stderr);
    #endif

    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Raytracer Window Class";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx( 
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Raytracing I Guess",    // Window text
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,            // Window style

        100, 100, // Pos
        STScreenWidth, STScreenHeight, // Size

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    Rhdc = GetDC(hwnd);
    STisRunning = true;

    RInitRenderer();

    InitWorld();

    // Run the main
    MSG msg = { };
    while (STisRunning)
    {
        while (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            }
        
        
        Update();
        RRenderScreen();
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        STisRunning = false;
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
            return 0;
        }
        
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void InitCamera(){
    Camera = Object::CreateObj<OBJCamera>(FVector3D(0, 0, 0), Quaternion(0.0f, 0.0f, 0.0f, 1.0f), FVector3D::Unit(), true, STFOV);
    int i = 0;
    while (OBJPool[i] != nullptr && OBJPool[i]->Type != OCAMERA) { i++;}
    if (OBJPool[i] != nullptr){
        HPixelStep = ((static_cast<OBJCamera*>(OBJPool[i]))->VPlane.Width) / STScreenWidth;
        VPixelStep = ((static_cast<OBJCamera*>(OBJPool[i]))->VPlane.Height) / STScreenHeight;
    }
}

void InitSun(){
    Sun = Object::CreateObj<OBJSun>(FVector3D(0, 0, 0), Quaternion(FVector3D(45, 45, 0)), FVector3D::Unit(), true, 1);
}

void InitWorld(){
    InitCamera();
    InitSun();
    SetCursorPos((int)(STScreenWidth / 2.0f), (int)(STScreenHeight / 2.0f));
    Start();
}



void Start(){
    Object::CreateObj<OBJSphere>(FVector3D(0, 0, 0), Quaternion(0, 0, 0, 1), FVector3D::Unit(), true, 1);
    Object::CreateObj<OBJSphere>(FVector3D(0, 0, 20), Quaternion(0, 0, 0, 1), FVector3D::Unit(), true, 2);
    Object::CreateObj<OBJSphere>(FVector3D(0, 20, 40), Quaternion(0, 0, 0, 1), FVector3D::Unit(), true, 5);
    Object::CreateObj<OBJSphere>(FVector3D(30, 20, 40), Quaternion(0, 0, 0, 1), FVector3D::Unit(), true, 20);
    Object::CreateObj<OBJSphere>(FVector3D(0, -2005, 0), Quaternion(0, 0, 0, 1), FVector3D::Unit(), true, 2000);
}

void Update(){
    
    if (GetAsyncKeyState('W') & 0x8000) {
        Camera->Position = Camera->Position + (Camera->GetForwardVector() * STCameraSpeed);
    }
    if (GetAsyncKeyState('S') & 0x8000) {
        Camera->Position = Camera->Position + (Camera->GetForwardVector() * -STCameraSpeed);
    }
    if (GetAsyncKeyState('A') & 0x8000) {
        Camera->Position = Camera->Position + (Camera->GetRightVector() * -STCameraSpeed);
    }
    if (GetAsyncKeyState('D') & 0x8000) {
        Camera->Position = Camera->Position + (Camera->GetRightVector() * STCameraSpeed);
    }
    if (GetAsyncKeyState('Q') & 0x8000) {
        Camera->Position = Camera->Position + (Camera->GetUpVector() * -STCameraSpeed);
    }
    if (GetAsyncKeyState('E') & 0x8000) {
        Camera->Position = Camera->Position + (Camera->GetUpVector() * STCameraSpeed);
    }

    POINT CursorPos;
    GetCursorPos(&CursorPos);

    float CenterX = STScreenWidth / 2.0f; 
    float CenterY = STScreenHeight / 2.0f;

    float DeltaX = (float)(CursorPos.x - CenterX);
    float DeltaY = (float)(CursorPos.y - CenterY);

    SetCursorPos((int)CenterX, (int)CenterY);

    // Toplam açıları statik olarak tutuyoruz ki her karede sıfırlanmasın
    static float TotalYaw = 0.0f;
    static float TotalPitch = 0.0f;

    TotalYaw += DeltaX * STCameraSensitivity;
    TotalPitch += DeltaY * STCameraSensitivity;

    // Kafanın tamamen ters dönmesini (boyun kırılmasını) engelleyen 89 derece sınırı
    if (TotalPitch > 89.0f)  TotalPitch = 89.0f;
    if (TotalPitch < -89.0f) TotalPitch = -89.0f;

    // Pitch, Yaw değerlerini kendi yazdığın o şaheser ConvertToRotation() metoduna yolla
    // (Sıralama: fx = Pitch, fy = Yaw, fz = Roll kabul ettiğimiz için böyle veriyoruz)
    FVector3D NewRotation(TotalPitch, TotalYaw, 0.0f);
    Camera->Rotation = NewRotation.ConvertToRotation();
}
