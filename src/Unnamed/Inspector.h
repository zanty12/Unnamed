#pragma once
#include <functional>
#include <string>

#include "entity.h"

struct Window
{
    std::string title;
    std::function<void()> func;
};

class Inspector
{
private:
    static std::vector<Window> windows_;
    static Entity* selected_entity_;
public:
    static void Register(Window window);
    static void DrawInspector();
};
