//
// Created by Prosper Evergreen on 24.04.2021.
//

#include "giraffe.hh"

Giraffe::Giraffe():Mammal(){}

void Giraffe::make_noise(std::ostream& output){
    output << noise_sound_ << std::endl;
}