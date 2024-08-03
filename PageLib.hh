#ifndef _PAGELIB_HH_
#define _PAGELIB_HH_
#include "HandleXML.hh"
#include "SimHashPage.hh"
#include "HandlePage.hh"

class PageLib {
public: 
    PageLib();    
    void create();
    void store();
private:
    
private:
    SimHashPage _simHashPage;
    HandleXML _handleXML;
    HandlePage _handlePage;
};

#endif //_PAGELIB_H