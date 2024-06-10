#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>

namespace seneca {

class SpellChecker {
    std::string m_badWords[6];
    std::string m_goodWords[6];
    size_t m_replacements[6]{};

public:
    SpellChecker(const char* filename) {
        std::ifstream file(filename);
        if (!file) {
            throw "Bad file name!";
        }

        std::string line;
        size_t index = 0;
        while (std::getline(file, line) && index < 6) {
            size_t pos = line.find(' ');
            m_badWords[index] = line.substr(0, pos);

            while (line[pos] == ' ') pos++;

            m_goodWords[index] = line.substr(pos);
            index++;
        }
    }

    void operator()(std::string& text) {
        for (size_t i = 0; i < 6; i++) {
            size_t pos = text.find(m_badWords[i]);
            while (pos != std::string::npos) {
                text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
                m_replacements[i]++;
                pos = text.find(m_badWords[i], pos + m_goodWords[i].length());
            }
        }
    }

    void showStatistics(std::ostream& out) const {
        for (size_t i = 0; i < 6; i++) {
            out << std::setw(15) << m_badWords[i] << ": " << m_replacements[i] << " replacements" << std::endl;
        }
    }
};

}

#endif // SENECA_SPELLCHECKER_H
