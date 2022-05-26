#include<iostream>
#include<iostream>
#include"raylib.h"
#pragma once

using namespace std;
Camera2D camera;

class Camera_cfg {
private:
    Vector2 target;
    float rotation;
    float zoom;
public:
    float GetXTarget() { return target.x; }
    float GetYTarget() { return target.y; }
    float GetRotation() { return rotation; }
    float GetZoom() { return zoom; }

    void SetXTarget(float element) { target.x = element; }
    void SetYTarget(float element) { target.y = element; }
    void SetRotation(float element) { rotation = element; }
    void SetZoom(float element) { zoom = element; }

    void AddX(float element) { target.x += element;};
    void RemoveX(float element) { target.x -= element;};
    void AddY(float element) { target.y += element;};
    void RemoveY(float element) {target.y -= element;};
    void AddZoom(float element){zoom += element;};
    void RemoveZoom(float element){zoom -= element;};
};