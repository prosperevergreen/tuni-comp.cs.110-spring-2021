//
// Created by Prosper Evergreen on 24.04.2021.
//

#ifndef ZOO_GIRAFFE_HH
#define ZOO_GIRAFFE_HH
#include "mammal.hh"

class Giraffe: public Mammal {
public:
    Giraffe();
    void make_noise(std::ostream& output);

private:
    std::string noise_sound_ = "Ori ori ori!";
};



#endif //ZOO_GIRAFFE_HH
