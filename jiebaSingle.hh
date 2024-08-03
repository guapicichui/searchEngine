#ifndef __jiebaSingle_HH_
#define __jiebaSingle_HH_
#include "simhash/cppjieba/Jieba.hpp"

static const char* const DICT_PATH = "./simhash/dict/jieba.dict.utf8";
static const char* const HMM_PATH = "./simhash/dict/hmm_model.utf8";
static const char* const USER_DICT_PATH = "./simhash/dict/user.dict.utf8";
static const char* const IDF_PATH = "./simhash/dict/idf.utf8";
static const char* const STOP_WORD_PATH = "./simhash/dict/stop_words.utf8";

class jiebaSingle{
public:
    static cppjieba::Jieba& getInstance()
    {
        static cppjieba::Jieba jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);
        return jieba;
    }
};

#endif