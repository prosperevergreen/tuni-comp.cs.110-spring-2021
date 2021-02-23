/*
 * Program author
 * Name: Prosper Evergreen
 * Student number: 050542738
 * UserID: hsprev
 * E-Mail: prosper.evergreen@tuni.fi
 *
 * Implementation of the Player Class
 *
 * */
#include "player.hh"

// Add class implementation here.
// It should be enough to write only 1-2 code lines in each public method.
Player::Player(const std::string& name)
    : name_(name)
    , pairs_(0)
{
}

std::string Player::get_name() const
{
    return name_;
}

unsigned int Player::number_of_pairs() const
{
    return pairs_;
}

void Player::print() const
{
    std::cout << "*** " << name_ << " has " << pairs_ << " pair(s)." << std::endl;
}

void Player::add_card(Card&) { }

void Player::increase_pairs(){
    pairs_++;
}
