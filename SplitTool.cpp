#include "SplitTool.hh"

static size_t nBytesCode(const char ch)
{
	if(ch & (1 << 7))
	{
		int nBytes = 1;
		for(int idx = 0; idx != 6; ++idx)
		{
			if(ch & (1 << (6 - idx)))
			{
				++nBytes;	
			}
			else
				break;
		}
		return nBytes;
	}
	return 1;
}  

SplitTool::SplitTool() {}

SplitTool& SplitTool::getInstance()
{
    static SplitTool split;
    return split;
}
std::vector<std::string> &SplitTool::makeWordsCn(std::string text, std::vector<std::string> &result)
{
    std::string::iterator fast = text.begin(), slow = text.begin();
    while (fast != text.end())
    {
        if (*fast != '\n')
            *slow++ = *fast++;
    }
    text.resize(slow - text.begin());
    std::vector<std::pair<std::string, std::string>> temp;
    jiebaSingle::getInstance().Tag(text, temp);
    for (auto elem : temp)
    {
        if (elem.second != "x" && elem.second != "eng")
            if (!std::isalnum(elem.first[0]))
                result.push_back(elem.first);
    }
    return result;
}

std::vector<std::string>& SplitTool::makeWordsEn(const std::string& text, std::vector<std::string> &result)
{
    
    std::string word;
    std::istringstream stream(text);
    while (stream >> word)
    {
        std::string::iterator fast = word.begin(), slow = word.begin();
        while (fast != word.end())
            if (std::isalpha(*fast))
            {
                *slow++ = *fast++;
            }
            else
                fast++;
        word.resize(slow - word.begin());
        result.push_back(word);
    }
    return result;
}
std::vector<char> SplitTool::makeAlphas(const std::string& word)
{
    std::vector<char> result;
    for (char ch : word)
        if (std::isalpha(ch))
            result.push_back(ch);
    return result;
}
std::vector<std::string> &SplitTool::makePhrasesEn(const std::string& text, std::vector<std::string> &result)
{
    std::cout << text << std::endl;
    for (std::string elem : Nltk::getInstance().nltkExtractPhrase(text))
        result.push_back(elem);
    std::cout << result << std::endl;
    return result;
}
std::vector<std::string> SplitTool::makeCharacterCn(const std::string& text)
{
    std::vector<std::string> result;
    for (int i = 0; i < text.size();)
    {
        std::string ch;
        for (int j = 0; j < nBytesCode(text[i]); ++j)
        {
            ch.push_back(text[j + i]); 
        }
        result.push_back(ch);
        i += nBytesCode(text[i]);
    }
    return result;
}