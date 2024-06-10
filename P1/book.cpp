#include "Book.h"
#include <sstream>
#include <iomanip>

namespace seneca {

Book::Book(const std::string& strBook) {
    std::stringstream ss(strBook);
    std::string token;
    size_t index = 0;

    while (getline(ss, token, ',')) {
        token.erase(0, token.find_first_not_of(" "));
        token.erase(token.find_last_not_of(" ") + 1);

        if (!token.empty()) {
            switch (index) {
            case 0:
                m_author = token;
                break;
            case 1:
                m_title = token;
                break;
            case 2:
                m_country = token;
                break;
            case 3:
                try {
                    m_price = std::stod(token);
                } catch (const std::invalid_argument& e) {
                    m_price = 0.0; // Set a default value for invalid input
                } catch (const std::out_of_range& e) {
                    m_price = 0.0; // Set a default value for out-of-range input
                }
                break;
            case 4:
                try {
                    m_year = std::stoi(token);
                } catch (const std::invalid_argument& e) {
                    m_year = 0; // Set a default value for invalid input
                } catch (const std::out_of_range& e) {
                    m_year = 0; // Set a default value for out-of-range input
                }
                break;
            case 5:
                m_description = token;
                break;
            }
        }

        index++;
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