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
#define RED    "\033[31m"
#define RESET  "\033[0m"

// DAY-1

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


//DAY-2
int main() {
    fs::path current = fs::current_path();
    string command, arg;

    while (true) {
        cout << YELLOW << current.string() << RESET << " $ ";
        cin >> command;

        if (command == "ls") {
            listFiles(current);
        }
        else if (command == "pwd") {
            cout << "Current Directory: " << GREEN << current.string() << RESET << "\n";
        }
        else if (command == "cd") {
            cin >> arg;
            fs::path target = (arg == "..") ? current.parent_path() : current / arg;
            if (fs::exists(target) && fs::is_directory(target)) {
                current = fs::canonical(target);
                cout << " Moved to: " << GREEN << current.string() << RESET << "\n";
            } else {
                cout << RED << " Directory not found!\n" << RESET;
            }
        }
        else if (command == "help") {
            cout << "\nAvailable commands:\n"
                 << "--------------------------------\n"
                 << "ls       → List files\n"
                 << "pwd      → Print current directory\n"
                 << "cd <dir> → Change directory\n"
                 << "help     → Show this help menu\n"
                 << "exit     → Quit the explorer\n"
                 << "--------------------------------\n";
        }
        else if (command == "exit") {
            cout << GREEN << "\n Exiting SatyaFileExplorer. Goodbye!\n" << RESET;
            break;
        }
        else {
            cout << RED << " Unknown command. Type 'help' to see available commands.\n" << RESET;
        }
    }

    return 0;
}



