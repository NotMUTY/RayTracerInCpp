


#include <Windows.h>
#include <ctime>
#include <iostream>
#include <thread>

#include "..\headers\renderer.h"
#include "..\headers\math.h"
#include "..\headers\objects.h"

HDC Rhdc = nullptr;
uint32_t RPixels[STScreenWidth * STScreenHeight];

int xpos = 0;

BITMAPINFO bmInfo = { 10 };


void RInitRenderer() {
    
    bmInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmInfo.bmiHeader.biWidth = STScreenWidth;
    bmInfo.bmiHeader.biHeight = STScreenHeight;
    bmInfo.bmiHeader.biPlanes = 1;
    bmInfo.bmiHeader.biBitCount = 32;
    bmInfo.bmiHeader.biCompression = BI_RGB;

}

#ifdef SINGLE
void RRenderScreen(){
    int x, y;
    
    for (x = 0; x < STScreenWidth; x++){
        for (y = 0; y < STScreenHeight; y++){
            Ray PixelRay;
            PixelRay.Start = Camera->Position;
            
            float u = -Camera->VPlane.HalfWidth + (x * HPixelStep);
            float v = -Camera->VPlane.HalfHeight + (y * VPixelStep);

            FVector3D ViewplaneCenter = Camera->Position + (Camera->GetForwardVector() * Camera->VPlane.Distance);
            FVector3D PixelPos = ViewplaneCenter + (Camera->GetRightVector() * u) + (Camera->GetUpVector() * v);
            FVector3D RayDir = PixelPos - Camera->Position;
            
            RayDir.Normalize();
            PixelRay.Direction = RayDir;

            FVector3D CamP = Camera->Position;

            float HitDist = INFINITY;
            OBJObject* NearestObj = nullptr;
            
            for (OBJObject* Obj : OBJPool){
                if (Obj == nullptr)
                    continue;

                if (Obj->Type != OSPHERE)
                    continue;

                float A = 1.0f;
                
                float B = 2.0f * (
                        RayDir.fx * (CamP.fx - Obj->Position.fx) +
                        RayDir.fy * (CamP.fy - Obj->Position.fy) +
                        RayDir.fz * (CamP.fz - Obj->Position.fz)
                    ); 

                float radius = static_cast<OBJSphere*>(Obj)->Radius;
                float C = (CamP.fx - Obj->Position.fx) * (CamP.fx - Obj->Position.fx) + 
                          (CamP.fy - Obj->Position.fy) * (CamP.fy - Obj->Position.fy) +
                          (CamP.fz - Obj->Position.fz) * (CamP.fz - Obj->Position.fz) - (radius * radius);

                float Delta = (B * B) - (4.0f * A * C);

                if (Delta < 0.0f)
                    continue;

                float sqrtDelta = sqrt(Delta);
                float Distance = (-B - sqrtDelta) / (2.0f * A);

                if (Distance < 0.001f) {
                    Distance = (-B + sqrtDelta) / (2.0f * A);
                }

                if (Distance < 0.001f)
                    continue;

                if (Distance < HitDist){
                    HitDist = Distance;
                    NearestObj = Obj;
                }
            }

            if (NearestObj != nullptr){
                FVector3D HitLocation = Camera->Position + (RayDir * HitDist);

                FVector3D SurfaceNormal = HitLocation - NearestObj->Position;
                SurfaceNormal.Normalize();

                float Brightness = DotProduct(Sun->GetForwardVector() * -1, SurfaceNormal) * Sun->LightIntensity;
                if (Brightness <= 0)
                    Brightness = 0;
                Brightness *= 255;
                int PixelBrightness = static_cast<int>(Brightness);
                RPixels[(y * STScreenWidth) + x] = HEX_RGB(PixelBrightness, PixelBrightness, PixelBrightness); 
            }
            
        }
    }

    RWriteToScreen();
    ClearScreen();
}
#elifdef MULTI

