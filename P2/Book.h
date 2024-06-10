#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

namespace seneca {

class Book {
    std::string m_author;
    std::string m_title;
    std::string m_country;
    size_t m_year;
    double m_price;
    std::string m_description;

public:
    Book() : m_year(0), m_price(0.0) {}

    Book(const std::string& strBook) {
        std::stringstream ss(strBook);
        std::string token;
        size_t index = 0;

        while (getline(ss, token, ',')) {
            token.erase(0, token.find_first_not_of(" "));
            token.erase(token.find_last_not_of(" ") + 1);

            switch (index) {
            case 0: m_author = token; break;
            case 1: m_title = token; break;
            case 2: m_country = token; break;
            case 3: m_year = std::stoul(token); break;
            case 4: m_price = std::stod(token); break;
            case 5: m_description = token; break;
            }

            index++;
        }
    }

    const std::string& title() const {
        return m_title;
    }

    template<typename T>
    void fixSpelling(T& spellChecker) {
        spellChecker(m_description);
    }

    friend std::ostream& operator<<(std::ostream& os, const Book& book) {
        os << std::setw(20) << book.m_author << " | "
           << std::setw(25) << book.m_title << " | "
           << std::setw(5) << book.m_country << " | "
           << std::setw(4) << book.m_year << " | "
           << std::setw(6) << std::fixed << std::setprecision(2) << book.m_price << " | "
           << book.m_description;
        return os;
    }
};

}

#endif // SENECA_BOOK_H
