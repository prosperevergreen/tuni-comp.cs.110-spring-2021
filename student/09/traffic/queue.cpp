#include "queue.hh"

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle)
    : first_(nullptr)
    , last_(nullptr)
    , is_green_(false)
    , cycle_(cycle)
{
}

Queue::~Queue()
{
    while (first_ != nullptr) {
        Vehicle* vehicle_to_be_released = first_;
        first_ = first_->next;

        delete vehicle_to_be_released;
    }
}

void Queue::enqueue(string reg)
{
    // Check if light is green to prevent adding to queue
    if (is_green_) { // light is green ((cannot add to vehicle to queue)

        cout << "GREEN: ";
        if (first_ == nullptr) { // Quene is empty
            cout << "The vehicle " << reg << " need not stop to wait" << endl;
        } else { // Queue is not empty
            cout << "Vehicle(s) " << reg << " can go on" << endl;
        }
    } else { // Light is red (can add to vehicle to queue)

        Vehicle* new_vehicle = new Vehicle { reg, nullptr };

        if (first_ == nullptr) { // Quene is empty (init queue)
            first_ = new_vehicle;
            last_ = new_vehicle;
        } else { // Queue is not empty (add vehicle to queue)
            last_->next = new_vehicle;
            last_ = new_vehicle;
        }
    }
}

void Queue::switch_light()
{
    is_green_ = !is_green_;
    print();
}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::print()
{
    // Check light color
    if (is_green_) { // Light is green
        cout << "GREEN: ";
        // Check if queue is empty
        if (first_ == nullptr) {
            cout << "No vehicles waiting in traffic lights" << endl;
        } else {
            // Queue is not empty
            cout << "Vehicle(s) ";
            unsigned int counter = 0;
            // print at most cycle number of vehicles in queue and dequeue each of the printed car
            while (first_ != nullptr && counter < cycle_) {
                cout << first_->reg_num << " ";
                dequeue();
                counter++;
            }
            cout << "can go on" << endl;
            is_green_ = !is_green_;
        }
    } else { // Light is red
        cout << "RED: ";
        // Check if queue is empty
        if (first_ == nullptr) { // Queue is empty
            cout << "No vehicles waiting in traffic lights" << endl;
        } else { // Queue is not empty
            cout << "Vehicle(s) ";
            Vehicle* vehicle_in_stop = first_;
            while (vehicle_in_stop != nullptr) { // Print all vehicles in queue
                cout << vehicle_in_stop->reg_num << " ";
                vehicle_in_stop = vehicle_in_stop->next;
            }
            cout << "waiting in traffic lights" << endl;
        }
    }
}

void Queue::dequeue()
{
    Vehicle* vehicle_be_dequeued = first_;
    first_ = first_->next;
    delete vehicle_be_dequeued;
}
