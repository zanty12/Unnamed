/**
* @file drawable.h
 * @brief This file contains the Drawable class.
 */

#pragma once
#include "trait.h"

/**
 * @class Drawable
 * @brief A class that represents a drawable trait.
 *
 * This class inherits from the Trait class and represents a drawable trait.
 * It adds a draw_priority_ member and provides methods to draw the trait,
 * and get and set its draw priority.
 */
class Drawable : public Trait
{
private:
    /**
     * @brief The draw priority of the Drawable.
     *
     * This member determines the order in which Drawables are drawn.
     * Drawables with higher draw_priority_ are drawn later.
     */
    int draw_priority_ = 0;

public:
    /**
     * @brief Construct a new Drawable object.
     *
     * The constructor initializes the base Trait class with the name "Drawable"
     * and sets the draw_priority_.
     *
     * @param draw_priority The draw priority of the Drawable. Defaults to 0.
     */
    Drawable(int draw_priority = 0);

    /**
     * @brief Destroy the Drawable object.
     *
     * This is a virtual destructor. It is defaulted, meaning it has no special functionality.
     * It's declared virtual to ensure correct behavior when deleting derived class objects through a pointer to the base class.
     */
    virtual ~Drawable();

    /**
     * @brief Draw the Drawable.
     *
     * This is a pure virtual function. It must be overridden in any non-abstract derived class.
     */
    virtual void Draw() = 0;

    /**
     * @brief Set the draw priority of the Drawable.
     *
     * @param priority The new draw priority.
     */
    void SetDrawPriority(int priority);

    /**
     * @brief Get the draw priority of the Drawable.
     *
     * @return The draw priority of the Drawable.
     */
    int GetDrawPriority() const { return draw_priority_; }
};