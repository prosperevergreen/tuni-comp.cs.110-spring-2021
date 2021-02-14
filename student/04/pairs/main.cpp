/* Pairs
 *
 * Desc:
 *  This program generates a pairs (memory) game. The game has a variant
 * number of cards and players. At the beginning, the program also asks for a
 * seed value, since the cards will be set randomly in the game board.
 *  On each round, the player in turn gives the coordinates of two cards
 * (totally four numbers). After that the given cards will be turned as
 * visible and told if they are pairs or not. If they are pairs, they are
 * removed from the game board, the score of the player is increased, and
 * a new turn is given for the player. If the cards are not pairs, they
 * will be  turned hidden again, and the next player will be in turn.
 *  The program checks if the user-given coordinates are legal. The cards
 * determined by the coordinates must be found in the game board.
 *  After each change, the game board is printed again. The cards are
 * described as letters, starting from A and lasting so far as there are
 * cards. In printing the game board, a visible card is shown as its letter,
 * a hidden one as the number sign (#), and a removed one as a dot.
 *  Game will end when all pairs have been found, and the game board is
 * empty. The program tells who has/have won, i.e. collected most pairs.
 *
 * Program author
 * Name: Prosper Evergreen
 * Student number: 050542738
 * UserID: hsprev
 * E-Mail: prosper.evergreen@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * */

#include <card.hh>
#include <iostream>
#include <player.hh>
#include <random>
#include <vector>

using namespace std;

const string INPUT_AMOUNT_OF_CARDS = "Enter the amount of cards (an even number): ";
const string INPUT_SEED = "Enter a seed value: ";
const string INPUT_AMOUNT_OF_PLAYERS = "Enter the amount of players (one or more): ";
const string INPUT_CARDS = "Enter two cards (x1, y1, x2, y2), or q to quit: ";
const string INVALID_CARD = "Invalid card.";
const string FOUND = "Pairs found.";
const string NOT_FOUND = "Pairs not found.";
const string GIVING_UP = "Why on earth you are giving up the game?";
const string GAME_OVER = "Game over!";
const unsigned int MIN_NUM_PLAYERS = 1;
const unsigned int MIN_COORDNATE = 1;
const unsigned int VALID_COORDNATE_SIZE = 4;
const string FORCE_QUIT = "q";
const unsigned int FORCE_QUIT_INT = 0;

using Game_row_type = vector<Card>;
using Player_type = vector<Player>;
using Game_board_type = vector<vector<Card>>;

// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns 0
// (which leads to an invalid card later).
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for (unsigned int i = 0; i < str.length(); ++i) {
        if (not isdigit(str.at(i))) {
            is_numeric = false;
            break;
        }
    }
    if (is_numeric) {
        return stoi(str);
    } else {
        return 0;
    }
}

// Fills the game board, the size of which is rows * columns, with empty cards.
void init_with_empties(Game_board_type& g_board, unsigned int rows, unsigned int columns)
{
    g_board.clear();
    Game_row_type row;
    for (unsigned int i = 0; i < columns; ++i) {
        Card card;
        row.push_back(card);
    }
    for (unsigned int i = 0; i < rows; ++i) {
        g_board.push_back(row);
    }
}

// Finds the next free position in the game board (g_board), starting from the
// given position start and continuing from the beginning if needed.
// (Called only by the function init_with_cards.)
unsigned int next_free(Game_board_type& g_board, unsigned int start)
{

    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    // Starting from the given value
    for (unsigned int i = start; i < rows * columns; ++i) {
        if (g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY) // vaihdettu
        {
            return i;
        }
    }

    // Continuing from the beginning
    for (unsigned int i = 0; i < start; ++i) {
        if (g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY) {
            return i;
        }
    }

    // You should never reach this
    std::cout << "No more empty spaces" << std::endl;
    return rows * columns - 1;
}

// Initializes the given game board (g_board) with randomly generated cards,
// based on the given seed value.
void init_with_cards(Game_board_type& g_board, int seed)
{
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    // Drawing a cell to be filled
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, rows * columns - 1);

    // Wiping out the first random number (that is always the lower bound of the distribution)
    distr(randomEng);

    // If the drawn cell is already filled with a card, next empty cell will be used.
    // (The next empty cell is searched for circularly, see function next_free.)
    for (unsigned int i = 0, c = 'A'; i < rows * columns - 1; i += 2, ++c) {

        // Adding two identical cards (pairs) in the game board
        for (unsigned int j = 0; j < 2; ++j) {
            unsigned int cell = distr(randomEng);
            cell = next_free(g_board, cell);
            g_board.at(cell / columns).at(cell % columns).set_letter(c);
            g_board.at(cell / columns).at(cell % columns).set_visibility(HIDDEN);
        }
    }
}

// Prints a line consisting of the given character c.
// The length of the line is given in the parameter line_length.
// (Called only by the function print.)
void print_line_with_char(char c, unsigned int line_length)
{
    for (unsigned int i = 0; i < line_length * 2 + 7; ++i) {
        cout << c;
    }
    cout << endl;
}

// Prints a variable-length game board with borders.
void print(const Game_board_type& g_board)
{

    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    print_line_with_char('=', columns);
    cout << "|   | ";
    for (unsigned int i = 0; i < columns; ++i) {
        cout << i + 1 << " ";
    }
    cout << "|" << endl;
    print_line_with_char('-', columns);
    for (unsigned int i = 0; i < rows; ++i) {
        cout << "| " << i + 1 << " | ";
        for (unsigned int j = 0; j < columns; ++j) {
            g_board.at(i).at(j).print();
            cout << " ";
        }
        cout << "|" << endl;
    }
    print_line_with_char('=', columns);
}

