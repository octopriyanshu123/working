#include <iostream>
#include <iomanip>  // Required for setw(), setfill(), setprecision, etc.
#include <ctime>    // Required for time-related functions

using namespace std;


void getReservationData()
{
string guestName;
int partySize;
cout << "Name and number of guests: ";
cin >> guestName >> partySize;
cout << "Thank you, " << guestName << "." << endl;
if (partySize > 10) {
cout << "An extra gratuity will apply." << endl;
}
}



int main() {
    // Boolean output formatting
    bool myBool { true };
    cout << "This is the default: " << myBool << endl;
    cout << "This should be true: " << boolalpha << myBool << endl;
    cout << "This should be 1: " << noboolalpha << myBool << endl;

    // Integer formatting
    int i { 123 };
    printf("This should be '123': %6d\n", i);
    cout << "This should be '123': " << setw(6) << i << endl;

    // Zero-padding integer formatting
    printf("This should be '000123': %06d\n", i);
    cout << "This should be '000123': " << setfill('0') << setw(6) << i << endl;

    // Floating-point formatting
    double dbl { 1.452 };
    double dbl2 { 5 };
    cout << "This should be ' 5': " << setw(2) << noshowpoint << dbl2 << endl;
    cout << "This should be @@1.452: " << setw(7) << setfill('@') << dbl << endl;
    // Reset fill character to space
    cout << setfill(' ');

    // Monetary value formatting
    long long int moneyAmount = 120000;
    cout << "This should be a monetary value of 120000: "
         << put_money(moneyAmount) << endl;

    // Date and time formatting
    time_t t_t { time(nullptr) }; // Get current system time.
    tm* t { localtime(&t_t) };    // Convert to local time.
    cout << "This should be the current date and time: "
         << put_time(t, "%c") << endl;

    // Quoted string formatting
    cout << "This should be: \"Quoted string with \\\"embedded quotes\\\".\": "
         << quoted("Quoted string with \"embedded quotes\".") << endl;

    // Set precision for floating-point numbers
    cout << "This should be '1.23': " << setprecision(3) << 1.23456789 << endl;

    // Reset precision
    cout.precision(5);
    cout << "This should be '1.23457': " << 1.23456789 << endl;

//     int userInput;
// cin >> userInput;
// cout << "User input was " << userInput << endl;

getReservationData();
    return 0;
}
