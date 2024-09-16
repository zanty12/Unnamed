#include "renderPL.h"

std::list<Drawable*> RenderPL::drawables_;

void RenderPL::Draw()
{
    for (auto& drawable : drawables_)
    {
        drawable->Draw();
    }
}

