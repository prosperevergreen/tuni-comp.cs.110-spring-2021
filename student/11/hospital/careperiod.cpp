#include "careperiod.hh"
#include <iostream>

CarePeriod::CarePeriod(const std::string& start, Person* patient)
    : patient_(patient)
    , start_(start)
{
}

CarePeriod::CarePeriod(const Date& start, Person* patient)
    : patient_(patient)
    , start_(start)
{
}

CarePeriod::~CarePeriod()
{
}

void CarePeriod::set_end_date(const Date& end)
{
    end_ = end;
}

void CarePeriod::add_assignee(const Person* staff){
    assignees.push_back(staff);
}
