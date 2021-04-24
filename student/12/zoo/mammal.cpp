//
// Created by Prosper Evergreen on 24.04.2021.
//

#include "mammal.hh"

Mammal::Mammal():Animal("Kip kop kip kop"){}

void Mammal::suckle(std::ostream& output){
    output << suckle_sound_ << std::endl;
}