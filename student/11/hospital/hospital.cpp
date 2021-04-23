#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <set>

Hospital::Hospital()
{
}

Hospital::~Hospital()
{
    // Deallocating staff
    for (std::map<std::string, Person*>::iterator
             iter
         = staff_.begin();
         iter != staff_.end();
         ++iter) {
        delete iter->second;
    }

    // Remember to deallocate patients also
    for (std::map<std::string, Person*>::iterator
             iter
         = current_patients_.begin();
         iter != current_patients_.end();
         ++iter) {
        delete iter->second;
    }
}

void Hospital::recruit(Params params)
{
    std::string specialist_id = params.at(0);
    if (staff_.find(specialist_id) != staff_.end()) {
        std::cout << ALREADY_EXISTS << specialist_id << std::endl;
        return;
    }
    Person* new_specialist = new Person(specialist_id);
    staff_.insert({ specialist_id, new_specialist });
    std::cout << STAFF_RECRUITED << std::endl;
}

void Hospital::enter(Params params)
{
    // Get pateients id
    std::string patient_id = params.at(0);

    // Check if patient is not currently in hospital
    if (current_patients_.find(patient_id) != current_patients_.end()) {
        std::cout << ALREADY_EXISTS << patient_id << std::endl;
        return;
    }

    // Check if patient had a previous care period
    CarePeriod* care_period = get_care_period(patient_id);
    // If patient hadn't visited hospital (no care period),
    // create a new patient object, else get patient from prev care period
    Person* patient = care_period == nullptr ? new Person(patient_id) : care_period->get_patient();

    // Add patient to hospital list
    current_patients_.insert({ patient_id, patient });
    // Get the current date
    Date today = utils::today;
    // Initialize patient new care period
    CarePeriod* new_care_record = new CarePeriod(today, patient);

    // Add to care records
    care_records_.push_back(new_care_record);

    std::cout << PATIENT_ENTERED << std::endl;
}

/**
* @brief Function that implements discharging a patient from the hospital
* @param params - vector string containing the patient's id
*
*/
void Hospital::leave(Params params)
{
    std::string patient_id = params.at(0);

    // Check if patient in hospital
    if (current_patients_.find(patient_id) == current_patients_.end()) {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }

    // Patient in hospital

    // Get the current date
    Date today = utils::today;
    // End patient current care plan
    get_care_period(patient_id)->set_end_date(today);
    // Remove patient from hospital current patients
    current_patients_.erase(patient_id);
    std::cout << PATIENT_LEFT << std::endl;
}

void Hospital::assign_staff(Params params)
{
    std::string specialist_id = params.at(0);
    std::string patient_id = params.at(1);

    // Check if staff exists
    if (staff_.find(specialist_id) == staff_.end()) {
        std::cout << CANT_FIND << specialist_id << std::endl;
        return;
    }

    // Check if patient is not in hospital
    if (current_patients_.find(patient_id) == current_patients_.end()) {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }

    std::cout << STAFF_ASSIGNED << patient_id << std::endl;

    // Get access to the latest patient care plan
    CarePeriod* current_care_period = get_care_period(patient_id);

    // Check if patient has already been assigned the staff
    if (current_care_period->has_staff(specialist_id)) {
        return;
    }

    // Add staff to patient assignee list
    current_care_period->add_assignee(staff_.at(specialist_id));
}

void Hospital::add_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string strength = params.at(1);
    std::string dosage = params.at(2);
    std::string patient = params.at(3);
    if (not utils::is_numeric(strength, true) or not utils::is_numeric(dosage, true)) {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    std::map<std::string, Person*>::const_iterator
        patient_iter
        = current_patients_.find(patient);
    if (patient_iter == current_patients_.end()) {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->add_medicine(medicine, stoi(strength), stoi(dosage));
    std::cout << MEDICINE_ADDED << patient << std::endl;
}

void Hospital::remove_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string patient = params.at(1);
    std::map<std::string, Person*>::const_iterator
        patient_iter
        = current_patients_.find(patient);
    if (patient_iter == current_patients_.end()) {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->remove_medicine(medicine);
    std::cout << MEDICINE_REMOVED << patient << std::endl;
}

void Hospital::print_patient_info(Params params)
{
    std::string patient_id = params.at(0);

    CarePeriod* latest_care_period = get_care_period(patient_id);

    if (latest_care_period == nullptr) {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }

    for (auto care_period : care_records_) {
        care_period->print();
    }
    std::cout << PRINT_MEDICINE;
    latest_care_period->get_patient()->print_medicines(PRE_TEXT);
}

void Hospital::print_care_periods_per_staff(Params params)
{
}

void Hospital::print_all_medicines(Params)
{
}

void Hospital::print_all_staff(Params)
{
    if (staff_.empty()) {
        std::cout << "None" << std::endl;
        return;
    }
    for (std::map<std::string, Person*>::const_iterator iter = staff_.begin();
         iter != staff_.end();
         ++iter) {
        std::cout << iter->first << std::endl;
    }
}

void Hospital::print_all_patients(Params)
{
}

void Hospital::print_current_patients(Params)
{
}

void Hospital::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if (not utils::is_numeric(day, false) or not utils::is_numeric(month, false) or not utils::is_numeric(year, false)) {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::advance_date(Params params)
{
    std::string amount = params.at(0);
    if (not utils::is_numeric(amount, true)) {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}

CarePeriod* Hospital::get_care_period(const std::string& patient_id)
{
    for (std::vector<CarePeriod*>::size_type i = care_records_.size() - 1; i >= 0; --i) {
        CarePeriod* care_record = care_records_.at(i);
        if (care_record->get_patient()->get_id() == patient_id) {
            return care_record;
        }
    }
    return nullptr;
}
