#include <iostream>
#include <cstring>
using namespace std;

// Structure to store vehicle information
struct VehicleInfo {
    char vin[17];
    int age;
    char type[10];
};

// Structure to define rate brackets
struct RateBracket {
    float minAge;
    float maxAge;
    float rate;
};

// Abstract base class for insurance calculators
class InsuranceCalculator {
protected:
    RateBracket* brackets;
    int count;

public:
    InsuranceCalculator() {
        brackets = NULL;
        count = 0;
    }

    // Pure virtual function
    virtual float quote(const VehicleInfo* info) = 0;

    // Add a new bracket
    void addBracket(RateBracket rb) {
        RateBracket* newBrackets = new RateBracket[count + 1];
        for (int i = 0; i < count; i++) {
            newBrackets[i] = brackets[i];
        }
        newBrackets[count] = rb;
        delete[] brackets;
        brackets = newBrackets;
        count++;
    }

    // Remove a bracket by index
    void removeBracket(int index) {
        if (index < 0 || index >= count) return;
        RateBracket* newBrackets = new RateBracket[count - 1];
        int j = 0;
        for (int i = 0; i < count; i++) {
            if (i != index) {
                newBrackets[j] = brackets[i];
                j++;
            }
        }
        delete[] brackets;
        brackets = newBrackets;
        count--;
    }

    // Destructor
    virtual ~InsuranceCalculator() {
        delete[] brackets;
    }

protected:
    // Match rate using age
    float findRateByAge(int age) {
        for (int i = 0; i < count; i++) {
            RateBracket* p = brackets + i;
            if (age >= p->minAge && age <= p->maxAge) {
                return p->rate;
            }
        }
        return 0.0f; // Default if no match
    }
};

// Third-party insurance calculator
class ThirdPartyCalculator : public InsuranceCalculator {
public:
    float quote(const VehicleInfo* info) {
        float baseRate = findRateByAge(info->age);
        return baseRate * 1.1f; // 10% markup
    }
};

// Comprehensive insurance calculator
class ComprehensiveCalculator : public InsuranceCalculator {
public:
    float quote(const VehicleInfo* info) {
        float baseRate = findRateByAge(info->age);
        return baseRate * 1.5f; // 50% markup
    }
};

int main() {
    // Example vehicle 1
    VehicleInfo car1;
    strcpy(car1.vin, "1HGCM82633A004352");
    car1.age = 3;
    strcpy(car1.type, "Sedan");

    // Example vehicle 2
    VehicleInfo car2;
    strcpy(car2.vin, "JH4KA8260MC123456");
    car2.age = 12;
    strcpy(car2.type, "SUV");

    // Create calculator instances
    InsuranceCalculator** calculators = new InsuranceCalculator*[2];
    calculators[0] = new ThirdPartyCalculator();
    calculators[1] = new ComprehensiveCalculator();

    // Create rate brackets
    RateBracket r1 = {0, 5, 1000};    // Young vehicles
    RateBracket r2 = {6, 10, 800};    // Mid-age vehicles
    RateBracket r3 = {11, 20, 600};   // Older vehicles

    // Add brackets to both calculators
    for (int i = 0; i < 2; i++) {
        calculators[i]->addBracket(r1);
        calculators[i]->addBracket(r2);
        calculators[i]->addBracket(r3);
    }

    // Display quotes
    cout << "Vehicle 1 (Sedan, Age 3):" << endl;
    cout << "  Third Party Quote: " << calculators[0]->quote(&car1) << " RWF" << endl;
    cout << "  Comprehensive Quote: " << calculators[1]->quote(&car1) << " RWF" << endl;

    cout << "\nVehicle 2 (SUV, Age 12):" << endl;
    cout << "  Third Party Quote: " << calculators[0]->quote(&car2) << " RWF" << endl;
    cout << "  Comprehensive Quote: " << calculators[1]->quote(&car2) << " RWF" << endl;

    // Cleanup
    delete calculators[0];
    delete calculators[1];
    delete[] calculators;

    return 0;
}

