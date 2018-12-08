#include <gtest/gtest.h>
#include "TCPListener.h"

// TEST(TCPListener_Construct_with_Dummy_Hostname, Not_Segfault){
//     //ASSERT_EXIT((new TCPListener("dummy", 30003),exit(0)),::testing::ExitedWithCode(0),".*");
//     EXPECT_DEATH(new TCPListener("dummy", 30003),"SEGMENTATION FAULT");
// }

// @todo: Comment out if above test is passed.
// TEST(Try_To_Connect_Unknown_Host, empty) {
//     TCPListener* client = new TCPListener("dummy", 30003);
//     bool status = client->connected;
//     delete client;
//     ASSERT_EQ(false, status);
// }
 
// TEST(Try_To_Connnect_Unknown_Port, dummy) {
//     TCPListener* client = new TCPListener("localhost", 10);
//     bool status = client->connected;
//     delete client;
//     ASSERT_EQ(false, status);
// }
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}