#pragma once
#include <list>
#include "traits/drawable.h"

class RenderPL
{
    static std::list<Drawable*> drawables_;

public:
    static void AddDrawable(Drawable* drawable)
    {
        //insert drawable then sort by priority

        drawables_.push_back(drawable);
        drawables_.sort([](Drawable* a, Drawable* b) { return a->GetDrawPriority() < b->GetDrawPriority(); });
    }

    static void RemoveDrawable(Drawable* drawable)
    {
        drawables_.remove(drawable);
    }

    static void Draw();

	static void SortDrawables()
	{
		drawables_.sort([](Drawable* a, Drawable* b) { return a->GetDrawPriority() < b->GetDrawPriority(); });
	}

    static void CleanUp()
    {
        drawables_.clear();
    }
};
