#pragma once
#include "trait.h"

/**
 * @class Unique
 * @brief A class that represents a unique trait.
 *
 * This class inherits from the Trait class and represents a unique trait.
 * It doesn't add any new functionality or data members to the base class.
 * It only provides a specific type of Trait, which is "Unique".
 */
class Unique : public Trait
{
public:
    Unique() : Trait("Unique")
    {
    }

    ~Unique() override = default;
};
