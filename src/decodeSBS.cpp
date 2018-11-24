#include "decodeSBS.h"

using namespace std;

void decodeSBS::split(const string& s, char c,
                vector<string>& v){
    string::size_type i = 0;
    string::size_type j = s.find(c); //Find special character in string

    while (j != string::npos) {
        v.push_back(s.substr(i, j-i));
        i = ++j;
        j = s.find(c,j);
        if (j == string::npos)
         v.push_back(s.substr(i, s.length()));
    }
    for (int i = 0; i < v.size(); ++i) {
        if ( i == 0) { 
            cout << "Message Type: " << v[i] << endl; }
        if ( i == 1) { 
            cout << "Transmission Type: " << v[i] << endl; }
        if ( i == 2) { 
            cout << "Session ID: " << v[i] << endl; }
        if ( i == 3) { 
            cout << "Aircraft ID: " << v[i] << endl; }
        if ( i == 4) { 
            cout << "HexIdent: " << v[i] << endl; }
        if ( i == 5) { 
            cout << "FlightID: " << v[i] << endl; }
        if ( i == 6) { 
            cout << "Date Message Generated: " << v[i] << endl; }
        if ( i == 7) { 
            cout << "Time Message Generated: " << v[i] << endl; }
        if ( i == 8) { 
            cout << "Date Message Logged: " << v[i] << endl; }
        if ( i == 9) { 
            cout << "Time Message Logged: " << v[i] << endl; }
        if ( i == 10) { 
            cout << "Callsign: " << v[i] << endl; }
        if ( i == 11) { 
            cout << "Altitude: " << v[i] << endl; }
        if ( i == 12) { 
            cout << "Ground Speed: " << v[i] << endl; }
        if ( i == 13) { 
            cout << "Track: " << v[i] << endl; }
        if ( i == 14) { 
            cout << "Lattitude: " << v[i] << endl; }
        if ( i == 15) { 
            cout << "Longtitude: " << v[i] << endl; }
        if ( i == 16) { 
            cout << "Vertical Rate: " << v[i] << endl; }
        if ( i == 17) { 
            cout << "Squawk: " << v[i] << endl; }
        if ( i == 18) { 
            cout << "Alert(Squawk Change): "<< v[i] << endl; }
        if ( i == 19) { 
            cout << "Emergency: " << v[i] << endl; }
        if ( i == 20) { 
            cout << "SPI(Ident): " << v[i] << endl; }
        if ( i == v.size() - 1) { 
            cout << "IsOnGround: " << v[i] << endl; }
    }
}

decodeSBS::decodeSBS() {
    //cout<< "Constructed!" << endl;
}

