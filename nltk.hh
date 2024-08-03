#ifndef __NLTK_HH__
#define __NLTK_HH__
#include <python3.10/Python.h>
#include <vector>
#include <string>
#include "logger.hh"

class Nltk{
    Nltk(const Nltk&) = delete;
    Nltk(Nltk&&) = delete; 
private:
    Nltk();
public:
    static Nltk& getInstance();
    ~Nltk();
    std::vector<std::string> nltkExtractPhrase(std::string text);
};

#endif