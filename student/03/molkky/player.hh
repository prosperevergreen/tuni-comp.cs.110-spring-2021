#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>

class Player
{
public:
    Player(std::string name);
    std::string get_name() const;
    int get_points() const;
    void add_points(int point);
    bool has_won() const;

private:
    std::string name_;
    unsigned int points_;
};

#endif // PLAYER_HH
