//#include "../src/main.cpp"
//#define CATCH_CONFIG_MAIN
//#include "catch.hpp"
//using namespace std;
//
///*
//	To check output (At the Project1 directory):
//		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
//*/
//
//TEST_CASE("BST Incorrect Commands", "[flag]"){
//
//    GatorAVLTree tree;
//    int num_of_coms = 5;
//
//// Unit Testing for my void print statements inspired Jarrod Humpel's answer from discord answering
//// Unit Testing Void Functions on 6/8/24 as well as by the FAQ resource on stackoverflow at
//// https://stackoverflow.com/questions/4191089/how-to-unit-test-function-writing-to-stdout-stdcout
//    vector<string> myCommands {"insert \"A11y\" 45679999", "innap \"Adam\" 12345678",
//                    "remove 2", "print", "insert \"Bill\" 1024"};
//
//    std::ostringstream oss;
//    std::streambuf* cout_streambuf = std::cout.rdbuf();
//    std::cout.rdbuf(oss.rdbuf());
//
//
//
//    for (int i = 0; i < num_of_coms; i++) {
//        // Collect input
//        string command = myCommands[i];
//
//        int command_chars = 0;
//        string subcommand = "";
//        while (command[command_chars] != ' ') {
//            if (subcommand == "printInorder") {
//                break;
//            }
//            else if (subcommand == "printPreorder") {
//                break;
//            }
//            else if (subcommand == "printPostorder") {
//                break;
//            }
//            else if (subcommand == "printLevelCount") {
//                break;
//            }
//            subcommand += command[command_chars];
//            command_chars++;
//        }
//
//        string name = "";
//        string id = "";
//        string N = "";
//
//        if (subcommand == "insert") {
//            int name_letters = 8;
//            while (command[name_letters] != '"') {
//                name += command[name_letters];
//                name_letters++;
//            }
//
//            int id_place = name_letters + 2;
//
//            id = command.substr(id_place);
//        }
//        else if (subcommand == "search" && command[7] == '"') {
//            name += command[8];
//            int name_letters = 9;
//            while (command[name_letters] != '"') {
//                name += command[name_letters];
//                name_letters++;
//            }
//        }
//        else if (subcommand == "remove" || subcommand == "search") {
//            id = command.substr(7);
//        }
//        else if (subcommand == "removeInorder") {
//            N = command.substr(14);
//        }
//        // else command is print command
//
//        // Execute based on command
//        if (subcommand == "insert") {
//            tree.insert(name,id);
//        }
//        else if (subcommand == "search" && command[7] == '"') {
//            tree.searchName(name);
//        }
//        else if (subcommand == "remove" || subcommand == "search") {
//            if (subcommand == "remove") {
//                tree.remove(id);
//            }
//            else {
//                tree.searchID(id);
//            }
//        }
//        else if (subcommand == "removeInorder") {
//            tree.removeInorder(N);
//        }
//        else {
//            if (subcommand == "printInorder") {
//                tree.printInorder();
//            }
//            else if (subcommand == "printPreorder") {
//                tree.printPreorder();
//            }
//            else if (subcommand == "printPostorder") {
//                tree.printPostorder();
//            }
//            else if (subcommand == "printLevelCount") {
//                tree.printLevelCount();
//            }
//            else {
//                cout << "unsuccessful";
//            }
//        }
//        // Proper end lines
//        if (i < num_of_coms - 1) {
//            cout << endl;
//        }
//    }
//
//    std::cout.rdbuf(cout_streambuf);
//    REQUIRE(oss.str() == "unsuccessful\nunsuccessful\n"
//                         "unsuccessful\nunsuccessful\nunsuccessful");
//    std::cout << oss.str();
//}
//
//TEST_CASE("BST Three Edge Cases", "[flag]") {
//    GatorAVLTree tree;
//    int num_of_coms = 3;
//
//    // Test when nodes don't exist for these functions
//    vector<string> myCommands {"remove \"Ally\"", "removeInorder 2",
//                "search 12348765"};
//
//    std::ostringstream oss;
//    std::streambuf* cout_streambuf = std::cout.rdbuf();
//    std::cout.rdbuf(oss.rdbuf());
//
//    for (int i = 0; i < num_of_coms; i++) {
//        // Collect input
//        string command = myCommands[i];
//
//        int command_chars = 0;
//        string subcommand = "";
//        while (command[command_chars] != ' ') {
//            if (subcommand == "printInorder") {
//                break;
//            }
//            else if (subcommand == "printPreorder") {
//                break;
//            }
//            else if (subcommand == "printPostorder") {
//                break;
//            }
//            else if (subcommand == "printLevelCount") {
//                break;
//            }
//            subcommand += command[command_chars];
//            command_chars++;
//        }
//
//        string name = "";
//        string id = "";
//        string N = "";
//
//        if (subcommand == "insert") {
//            int name_letters = 8;
//            while (command[name_letters] != '"') {
//                name += command[name_letters];
//                name_letters++;
//            }
//
//            int id_place = name_letters + 2;
//
//            id = command.substr(id_place);
//        }
//        else if (subcommand == "search" && command[7] == '"') {
//            name += command[8];
//            int name_letters = 9;
//            while (command[name_letters] != '"') {
//                name += command[name_letters];
//                name_letters++;
//            }
//        }
//        else if (subcommand == "remove" || subcommand == "search") {
//            id = command.substr(7);
//        }
//        else if (subcommand == "removeInorder") {
//            N = command.substr(14);
//        }
//        // else command is print command
//
//        // Execute based on command
//        if (subcommand == "insert") {
//            tree.insert(name,id);
//        }
//        else if (subcommand == "search" && command[7] == '"') {
//            tree.searchName(name);
//        }
//        else if (subcommand == "remove" || subcommand == "search") {
//            if (subcommand == "remove") {
//                tree.remove(id);
//            }
//            else {
//                tree.searchID(id);
//            }
//        }
//        else if (subcommand == "removeInorder") {
//            tree.removeInorder(N);
//        }
//        else {
//            if (subcommand == "printInorder") {
//                tree.printInorder();
//            }
//            else if (subcommand == "printPreorder") {
//                tree.printPreorder();
//            }
//            else if (subcommand == "printPostorder") {
//                tree.printPostorder();
//            }
//            else if (subcommand == "printLevelCount") {
//                tree.printLevelCount();
//            }
//            else {
//                cout << "unsuccessful";
//            }
//        }
//        // Proper end lines
//        if (i < num_of_coms - 1) {
//            cout << endl;
//        }
//    }
//
//    std::cout.rdbuf(cout_streambuf);
//    REQUIRE(oss.str() == "unsuccessful\nunsuccessful\n"
//                         "unsuccessful");
//    std::cout << oss.str();
//}
//
//TEST_CASE("BST Four Rotations", "[flag]") {
//    GatorAVLTree tree;
//    int num_of_coms = 28;
//
//    // Test Left Rotation (Right Right Case), Right, Right Left, Left Right
//    vector<string> myCommands {"insert \"Adam\" 00000001", "insert \"Bob\" 00000002", "insert \"Charles\" 00000003",
//                               "printPreorder", "removeInorder 0", "removeInorder 0", "removeInorder 0",
//                               "insert \"Charles\" 00000003", "insert \"Bob\" 00000002", "insert \"Adam\" 00000001",
//                               "printPreorder", "removeInorder 0", "removeInorder 0", "removeInorder 0",
//                               "insert \"Adam\" 00000001", "insert \"Charles\" 00000003", "insert \"Bob\" 00000002",
//                               "printPreorder", "removeInorder 0", "removeInorder 0", "removeInorder 0",
//                               "insert \"Charles\" 00000003", "insert \"Adam\" 00000001", "insert \"Bob\" 00000002",
//                               "printPreorder", "removeInorder 0", "removeInorder 0", "removeInorder 0"};
//
//    std::ostringstream oss;
//    std::streambuf* cout_streambuf = std::cout.rdbuf();
//    std::cout.rdbuf(oss.rdbuf());
//
//    for (int i = 0; i < num_of_coms; i++) {
//        // Collect input
//        string command = myCommands[i];
//
//        int command_chars = 0;
//        string subcommand = "";
//        while (command[command_chars] != ' ') {
//            if (subcommand == "printInorder") {
//                break;
//            }
//            else if (subcommand == "printPreorder") {
//                break;
//            }
//            else if (subcommand == "printPostorder") {
//                break;
//            }
//            else if (subcommand == "printLevelCount") {
//                break;
//            }
//            subcommand += command[command_chars];
//            command_chars++;
//        }
//
//        string name = "";
//        string id = "";
//        string N = "";
//
//        if (subcommand == "insert") {
//            int name_letters = 8;
//            while (command[name_letters] != '"') {
//                name += command[name_letters];
//                name_letters++;
//            }
//
//            int id_place = name_letters + 2;
//
//            id = command.substr(id_place);
//        }
//        else if (subcommand == "search" && command[7] == '"') {
//            name += command[8];
//            int name_letters = 9;
//            while (command[name_letters] != '"') {
//                name += command[name_letters];
//                name_letters++;
//            }
//        }
//        else if (subcommand == "remove" || subcommand == "search") {
//            id = command.substr(7);
//        }
//        else if (subcommand == "removeInorder") {
//            N = command.substr(14);
//        }
//        // else command is print command
//
//        // Execute based on command
//        if (subcommand == "insert") {
//            tree.insert(name,id);
//        }
//        else if (subcommand == "search" && command[7] == '"') {
//            tree.searchName(name);
//        }
//        else if (subcommand == "remove" || subcommand == "search") {
//            if (subcommand == "remove") {
//                tree.remove(id);
//            }
//            else {
//                tree.searchID(id);
//            }
//        }
//        else if (subcommand == "removeInorder") {
//            tree.removeInorder(N);
//        }
//        else {
//            if (subcommand == "printInorder") {
//                tree.printInorder();
//            }
//            else if (subcommand == "printPreorder") {
//                tree.printPreorder();
//            }
//            else if (subcommand == "printPostorder") {
//                tree.printPostorder();
//            }
//            else if (subcommand == "printLevelCount") {
//                tree.printLevelCount();
//            }
//            else {
//                cout << "unsuccessful";
//            }
//        }
//        // Proper end lines
//        if (i < num_of_coms - 1) {
//            cout << endl;
//        }
//    }
//
//    std::cout.rdbuf(cout_streambuf);
//    REQUIRE(oss.str() == "successful\nsuccessful\nsuccessful\nBob, Adam, Charles\nsuccessful\nsuccessful\nsuccessful\n"
//                         "successful\nsuccessful\nsuccessful\nBob, Adam, Charles\nsuccessful\nsuccessful\nsuccessful\n"
//                         "successful\nsuccessful\nsuccessful\nBob, Adam, Charles\nsuccessful\nsuccessful\nsuccessful\n"
//                         "successful\nsuccessful\nsuccessful\nBob, Adam, Charles\nsuccessful\nsuccessful\nsuccessful");
//    std::cout << oss.str();
//}
//
//TEST_CASE("BST Three Deletions", "[flag]") {
//    GatorAVLTree tree;
//    int num_of_coms = 27;
//
//    // Test 0, 1, and 2 children
//    vector<string> myCommands {"insert \"Adam\" 00000001", "insert \"Bob\" 00000002", "insert \"Charles\" 00000003",
//                               "printPreorder", "remove 00000003", "printPreorder", "removeInorder 0", "removeInorder 0",
//                               "insert \"Bob\" 00000002", "insert \"Adam\" 00000001", "insert \"David\" 00000004",
//                               "insert \"Charles\" 00000003", "printPreorder", "remove 00000004", "printPreorder",
//                               "removeInorder 0", "removeInorder 0", "removeInorder 0",
//                               "insert \"Adam\" 00000001", "insert \"Bob\" 00000002", "insert \"Charles\" 00000003",
//                               "insert \"David\" 00000004", "insert \"Edward\" 00000005", "insert \"Finn\" 00000006",
//                               "printPreorder", "remove 00000004", "printPreorder"};
//
//    std::ostringstream oss;
//    std::streambuf* cout_streambuf = std::cout.rdbuf();
//    std::cout.rdbuf(oss.rdbuf());
//
//    for (int i = 0; i < num_of_coms; i++) {
//        // Collect input
//        string command = myCommands[i];
//
//        int command_chars = 0;
//        string subcommand = "";
//        while (command[command_chars] != ' ') {
//            if (subcommand == "printInorder") {
//                break;
//            }
//            else if (subcommand == "printPreorder") {
//                break;
//            }
//            else if (subcommand == "printPostorder") {
//                break;
//            }
//            else if (subcommand == "printLevelCount") {
//                break;
//            }
//            subcommand += command[command_chars];
//            command_chars++;
//        }
//
//        string name = "";
//        string id = "";
//        string N = "";
//
//        if (subcommand == "insert") {
//            int name_letters = 8;
//            while (command[name_letters] != '"') {
//                name += command[name_letters];
//                name_letters++;
//            }
//
//            int id_place = name_letters + 2;
//
//            id = command.substr(id_place);
//        }
//        else if (subcommand == "search" && command[7] == '"') {
//            name += command[8];
//            int name_letters = 9;
//            while (command[name_letters] != '"') {
//                name += command[name_letters];
//                name_letters++;
//            }
//        }
//        else if (subcommand == "remove" || subcommand == "search") {
//            id = command.substr(7);
//        }
//        else if (subcommand == "removeInorder") {
//            N = command.substr(14);
//        }
//        // else command is print command
//
//        // Execute based on command
//        if (subcommand == "insert") {
//            tree.insert(name,id);
//        }
//        else if (subcommand == "search" && command[7] == '"') {
//            tree.searchName(name);
//        }
//        else if (subcommand == "remove" || subcommand == "search") {
//            if (subcommand == "remove") {
//                tree.remove(id);
//            }
//            else {
//                tree.searchID(id);
//            }
//        }
//        else if (subcommand == "removeInorder") {
//            tree.removeInorder(N);
//        }
//        else {
//            if (subcommand == "printInorder") {
//                tree.printInorder();
//            }
//            else if (subcommand == "printPreorder") {
//                tree.printPreorder();
//            }
//            else if (subcommand == "printPostorder") {
//                tree.printPostorder();
//            }
//            else if (subcommand == "printLevelCount") {
//                tree.printLevelCount();
//            }
//            else {
//                cout << "unsuccessful";
//            }
//        }
//        // Proper end lines
//        if (i < num_of_coms - 1) {
//            cout << endl;
//        }
//    }
//
//    std::cout.rdbuf(cout_streambuf);
//    REQUIRE(oss.str() == "successful\nsuccessful\nsuccessful\nBob, Adam, Charles\nsuccessful\n"
//                         "Bob, Adam\nsuccessful\nsuccessful\n"
//                         "successful\nsuccessful\nsuccessful\nsuccessful\nBob, Adam, David, Charles\nsuccessful\n"
//                         "Bob, Adam, Charles\nsuccessful\nsuccessful\nsuccessful\n"
//                         "successful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\n"
//                         "David, Bob, Adam, Charles, Edward, Finn\nsuccessful\nEdward, Bob, Adam, Charles, Finn");
//    std::cout << oss.str();
//}
//
//TEST_CASE("BST 100 Nodes", "[flag]") {
//    GatorAVLTree tree;
//    int num_of_coms = 111;
//
//    vector<string> names {"blank", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p",
//                          "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "aa", "ab", "ac", "ad", "ae", "af", "ag",
//                          "ah", "ai", "aj", "ak", "al", "am", "an", "ao", "ap", "aq", "ar", "as", "at", "au", "av",
//                          "aw", "ax", "ay", "az", "ba", "bb", "bc", "bd", "be", "bf", "bg", "bh", "bi", "bj", "bk",
//                          "bl", "bm", "bn", "bo", "bp", "bq", "br", "bs", "bt", "bu", "bv", "bw", "bx", "by", "bz",
//                          "ca", "cb", "cc", "cd", "ce", "cf", "cg", "ch", "ci", "cj", "ck", "cl", "cm", "cn", "co",
//                          "cp", "cq", "cr", "cs", "ct", "cu", "cv"};
//
//    vector<string> myCommands {};
//    vector<string> expectedStudents{};
//
//    for (int i = 1; i < 101; i++) {
//        string id = "";
//        if (i < 10) {
//            id += "0000000";
//            id += to_string(i);
//        }
//        else if (i < 100) {
//            id += "000000";
//            id += to_string(i);
//        }
//        else {
//            id += "00000";
//            id += to_string(i);
//        }
//        string command = "insert \"";
//        command += names[i];
//        command += "\" ";
//        command += id;
//        myCommands.push_back(command);
//        expectedStudents.push_back(names[i]);
//    }
//
//    // Now remove at random
//    for (int i = 0; i < 10; i++) {
//        int random = rand() % 100;
//        string remove_command = "removeInorder ";
//        remove_command += to_string(random);
//        myCommands.push_back(remove_command);
//        expectedStudents.erase(expectedStudents.begin() + random);
//    }
//
//    myCommands.push_back("printInorder");
//
//    std::ostringstream oss;
//    std::streambuf* cout_streambuf = std::cout.rdbuf();
//    std::cout.rdbuf(oss.rdbuf());
//
//    for (int i = 0; i < num_of_coms; i++) {
//        // Collect input
//        string command = myCommands[i];
//
//        int command_chars = 0;
//        string subcommand = "";
//        while (command[command_chars] != ' ') {
//            if (subcommand == "printInorder") {
//                break;
//            }
//            else if (subcommand == "printPreorder") {
//                break;
//            }
//            else if (subcommand == "printPostorder") {
//                break;
//            }
//            else if (subcommand == "printLevelCount") {
//                break;
//            }
//            subcommand += command[command_chars];
//            command_chars++;
//        }
//
//        string name = "";
//        string id = "";
//        string N = "";
//
//        if (subcommand == "insert") {
//            int name_letters = 8;
//            while (command[name_letters] != '"') {
//                name += command[name_letters];
//                name_letters++;
//            }
//
//            int id_place = name_letters + 2;
//
//            id = command.substr(id_place);
//        }
//        else if (subcommand == "search" && command[7] == '"') {
//            name += command[8];
//            int name_letters = 9;
//            while (command[name_letters] != '"') {
//                name += command[name_letters];
//                name_letters++;
//            }
//        }
//        else if (subcommand == "remove" || subcommand == "search") {
//            id = command.substr(7);
//        }
//        else if (subcommand == "removeInorder") {
//            N = command.substr(14);
//        }
//        // else command is print command
//
//        // Execute based on command
//        if (subcommand == "insert") {
//            tree.insert(name,id);
//        }
//        else if (subcommand == "search" && command[7] == '"') {
//            tree.searchName(name);
//        }
//        else if (subcommand == "remove" || subcommand == "search") {
//            if (subcommand == "remove") {
//                tree.remove(id);
//            }
//            else {
//                tree.searchID(id);
//            }
//        }
//        else if (subcommand == "removeInorder") {
//            tree.removeInorder(N);
//        }
//        else {
//            if (subcommand == "printInorder") {
//                tree.printInorder();
//            }
//            else if (subcommand == "printPreorder") {
//                tree.printPreorder();
//            }
//            else if (subcommand == "printPostorder") {
//                tree.printPostorder();
//            }
//            else if (subcommand == "printLevelCount") {
//                tree.printLevelCount();
//            }
//            else {
//                cout << "unsuccessful";
//            }
//        }
//        // Proper end lines
//        if (i < num_of_coms - 1) {
//            cout << endl;
//        }
//    }
//
//    // Make string to compare to oss.str()
//    string compare_string = "";
//
//    for (int i = 0; i < 110; i++) {
//        compare_string += "successful\n";
//    }
//    for (int i = 0; i < 90; i++) {
//        compare_string += expectedStudents[i];
//        if (i == 89) {
//            break;
//        }
//        compare_string += ", ";
//    }
//
//    std::cout.rdbuf(cout_streambuf);
//    REQUIRE(oss.str() == compare_string);
//    std::cout << oss.str();
//}