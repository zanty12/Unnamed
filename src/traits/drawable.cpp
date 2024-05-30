#include "drawable.h"

#include "../manager.h"

Drawable::Drawable(int draw_priority)
{
    draw_priority_ = draw_priority;
    RenderPL::AddDrawable(this);
}

Drawable::~Drawable()
{
    RenderPL::RemoveDrawable(this);
}
