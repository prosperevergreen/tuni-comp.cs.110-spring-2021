//
// Created by Prosper Evergreen on 24.04.2021.
//

#ifndef ZOO_MAMMAL_HH
#define ZOO_MAMMAL_HH

#include "animal.hh"

class Mammal: public Animal {
public:
    Mammal();
    void suckle(std::ostream& output);

private:
    std::string suckle_sound_ = "Mus mus";
};


#endif //ZOO_MAMMAL_HH
