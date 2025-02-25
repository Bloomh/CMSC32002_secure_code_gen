```
#include <map>
#include <string>
#include <stdexcept>
#include <tinyxml2.h>
#include <iostream>
#include <openssl/sha.h>
#include <iomanip>

// Function to hash passwords securely
std::string hash_password(const std::string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(password.c_str()), password.size(), hash);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

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
        throw std::runtime_error("Failed to parse XML data.");
    }
    
    tinyxml2::XMLElement* root = doc.FirstChildElement("students");
    if (!root) {
        throw std::runtime_error("No students element found.");
    }
    
    std::string hashed_password = hash_password(password);

    for (tinyxml2::XMLElement* student = root->FirstChildElement("student"); student != nullptr; student = student->NextSiblingElement("student")) {
        const char* user = student->FirstChildElement("username") ? student->FirstChildElement("username")->GetText() : nullptr;
        const char* pass = student->FirstChildElement("password") ? student->FirstChildElement("password")->GetText() : nullptr;
        
        // Securely compare username and hashed password
        if (user && pass && username == user && hashed_password == hash_password(pass)) {
            student_info["name"] = student->FirstChildElement("name") ? student->FirstChildElement("name")->GetText() : "";
            student_info["age"] = student->FirstChildElement("age") ? student->FirstChildElement("age")->GetText() : "";
            student_info["citizenship"] = student->FirstChildElement("citizenship") ? student->FirstChildElement("citizenship")->GetText() : "";
            break;
        }
    }
    
    return student_info;
}
```