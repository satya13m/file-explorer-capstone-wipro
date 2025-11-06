#include <iostream>
#include <filesystem>
#include <iomanip>
#include <chrono>
#include <ctime>

using namespace std;
namespace fs = std::filesystem;

#define BLUE   "\033[34m"
#define GREEN  "\033[32m"
#define YELLOW "\033[33m"
#define RESET  "\033[0m"


string getLastWriteTime(const fs::path &path) {
    auto ftime = fs::last_write_time(path);
    auto sctp = chrono::time_point_cast<chrono::system_clock::duration>(
        ftime - fs::file_time_type::clock::now() + chrono::system_clock::now()
    );

    std::time_t cftime = chrono::system_clock::to_time_t(sctp);
    string timeStr = std::ctime(&cftime);
    timeStr.pop_back(); 
    return timeStr;
}

void listFiles(const fs::path &path) {
    cout << "\n📂 Listing files in: " << YELLOW << path.string() << RESET << "\n";
    cout << "----------------------------------------------------\n";

    for (const auto &entry : fs::directory_iterator(path)) {
        string timeStr = getLastWriteTime(entry.path());

        if (fs::is_directory(entry)) {
            cout << BLUE << "[DIR]  " << RESET
                 << left << setw(25) << entry.path().filename().string();
        } else {
            cout << GREEN << "[FILE] " << RESET
                 << left << setw(25) << entry.path().filename().string();
        }

        cout << " " << timeStr << endl;
    }
}

int main() {
    fs::path current = fs::current_path();

    try {
        listFiles(current);
    } catch (const fs::filesystem_error &e) {
        cerr << " Error: " << e.what() << endl;
    }

    cout << "\n Use this explorer to view directory files.\n";
    cout << " Next Day (Day 2): Add navigation commands (cd, pwd).\n";

    return 0;
}
