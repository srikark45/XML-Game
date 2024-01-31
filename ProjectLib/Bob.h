/**
 * @file Bob.h
 * @author User
 *
 * Class the handles the variant image
 */

#ifndef PROJECT1_BOB_H
#define PROJECT1_BOB_H

#include "Harold.h"

/**
 * Class the handles the variant image
 */
class Bob : public Harold
{
private:

public:
    /// Constructor for the Variant image of Harold
    ///@param game the game in which the variant harold is a part of
    Bob(Game* game);
};

#endif //PROJECT1_BOB_H
