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
#include <string>
#include <map>
#include <tinyxml2.h>
#include <iostream>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError result = doc.Parse(xml_data.c_str());
    std::map<std::string, std::string> student_info;

    if (result != tinyxml2::XML_SUCCESS) {
        std::cerr << "Error parsing XML data." << std::endl;
        return student_info; // Return empty map on parse error.
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement("students");
    if (!root) {
        return student_info; // Return empty map if no students element.
    }

    for (tinyxml2::XMLElement* student = root->FirstChildElement("student"); student != nullptr; student = student->NextSiblingElement("student")) {
        const char* user_elem = student->FirstChildElement("username") ? student->FirstChildElement("username")->GetText() : nullptr;
        const char* pass_elem = student->FirstChildElement("password") ? student->FirstChildElement("password")->GetText() : nullptr;

        // Check for null pointers to prevent crashes and ensure secure comparison.
        if (user_elem && pass_elem && username == user_elem && password == pass_elem) {
            const char* name_elem = student->FirstChildElement("name") ? student->FirstChildElement("name")->GetText() : nullptr;
            const char* citizenship_elem = student->FirstChildElement("citizenship") ? student->FirstChildElement("citizenship")->GetText() : nullptr;
            const char* age_elem = student->FirstChildElement("age") ? student->FirstChildElement("age")->GetText() : nullptr;

            // Store the valid student information in the map, checking for null elements.
            if (name_elem) student_info["name"] = name_elem;
            if (citizenship_elem) student_info["citizenship"] = citizenship_elem;
            if (age_elem) student_info["age"] = age_elem;
            break;
        }
    }

    return student_info;
}