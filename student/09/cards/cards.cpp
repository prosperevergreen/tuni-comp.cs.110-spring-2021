#include "cards.hh"

// TODO: Implement the methods here

Cards::Cards()
    : top_(nullptr)
    , last_(nullptr)
{
}

void Cards::add(int id)
{
    Card_data* new_item = new Card_data { id, nullptr, nullptr };

    if (top_ == nullptr) {
        last_ = new_item;
        top_ = last_;
    } else {
        top_->next = new_item;
        new_item->prev = top_;
        top_ = new_item;
    }
}

void Cards::print_from_top_to_bottom(std::ostream& s)
{
    Card_data* item_to_be_printed = top_;
    unsigned int counter = 1;
    while (item_to_be_printed != nullptr) {
        s << counter << ": " << item_to_be_printed->data << "\n";
        counter++;
        item_to_be_printed = item_to_be_printed->prev;
    }
}

bool Cards::remove(int& id)
{
    if (top_ == nullptr) {
        return false;
    }

    Card_data* item_to_be_removed = top_;

    id = item_to_be_removed->data;

    if (top_ == last_) {
        top_ = nullptr;
        last_ = nullptr;
    } else {
        top_ = top_->prev;
    }

    delete item_to_be_removed;

    return true;
}

bool Cards::bottom_to_top()
{
    if (top_ == nullptr) {
        return false;
    }

    Card_data* item_to_be_moved = last_;

    // Put last in front of top
    top_->next = last_;

    // Put top behind last
    last_->prev = top_;

    // Make last to be top
    top_ = item_to_be_moved;

    // Assign the card next to last to be the new last
    last_ = last_->next;

    // Point prev of top to null
    last_->prev = nullptr;
    // Point next of top to null
    top_->next = nullptr;

    return true;
}

bool Cards::top_to_bottom()
{
    if (top_ == nullptr) {
        return false;
    }

    Card_data* item_to_be_moved = top_;

    // Put top behind last
    last_->prev = top_;
    // Put last in front of top
    top_->next = last_;
    // Make top to be last
    last_ = item_to_be_moved;
    // Assign the card behind top to be the new top
    top_ = top_->prev;
    // Point prev of top to null
    last_->prev = nullptr;
    // Point next of top to null
    top_->next = nullptr;

    return true;
}

void Cards::print_from_bottom_to_top(std::ostream& s)
{
    Card_data* item_to_be_printed = last_;
    unsigned int counter = 1;
    while (item_to_be_printed != nullptr) {
        s << counter << ": " << item_to_be_printed->data << "\n";
        counter++;
        item_to_be_printed = item_to_be_printed->next;
    }
}

Cards::~Cards()
{
    while (top_ != nullptr) {
        Card_data* item_to_be_released = top_;
        top_ = top_->prev;
        delete item_to_be_released;
    }
}
