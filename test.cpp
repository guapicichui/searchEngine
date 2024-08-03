#include "SplitTool.hh"

void test()
{
    std::string str = "This header should be the first thing seen when viewing this Project\
Gutenberg file. Please do not remove it.  Do not change or edit the\
header without written permission.\
Please read the \"legal small print,\" and other information about the\
eBook and Project Gutenberg at the bottom of this file.  Included is\
important information about your specific rights and restrictions in\n\
how the file may be used.  You can also find out about how to make a\
donation to Project Gutenberg, and how to get involved.";
    std::vector<std::string> result;
    SplitTool::getInstance().makePhrasesEn(str, result);
    std::cout << result << std::endl;
}

int main()
{
    test();
}