#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <algorithm>

Hospital::Hospital() {
}

Hospital::~Hospital() {
    // Deallocating staff
    for (std::map<std::string, Person *>::iterator
                 iter
                 = staff_.begin();
         iter != staff_.end();
         ++iter) {
        delete iter->second;
    }

    // Remember to deallocate patients also
    for(auto patient: all_patients_id){
        delete get_care_period(patient)->get_patient();
    }
}

void Hospital::recruit(Params params) {
    std::string specialist_id = params.at(0);
    if (staff_.find(specialist_id) != staff_.end()) {
        std::cout << ALREADY_EXISTS << specialist_id << std::endl;
        return;
    }
    Person *new_specialist = new Person(specialist_id);
    staff_.insert({specialist_id, new_specialist});
    std::cout << STAFF_RECRUITED << std::endl;
}

void Hospital::enter(Params params) {
    // Get pateients id
    std::string patient_id = params.at(0);

    // Check if patient is not currently in hospital
    if (current_patients_.find(patient_id) != current_patients_.end()) {
        std::cout << ALREADY_EXISTS << patient_id << std::endl;
        return;
    }

    // Check if patient had a previous care period
    CarePeriod *care_period = get_care_period(patient_id);
    // If patient hadn't visited hospital (no care period),
    // create a new patient object, else get patient from prev care period
    Person *patient = care_period == nullptr ? new Person(patient_id) : care_period->get_patient();
    if(care_period == nullptr){
        all_patients_id.insert(patient_id);
    }

    // Add patient to hospital list
    current_patients_.insert({patient_id, patient});
    // Get the current date
    Date today = utils::today;
    // Initialize patient new care period
    CarePeriod *new_care_record = new CarePeriod(today, patient);

    // Add to care records
    care_periods_.push_back(new_care_record);

    std::cout << PATIENT_ENTERED << std::endl;
}

/**
* @brief Function that implements discharging a patient from the hospital
* @param params - vector string containing the patient's id
*
*/
void Hospital::leave(Params params) {
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

/**
* @brief Function that implements assigning of staff to a patient
* @param params - vector string containing the staff's id & patient's id
*
*/
void Hospital::assign_staff(Params params) {
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
    CarePeriod *current_care_period = get_care_period(patient_id);

    // Check if patient has already been assigned the staff
    if (current_care_period->has_staff(specialist_id)) {
        return;
    }

    // Add staff to patient assignee list
    current_care_period->add_assignee(specialist_id);
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

    // Remove patient from medicine list
    remove_medicine_patient(patient, medicine);

    // Check if medicine is in hospital list
    if (medicines_.find(medicine) == medicines_.end()) {
        // Create new medicine
        medicines_.insert({medicine,{patient}});
    }else{
        // Add patient to existing medicine
        medicines_.at(medicine).insert(patient);
    }

    std::cout << MEDICINE_ADDED << patient << std::endl;
}

void Hospital::remove_medicine(Params params) {
    std::string medicine = params.at(0);
    std::string patient = params.at(1);
    std::map<std::string, Person *>::const_iterator
            patient_iter
            = current_patients_.find(patient);
    if (patient_iter == current_patients_.end()) {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->remove_medicine(medicine);
    remove_medicine_patient(patient, medicine);
    std::cout << MEDICINE_REMOVED << patient << std::endl;
}

void Hospital::print_patient_info(Params params) {
    std::string patient_id = params.at(0);

    CarePeriod *latest_care_period = get_care_period(patient_id);

    if (latest_care_period == nullptr) {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }

    for (auto care_period : care_periods_) {
        care_period->print();
    }
    std::cout << PRINT_MEDICINE;
    latest_care_period->get_patient()->print_medicines(PRE_TEXT);
}

void Hospital::print_care_periods_per_staff(Params params) {
    const std::string staff_id = params.at(0);

    // Check if staff exists
    if (staff_.find(staff_id) == staff_.end()) {
        std::cout << CANT_FIND << staff_id << std::endl;
        return;
    }

    bool has_care_period = false;
    // Loop through each period and check if staff is assigned
    for (auto care_period : care_periods_) {
        if (care_period->has_staff(staff_id)) {
            has_care_period = true;
            care_period->print_period();
            care_period->print_patient();
        }
    }

    // Check if staff has no care record
    if (!has_care_period) {
        std::cout << NONE << std::endl;
    }
}


void Hospital::print_all_medicines(Params) {
    // Check if their is a medicine in the hospital
    if(medicines_.empty()){
        std::cout << NONE << std::endl;
        return;
    }
    // loop through the medicine and print the patients using it
    for(auto medicine: medicines_){
        std::cout << medicine.first << " prescribed for" << std::endl;
        for(auto patient: medicine.second){
            std::cout  << "* " << patient << std::endl;
        }
    }
}

void Hospital::print_all_staff(Params) {
    if (staff_.empty()) {
        std::cout << NONE << std::endl;
        return;
    }
    for (std::map<std::string, Person *>::const_iterator iter = staff_.begin();
         iter != staff_.end();
         ++iter) {
        std::cout << iter->first << std::endl;
    }
}



void Hospital::print_all_patients(Params) {
    if (all_patients_id.empty()) {
        std::cout << NONE << std::endl;
        return;
    }
    for(auto patient_id: all_patients_id){
        std::cout << patient_id << std::endl;
        print_patient_info(std::vector<std::string>{patient_id});
    }
}

void Hospital::print_current_patients(Params) {
    if (current_patients_.empty()) {
        std::cout << NONE << std::endl;
        return;
    }
    for(auto patient: current_patients_){
        std::string patient_id = patient.first;
        std::cout << patient_id << std::endl;
        print_patient_info(std::vector<std::string>{patient_id});
    }
}

void Hospital::set_date(Params params) {
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if (not utils::is_numeric(day, false) or not utils::is_numeric(month, false) or
        not utils::is_numeric(year, false)) {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::advance_date(Params params) {
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

CarePeriod *Hospital::get_care_period(const std::string &patient_id) {
    for (auto it = care_periods_.rbegin(); it != care_periods_.rend(); ++it) {
        if ((*it)->get_patient()->get_id() == patient_id) {
            return *it;
        }
    }
    return nullptr;
}

void Hospital::remove_medicine_patient(std::string patient, std::string pill){

    // Search through all the medicine
    for(auto medicine = medicines_.begin(); medicine != medicines_.end(); ++medicine){
        // Search through all the patients in each medicine
        for (auto i = medicine->second.begin(); i != medicine->second.end(); ++i) {
            // Check if the id matches the patient
            if ((*i) == patient && pill == medicine->first) {
                // Remove the patient from the list
                medicine->second.erase(i);
                // Check if list is now empty
                if(medicine->second.empty()){
                    // remove medicine from hospital list
                    medicines_.erase(medicine->first);
                }
                // Set exit loop to true
                return;
            }
        }
    }
}

