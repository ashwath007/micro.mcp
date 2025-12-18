#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

void printDirectoryTree(const std::string& path, int depth = 0) {
    if (depth > 10) {  // Prevent infinite recursion (safety limit)
        std::cout << "Depth limit reached\n";
        return;
    }

    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            for (int i = 0; i < depth; ++i) {
                std::cout << "  ";  // Indentation for depth
            }
            std::cout << entry.path().filename().string();

            if (entry.is_directory()) {
                std::cout << "/\n";
                printDirectoryTree(entry.path().string(), depth + 1);  // Recursive call
            } else {
                std::cout << "\n";
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << " (Error: " << e.what() << ")\n";
    }
}

int main() {
    std::string startPath = ".";  // Current directory; change as needed
    std::cout << "Directory tree of: " << fs::absolute(startPath) << "\n";
    printDirectoryTree(startPath);
    return 0;
}
