#include "player.hh"
#include <iostream>
#include <string>

Player::Player(std::string name)
    : name_(name)
    , points_(0)
{
}

std::string Player::get_name() const
{
    return name_;
}

int Player::get_points() const
{
    return points_;
}

bool Player::has_won() const
{
    return points_ == 50;
}

void Player::add_points(int points)
{
    const unsigned int max_points = 50;

    if (points_ + points > max_points) {
        std::cout << name_ << "Teppo gets penalty points!" << std::endl;
        points_ = 25;
        return;
    }

    points_ += points;
}
