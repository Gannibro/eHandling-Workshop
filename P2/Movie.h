#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

namespace seneca {

class Movie {
    std::string m_title;
    size_t m_year;
    std::string m_description;

public:
    Movie() : m_year(0) {}

    const std::string& title() const {
        return m_title;
    }

    Movie(const std::string& strMovie) {
        std::stringstream ss(strMovie);
        std::string token;
        size_t index = 0;

        while (getline(ss, token, ',')) {
            token.erase(0, token.find_first_not_of(" "));
            token.erase(token.find_last_not_of(" ") + 1);

            switch (index) {
            case 0: m_title = token; break;
            case 1: m_year = std::stoul(token); break;
            case 2: m_description = token; break;
            }

            index++;
        }
    }

    template<typename T>
    void fixSpelling(T& spellChecker) {
        spellChecker(m_title);
        spellChecker(m_description);
    }

    friend std::ostream& operator<<(std::ostream& os, const Movie& movie) {
        os << std::left << std::setw(40) << movie.m_title << " | "
           << std::setw(4) << movie.m_year << " | "
           << movie.m_description;
        return os;
    }
};

}

#endif // SENECA_MOVIE_H
