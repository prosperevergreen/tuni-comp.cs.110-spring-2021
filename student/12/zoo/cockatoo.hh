//
// Created by Prosper Evergreen on 24.04.2021.
//

#ifndef ZOO_COCKATOO_HH
#define ZOO_COCKATOO_HH

#include "bird.hh"

class Cockatoo: public Bird{
public:

    Cockatoo();
    void sing(std::ostream& output);
private:
    std::string sing_sound_ ="Kee-ow kee-ow!";
};


#endif //ZOO_COCKATOO_HH