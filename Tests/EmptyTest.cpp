#include "gtest/gtest.h"
#include <wx/xml/xml.h>
#include <fstream>
#include <wx/filename.h>
#include <wx/stdpaths.h>

using namespace std;

const wstring umlXml = L"data/uml.xml";


TEST(EmptyTest, ExampleTest){


  ASSERT_EQ(7, 7);
}

TEST(EmptyTest, Load){
    wxXmlDocument xmlDoc;
    ASSERT_TRUE(xmlDoc.Load( L"data/uml.xml"));
}
