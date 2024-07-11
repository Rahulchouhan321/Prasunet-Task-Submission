#include <iostream>
#include <iomanip>

using namespace std;

// Function to convert Celsius to Fahrenheit
double celsiusToFahrenheit(double celsius) {
    return (celsius * 9.0/5.0) + 32.0;
}

// Function to convert Celsius to Kelvin
double celsiusToKelvin(double celsius) {
    return celsius + 273.15;
}

// Function to convert Fahrenheit to Celsius
double fahrenheitToCelsius(double fahrenheit) {
    return (fahrenheit - 32.0) * 5.0/9.0;
}

// Function to convert Fahrenheit to Kelvin
double fahrenheitToKelvin(double fahrenheit) {
    return (fahrenheit - 32.0) * 5.0/9.0 + 273.15;
}

// Function to convert Kelvin to Celsius
double kelvinToCelsius(double kelvin) {
    return kelvin - 273.15;
}

// Function to convert Kelvin to Fahrenheit
double kelvinToFahrenheit(double kelvin) {
    return (kelvin - 273.15) * 9.0/5.0 + 32.0;
}

int main() {
    double temperature;
    char unit;

    cout << "Enter temperature value: ";
    cin >> temperature;
    cout << "Enter unit of measurement (C for Celsius, F for Fahrenheit, K for Kelvin): ";
    cin >> unit;

    cout << fixed << setprecision(2);

    switch (unit) {
        case 'C':
        case 'c':
            cout << "Celsius: " << temperature << "°C" << endl;
            cout << "Fahrenheit: " << celsiusToFahrenheit(temperature) << "°F" << endl;
            cout << "Kelvin: " << celsiusToKelvin(temperature) << "K" << endl;
            break;
        case 'F':
        case 'f':
            cout << "Fahrenheit: " << temperature << "°F" << endl;
            cout << "Celsius: " << fahrenheitToCelsius(temperature) << "°C" << endl;
            cout << "Kelvin: " << fahrenheitToKelvin(temperature) << "K" << endl;
            break;
        case 'K':
        case 'k':
            cout << "Kelvin: " << temperature << "K" << endl;
            cout << "Celsius: " << kelvinToCelsius(temperature) << "°C" << endl;
            cout << "Fahrenheit: " << kelvinToFahrenheit(temperature) << "°F" << endl;
            break;
        default:
            cout << "Invalid unit of measurement!" << endl;
    }

    return 0;
}
