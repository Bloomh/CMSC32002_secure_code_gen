#include <string>
#include <map>
#include <sstream>
#include <algorithm>

std::string extract_element(const std::string& xml, const std::string& element) {
    std::string start_tag = "<" + element + ">";
    std::string end_tag = "</" + element + ">";
    size_t start = xml.find(start_tag);
    if (start == std::string::npos) return "";
    start += start_tag.length();
    size_t end = xml.find(end_tag, start);
    if (end == std::string::npos) return "";
    return xml.substr(start, end - start);
}

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> student_info;
    size_t pos = 0;
    std::string student_tag = "<student>";

    while ((pos = xml_data.find(student_tag, pos)) != std::string::npos) {
        size_t end_pos = xml_data.find("</student>", pos);
        if (end_pos == std::string::npos) break;
        std::string student_xml = xml_data.substr(pos, end_pos - pos + strlen("</student>")); // Extract student XML
        std::string xml_username = extract_element(student_xml, "username");
        std::string xml_password = extract_element(student_xml, "password");

        // Validate username and password
        if (xml_username == username && xml_password == password) {
            student_info["name"] = extract_element(student_xml, "name");
            student_info["citizenship"] = extract_element(student_xml, "citizenship");
            student_info["age"] = extract_element(student_xml, "age");
            break; // Found the matching student, exit loop
        }
        pos = end_pos + strlen("</student>"); // Move to the next student
    }

    return student_info;
}