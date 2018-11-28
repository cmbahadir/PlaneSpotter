#include <gtest/gtest.h>
#include "tcpListener.h"

TEST(TCPListener_Construct_with_Dummy_Hostname, Not_Segfault){
    ASSERT_EXIT((new tcpListener("dummy", 30003),exit(0)),::testing::ExitedWithCode(0),".*");
}


// TEST(Try_To_Connect_Unknown_Host, empty) {
//     tcpListener* client = new tcpListener("dummy", 30003);
//     bool status = client->connected;
//     delete client;
//     ASSERT_EQ(false, status);
// }
 
// TEST(Try_To_Connnect_Unknown_Port, dummy) {
//     tcpListener* client = new tcpListener("localhost", 10);
//     bool status = client->connected;
//     delete client;
//     ASSERT_EQ(false, status);
// }
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}