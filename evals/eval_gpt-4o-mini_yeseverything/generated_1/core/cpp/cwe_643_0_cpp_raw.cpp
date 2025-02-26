#include <map>
#include <string>
#include <cctype>
#include <algorithm>

// Helper function to sanitize input and prevent XPath injection
std::string sanitize_input(const std::string& input) {
    std::string sanitized;
    // Allow only alphanumeric characters and underscores
    for (char c : input) {
        if (std::isalnum(c) || c == '_') {
            sanitized += c;
        }
    }
    return sanitized;
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

We can construct a XPath query and use it to search.

@param xml_data The XML data containing the student information.
@param username The username of the student to search for.
@param password The password of the student to search for.

@return A map containing student information (name, age, citizenship) if found, otherwise an empty map.
*/
std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> student_info;

    // Sanitize input to prevent XPath injection
    std::string sanitized_username = sanitize_input(username);
    std::string sanitized_password = sanitize_input(password);

    // Find the start of the <students> tag
    size_t start = xml_data.find("<students>");
    if (start == std::string::npos) return student_info;

    // Find the end of the <students> tag
    size_t end = xml_data.find("</students>", start);
    if (end == std::string::npos) return student_info;

    // Extract the students section
    std::string students_section = xml_data.substr(start, end - start);

    // Search for each student element
    size_t pos = 0;
    while ((pos = students_section.find("<student>", pos)) != std::string::npos) {
        size_t student_end = students_section.find("</student>", pos);
        if (student_end == std::string::npos) break;

        std::string student_info_str = students_section.substr(pos, student_end - pos);

        // Extract username and password
        std::string xml_username = student_info_str.substr(student_info_str.find("<username>") + 10);
        xml_username = xml_username.substr(0, xml_username.find("</username>"));

        std::string xml_password = student_info_str.substr(student_info_str.find("<password>") + 10);
        xml_password = xml_password.substr(0, xml_password.find("</password>"));

        // Validate username and password
        if (xml_username == sanitized_username && xml_password == sanitized_password) {
            // Extract other details
            student_info["name"] = student_info_str.substr(student_info_str.find("<name>") + 6);
            student_info["name"] = student_info["name"].substr(0, student_info["name"].find("</name>"));
            student_info["age"] = student_info_str.substr(student_info_str.find("<age>") + 5);
            student_info["age"] = student_info["age"].substr(0, student_info["age"].find("</age>"));
            student_info["citizenship"] = student_info_str.substr(student_info_str.find("<citizenship>") + 15);
            student_info["citizenship"] = student_info["citizenship"].substr(0, student_info["citizenship"].find("</citizenship>"));
            break;
        }
        pos = student_end + 10; // Move past </student>
    }

    return student_info;
}