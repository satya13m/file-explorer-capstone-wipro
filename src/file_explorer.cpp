#include <iostream>
#include <filesystem>
#include <string>
using namespace std;
namespace fs = std::filesystem;

int main() {
    string current_path = fs::current_path();
    cout << "Current Directory: " << current_path << endl;

    cout << "Files in directory:\n";
    for (const auto& entry : fs::directory_iterator(current_path)) {
        cout << " - " << entry.path().filename().string() << endl;
    }
    return 0;
}