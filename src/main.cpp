#include "decodeSBS.h"
#include "tcpListener.h"

using namespace std;

int main(int argc, char *argv[]) {
    string hostaddress;
    vector<string> v;
    char comma = ',';
    int hostport = 30003;
    bool connectStatus;

    if(argc < 2) {
        cout << "Usage: sbsDecode <hostname>" << endl;
        return 0;
    }
    else {
        //Class instantiation
        hostaddress = argv[1];
        decodeSBS* decode = new decodeSBS();
        tcpListener* client = new tcpListener(hostaddress, hostport);
        connectStatus = client->connected;
        if (connectStatus == true){
            string response = client->read();
            cout << "Response: %s" << response << endl;
            decode->split(response, comma, v);
            client->disconnect(); //Disconnnect method is not implemented.
        }
    }

}