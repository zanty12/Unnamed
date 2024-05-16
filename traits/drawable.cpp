#include "drawable.h"

#include "../manager.h"

Drawable::Drawable()
{
    Manager::AddDrawable(this);
}
