#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Book.h"

int cout = 0; // won't compile if headers don't follow convention regarding namespaces

enum AppErrors {
    CannotOpenFile = 1, // An input file cannot be opened
    BadArgumentCount = 2, // The application didn't receive enough parameters
};

// ws books.txt
int main(int argc, char** argv) {
    std::cout << "Command Line:\n";
    std::cout << "--------------------------\n";
    for (int i = 0; i < argc; ++i)
        std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
    std::cout << "--------------------------\n\n";

    // get the books
    std::vector<seneca::Book> library;
    if (argc == 2) {
        std::ifstream file(argv[1]);
        if (file.is_open()) {
            std::string line;
            while (getline(file, line)) {
                if (line[0] != '#') {
                    library.emplace_back(seneca::Book(line));
                }
            }
            file.close();
        } else {
            std::cerr << "ERROR: Cannot open file '" << argv[1] << "'." << std::endl;
            exit(AppErrors::CannotOpenFile);
        }
    } else {
        std::cerr << "ERROR: Incorrect number of arguments.\n";
        exit(AppErrors::BadArgumentCount);
    }

    double usdToCadRate = 1.3;
    double gbpToCadRate = 1.5;

    auto fixPrice = [=](seneca::Book& book) {
        if (book.country() == "US") {
            book.price() *= usdToCadRate;
        } else if (book.country() == "UK" && book.year() >= 1990 && book.year() <= 1999) {
            book.price() *= gbpToCadRate;
        }
    };

    std::cout << "-----------------------------------------\n";
    std::cout << "The library content\n";
    std::cout << "-----------------------------------------\n";
    for (const auto& book : library) {
        std::cout << book << std::endl;
    }
    std::cout << "-----------------------------------------\n\n";

    for (auto& book : library) {
        fixPrice(book);
    }

    std::cout << "-----------------------------------------\n";
    std::cout << "The library content (updated prices)\n";
    std::cout << "-----------------------------------------\n";
    for (const auto& book : library) {
        std::cout << book << std::endl;
    }
    std::cout << "-----------------------------------------\n";

    return cout;
}