// Asks the desired product from the user, and calculates the factors of
// the product such that the factor as near to each other as possible.
void ask_product_and_calculate_factors(unsigned int& smaller_factor, unsigned int& bigger_factor)
{
    unsigned int product = 0;
    while (not(product > 0 and product % 2 == 0)) {
        std::cout << INPUT_AMOUNT_OF_CARDS;
        string product_str = "";
        std::getline(std::cin, product_str);
        product = stoi_with_check(product_str);
    }

    for (unsigned int i = 1; i * i <= product; ++i) {
        if (product % i == 0) {
            smaller_factor = i;
        }
    }
    bigger_factor = product / smaller_factor;
}

// More functions
void init_players(Player_type& players)
{
    unsigned int num_of_players = 0;

    // Checks that number of players is more than minimum required
    while (num_of_players < MIN_NUM_PLAYERS) {
        cout << INPUT_AMOUNT_OF_PLAYERS;
        string user_input = "";
        cin >> user_input;
        num_of_players = stoi_with_check(user_input);
    }

    std::cout << "List " << num_of_players << " players: ";

    // Creates and add players to the vector list
    for (unsigned int i = 0; i < num_of_players; ++i) {
        string player_name = "";
        cin >> player_name;
        Player new_player(player_name);
        players.push_back(new_player);
    }
}

bool coords_in_range(unsigned int value, unsigned int max)
{

    if (value < MIN_COORDNATE) {
        return false;
    }

    if (value > max) {
        return false;
    }

    return true;
}

bool is_card_available(const Game_board_type& g_board, unsigned int x, unsigned int y)
{
    return g_board.at(y - 1).at(x - 1).get_visibility() != EMPTY;
}

bool is_coordinate_valid(const Game_board_type& g_board, vector<unsigned int>& card_coords)
{
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    // Checks if coordinates are in range
    for (unsigned int coord_index = 0; coord_index < VALID_COORDNATE_SIZE; coord_index++) {

        if (coord_index % 2 == 0) {
            // Checks if x coordinate is in range
            if (!coords_in_range(card_coords.at(coord_index), columns)) {
                return false;
            }
        } else {
            // Checks if y coordinate is in range
            if (!coords_in_range(card_coords.at(coord_index), rows)) {
                return false;
            }
        }
    }

    // Check if card 1 == card 2
    if (card_coords.at(0) == card_coords.at(2) and card_coords.at(1) == card_coords.at(3)) {
        return false;
    }

    // Checks if card 1 is empty
    if (!is_card_available(g_board, card_coords.at(0), card_coords.at(1))) {
        return false;
    }

    cout << "At card 1 check" << endl;

    // Checks if card 2 is empty
    if (!is_card_available(g_board, card_coords.at(2), card_coords.at(3))) {
        return false;
    }

    cout << "At card 2 check" << endl;

    return true;
}

vector<unsigned int> get_player_choice(const Game_board_type& g_board, const Player& player)
{

    bool valid_input = false;
    vector<unsigned int> user_choice;

    while (!valid_input) {
        user_choice = {};
        cout << player.get_name() << ": " << INPUT_CARDS;
        string first_input;
        cin >> first_input;

        // Checks if first input is "q" to quit game
        if (first_input == FORCE_QUIT) {
            valid_input = true;
            user_choice.push_back(FORCE_QUIT_INT);
        } else { // Validate input ass coordinate to available cards
            vector<unsigned int> temp_card_coords;
            temp_card_coords.push_back(stoi_with_check(first_input));
            for (unsigned int num = 1; num < VALID_COORDNATE_SIZE; num++) {
                string coordinate_input = "";
                cin >> coordinate_input;
                temp_card_coords.push_back(stoi_with_check(coordinate_input));
            }

            if (is_coordinate_valid(g_board, temp_card_coords)) {
                user_choice = temp_card_coords;
                valid_input = true;
            } else {
                cout << INVALID_CARD << endl;
            }
        }
    }

    return user_choice;
}

bool is_gameover(Game_board_type& g_board, const Player_type& players)
{

    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    unsigned int number_of_pairs = (rows * columns) / 2;

    unsigned int current_pairs = 0;
    for (Player_type::size_type index = 0; index < players.size(); ++index) {
        current_pairs += players.at(index).number_of_pairs();
    }

    return number_of_pairs == current_pairs;
}

void run_game(Game_board_type& g_board, const Player_type& players)
{
    bool quit_now = false;
    unsigned int play_counter = 0;
    unsigned int turn = 0;
    while (!is_gameover(g_board, players) and !quit_now) {
        print(g_board);
        turn = play_counter % players.size();

        vector<unsigned int> user_choice = get_player_choice(g_board, players.at(turn));
        if(user_choice.size() == 1 and user_choice.at(0) == FORCE_QUIT_INT){
            return;
        }
        play_counter++;
    }
}

int main()
{
    Game_board_type game_board;
    Player_type players;

    unsigned int factor1 = 1;
    unsigned int factor2 = 1;
    ask_product_and_calculate_factors(factor1, factor2);
    init_with_empties(game_board, factor1, factor2);

    string seed_str = "";
    std::cout << INPUT_SEED;
    std::getline(std::cin, seed_str);
    int seed = stoi_with_check(seed_str);
    init_with_cards(game_board, seed);

    // More code
    init_players(players);
    run_game(game_board, players);

    return EXIT_SUCCESS;
}
