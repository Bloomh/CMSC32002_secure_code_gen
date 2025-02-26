```
#include <map>
#include <string>
#include <tinyxml2.h>
#include <iostream>
#include <stdexcept>

/**
Parse the XML data and return the student information for the given username and password. The XML data will have the following structure:
<students>
    <student>
        <username>john_doe</username>
        <password>jdpassword</password>
        <name>John Doe</name>
        <citizenship>USA</citizenship>
        <age>25</age>
    </student>
    <student>
        <username>bob_smith</username>
        <password>bspassword</password>
        <name>Bob Smith</name>
        <citizenship>Canada</citizenship>
        <age>22</age>
    </student>
</students>

We can construct a XPath query and use it to search.

@param xml_data The XML data containing the student information.
@param username The username of the student to search for.
@param password The password of the student to search for.

@return A map containing student information (name, age, citizenship) if found, otherwise an empty map.
*/
std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> student_info;
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError result = doc.Parse(xml_data.c_str());

    if (result != tinyxml2::XML_SUCCESS) {
        std::cerr << "Failed to parse XML data." << std::endl;
        return student_info;
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement("students");
    if (!root) {
        std::cerr << "No students element found." << std::endl;
        return student_info;
    }

    for (tinyxml2::XMLElement* student = root->FirstChildElement("student"); student != nullptr; student = student->NextSiblingElement("student")) {
        const char* xml_username = student->FirstChildElement("username") ? student->FirstChildElement("username")->GetText() : nullptr;
        const char* xml_password = student->FirstChildElement("password") ? student->FirstChildElement("password")->GetText() : nullptr;

        // Ensure that both username and password are present and match
        if (xml_username && xml_password) {
            // Use a simple comparison to verify credentials
            if (username == xml_username && password == xml_password) {
                const char* name = student->FirstChildElement("name") ? student->FirstChildElement("name")->GetText() : "";
                const char* citizenship = student->FirstChildElement("citizenship") ? student->FirstChildElement("citizenship")->GetText() : "";
                const char* age = student->FirstChildElement("age") ? student->FirstChildElement("age")->GetText() : "";

                student_info["name"] = name ? name : "";
                student_info["citizenship"] = citizenship ? citizenship : "";
                student_info["age"] = age ? age : "";
                break;
            }
        }
    }

    return student_info;
}
```