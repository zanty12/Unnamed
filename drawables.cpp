#include "drawables.h"

#include "manager.h"

Drawable::Drawable()
{
    Manager::AddDrawable(this);
}
