#include <iostream>
#include <memory>
#include "cards.hh"


Cards::Cards(): top_( nullptr ) {
}


void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card 
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

// Tip for writing code more efficiently:
// Do not write the stubs of the methods remove and reverse by yourself here,
// but open the file cards.hh and click the declaration of the method
// by the right mouse button and select
// Refactor > Add definition in cards.cpp


// Removes the topmost card and passes it in the reference parameter id to the caller.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::remove(int& id){
    if (top_ == nullptr) {
        return false;
    }

    id = top_->data;
    top_ = top_->next;

    return true;
}

// Reverses the content of the data structure as opposite.
void Cards::reverse(){
    if (top_ == nullptr || top_->next == nullptr) {
        return;
    }

    std::shared_ptr<Card_data> temp_next = nullptr;
    std::shared_ptr<Card_data> temp_prev = nullptr;

    while(top_ != nullptr){
        temp_next = top_->next;
        top_->next = temp_prev;
        temp_prev = top_;
        top_ = temp_next;
    }
    top_ = temp_prev;
}
