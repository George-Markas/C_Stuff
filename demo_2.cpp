#include <string>
#include <utility>
#include <iostream>

using namespace std;

class student {
    private:
        char * registerNumber;
        string fullName;
        unsigned int semester;

    public:
        /* Setters */
        void setRegisterNumber (char * input) {
            registerNumber = input;
        }

        void setFullName (string input) {
            fullName = std::move(input);
        }

        void setSemester (unsigned int input) {
            semester = input;
        }

        /* Getters */
        char * getRegisterNumber() {
            return registerNumber;
        }

        string getFullName() {
            return fullName;
        }

        [[nodiscard]] unsigned int getSemester() const {
            return semester;
        }

        /* Constructors */
        student (char* input_1, string input_2) {
            registerNumber = input_1;
            fullName = std::move(input_2);
            semester = 1;
        }

        student (char* input_1, string input_2, unsigned int input_3) {
            registerNumber = input_1;
            fullName = std::move(input_2);
            semester = input_3;
        }

        student (student &t) {
            registerNumber = t.registerNumber;
            fullName  = t.fullName;
            semester = t.semester;
        }

        /* Class Functions */
        void attributePrint() {
            std::cout << "Αριθμός Μητρώου: " << registerNumber << "Ονοματεπώνυμο :" << fullName << "Εξάμηνο: "<< semester;
        }

        void operator+=(unsigned int) {
            semester++;
        }
        void operator-=(unsigned int) {
            semester--;
        }
};

int main () {
    char sample_register[8] = "2239000";
    string sample_name = "John Doe";

    student Sample_1 (sample_register, sample_name);
}