//
// Created by Prosper Evergreen on 24.04.2021.
//

#include "cockatoo.hh"

Cockatoo::Cockatoo():Bird(){}

void Cockatoo::sing(std::ostream& output){
    output << sing_sound_ << std::endl;
}
