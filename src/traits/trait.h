/**
* @file trait.h
 * @brief This file contains the Trait class.
 */

#pragma once
#include <string>

/**
 * @class Trait
 * @brief A class that represents a trait.
 *
 * This class is used as a base class for different types of traits.
 * It provides a type_ member and a method to get the type of the trait.
 */
class Trait
{
private:
    /**
     * @brief The type of the Trait.
     *
     * This member stores the type of the Trait as a string.
     */
    std::string type_;

public:
    /**
     * @brief Construct a new Trait object.
     *
     * The constructor initializes the type_ member with the provided type.
     *
     * @param type The type of the Trait.
     */
    Trait(std::string type) : type_(std::move(type)){}

    /**
     * @brief Destroy the Trait object.
     *
     * This is a virtual destructor. It is defaulted, meaning it has no special functionality.
     * It's declared virtual to ensure correct behavior when deleting derived class objects through a pointer to the base class.
     */
    virtual ~Trait() = default;

    /**
     * @brief Get the type of the Trait.
     *
     * @return The type of the Trait.
     */
    std::string GetType() const { return type_; }
};