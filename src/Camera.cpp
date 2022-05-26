#include<iostream>
#include"Camera.hpp"

void CameraConfig(float X, float Y, float Rot, float Zoom){
    Camera.SetXTarget(X);
    Camera.SetYTarget(Y);
    Camera.SetRotation(Rot);
    Camera.SetZoom(Zoom);
}