void RenderRowByStep(int Step, int StartY){
    int x, y;
    for (x = 0; x < STScreenWidth; x++){
        for (y = StartY; y < STScreenHeight; y+=Step){
            Ray PixelRay;
            PixelRay.Start = Camera->Position;
            
            float u = -Camera->VPlane.HalfWidth + (x * HPixelStep);
            float v = -Camera->VPlane.HalfHeight + (y * VPixelStep);

            FVector3D ViewplaneCenter = Camera->Position + (Camera->GetForwardVector() * Camera->VPlane.Distance);
            FVector3D PixelPos = ViewplaneCenter + (Camera->GetRightVector() * u) + (Camera->GetUpVector() * v);
            FVector3D RayDir = PixelPos - Camera->Position;
            
            RayDir.Normalize();
            PixelRay.Direction = RayDir;

            FVector3D CamP = Camera->Position;

            float HitDist = INFINITY;
            OBJObject* NearestObj = nullptr;
            
            for (OBJObject* Obj : OBJPool){
                if (Obj == nullptr)
                    continue;

                if (Obj->Type != OSPHERE)
                    continue;

                float A = 1.0f;
                
                float B = 2.0f * (
                        RayDir.fx * (CamP.fx - Obj->Position.fx) +
                        RayDir.fy * (CamP.fy - Obj->Position.fy) +
                        RayDir.fz * (CamP.fz - Obj->Position.fz)
                    ); 

                float radius = static_cast<OBJSphere*>(Obj)->Radius;
                float C = (CamP.fx - Obj->Position.fx) * (CamP.fx - Obj->Position.fx) + 
                          (CamP.fy - Obj->Position.fy) * (CamP.fy - Obj->Position.fy) +
                          (CamP.fz - Obj->Position.fz) * (CamP.fz - Obj->Position.fz) - (radius * radius);

                float Delta = (B * B) - (4.0f * A * C);

                if (Delta < 0.0f)
                    continue;

                float sqrtDelta = sqrt(Delta);
                float Distance = (-B - sqrtDelta) / (2.0f * A);

                if (Distance < 0.001f) {
                    Distance = (-B + sqrtDelta) / (2.0f * A);
                }

                if (Distance < 0.001f)
                    continue;

                if (Distance < HitDist){
                    HitDist = Distance;
                    NearestObj = Obj;
                }
            }

            if (NearestObj != nullptr){
                FVector3D HitLocation = Camera->Position + (RayDir * HitDist);

                FVector3D SurfaceNormal = HitLocation - NearestObj->Position;
                SurfaceNormal.Normalize();

                float Brightness = DotProduct(Sun->GetForwardVector() * -1, SurfaceNormal) * Sun->LightIntensity;
                if (Brightness <= 0)
                    Brightness = 0;
                Brightness *= 255;
                int PixelBrightness = static_cast<int>(Brightness);
                RPixels[(y * STScreenWidth) + x] = HEX_RGB(PixelBrightness, PixelBrightness, PixelBrightness); 
            }
            
        }
    }

}

void RRenderScreen(){
    std::thread Workers[STThreadCount];

    for (int i = 0; i < STThreadCount; i++){
        Workers[i] = std::thread(RenderRowByStep, STThreadCount, i);
    }

    for (int i = 0; i < STThreadCount; i++){
        Workers[i].join();
    }

    RWriteToScreen();
    ClearScreen();
}

#else

void RRenderScreen(){}

#endif


void RWriteToScreen(){
    StretchDIBits(
        Rhdc,
        0,
        0,
        STScreenWidth,
        STScreenHeight,
        0,
        0,
        STScreenWidth,
        STScreenHeight,
        RPixels,
        &bmInfo,
        DIB_RGB_COLORS,
        SRCCOPY
        );
}

void ClearScreen(){
    for (int i = 0; i < STScreenHeight * STScreenWidth; i++){
        RPixels[i] = HEX_RGB(0, 0, 0);
    }
}
