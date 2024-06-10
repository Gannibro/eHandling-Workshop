// Book.h
#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include <string>

namespace seneca {

class Book {
private:
    std::string m_author;
    std::string m_title;
    std::string m_country;
    size_t m_year;
    double m_price;
    std::string m_description;

public:
    Book() = default;

    const std::string& title() const {
        return m_title;
    }

    const std::string& country() const {
        return m_country;
    }

    const size_t& year() const {
        return m_year;
    }

    double& price() {
        return m_price;
    }

    Book(const std::string& strBook);

    friend std::ostream& operator<<(std::ostream& os, const Book& book);
};

}

#endif