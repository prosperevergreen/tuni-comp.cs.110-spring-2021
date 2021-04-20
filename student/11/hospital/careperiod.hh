/* Class CarePeriod
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a patient's care period in hospital.
 *
 * Note: Students need to implement almost all of this class by themselves.
 * */
#ifndef CAREPERIOD_HH
#define CAREPERIOD_HH

#include "date.hh"
#include "person.hh"
#include <string>

class CarePeriod {
public:
    // Constructor, start date given as a string (ddmmyyyy).
    CarePeriod(const std::string& start, Person* patient);
    // Constructor, start date given as a Date object.
    CarePeriod(const Date& start, Person* patient);

    // Destructor.
    ~CarePeriod();

    // More public methods
    void set_end_date(const Date& end);
    void add_assignee(const Person* staff);
    std::vector<Person*> get_assignees();

private:
    Person* patient_;
    Date start_;
    Date end_ = Date();

    // More attributes and methods
    std::vector<const Person*> assignees;

};

#endif // CAREPERIOD_HH
