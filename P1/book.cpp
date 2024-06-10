#include "Book.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>

namespace seneca {

Book::Book(const std::string& strBook) {
    std::stringstream ss(strBook);
    std::string token;
    size_t index = 0;

    std::vector<std::string> tokens;
    while (getline(ss, token, ',')) {
        token.erase(0, token.find_first_not_of(" "));
        token.erase(token.find_last_not_of(" ") + 1);
        tokens.push_back(token);
    }

    if (tokens.size() >= 5) {
        m_author = tokens[0];
        m_title = tokens[1];
        m_country = tokens[2];

        try {
            m_price = std::stod(tokens[3]);
        } catch (const std::invalid_argument& e) {
            m_price = 0.0;
        } catch (const std::out_of_range& e) {
            m_price = 0.0;
        }

        try {
            m_year = std::stoi(tokens[4]);
        } catch (const std::invalid_argument& e) {
            m_year = 0;
        } catch (const std::out_of_range& e) {
            m_year = 0;
        }

        if (tokens.size() > 5) {
            m_description = tokens[5];
            for (size_t i = 6; i < tokens.size(); ++i) {
                m_description += ", " + tokens[i];
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << std::left
       << std::setw(20) << book.m_author << " | "
       << std::setw(22) << book.m_title << " | "
       << std::setw(5) << book.m_country << " | ";

    if (book.m_year != 0) {
        os << std::setw(4) << book.m_year << " | ";
    } else {
        os << std::setw(4) << "N/A" << " | ";
    }

    if (book.m_price != 0.0) {
        os << std::setw(6) << std::fixed << std::setprecision(2) << book.m_price << " | ";
    } else {
        os << std::setw(6) << "N/A" << " | ";
    }

    os << book.m_description;

    return os;
}

}
