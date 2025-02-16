#include "drawable.h"

#include "../manager.h"

Drawable::Drawable(int draw_priority) : Trait("Drawable")
{
    draw_priority_ = draw_priority;
    RenderPL::AddDrawable(this);
}

Drawable::~Drawable()
{
    RenderPL::RemoveDrawable(this);
}

void Drawable::SetDrawPriority(int priority)
{
	draw_priority_ = priority;
	RenderPL::SortDrawables();
}
