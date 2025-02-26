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
    // Validate input parameters to prevent XML injection attacks
    if (username.empty() || password.empty()) {
        throw std::invalid_argument("Username and password must not be empty.");
    }

    // Sanitize inputs to prevent any form of injection
    std::string sanitized_username = std::regex_replace(username, std::regex("[^a-zA-Z0-9_]"), "");
    std::string sanitized_password = std::regex_replace(password, std::regex("[^a-zA-Z0-9_]"), "");

    std::map<std::string, std::string> student_info;

    // Parse the XML data manually using simple string operations
    std::istringstream xml_stream(xml_data);
    std::string line;
    bool found_student = false;

    while (std::getline(xml_stream, line)) {
        if (line.find("<username>") != std::string::npos) {
            size_t start = line.find("<username>") + 10;
            size_t end = line.find("</username>", start);
            std::string xml_username = line.substr(start, end - start);

            std::getline(xml_stream, line);
            start = line.find("<password>") + 10;
            end = line.find("</password>", start);
            std::string xml_password = line.substr(start, end - start);

            if (xml_username == sanitized_username && xml_password == sanitized_password) {
                found_student = true;
                std::getline(xml_stream, line);
                start = line.find("<name>") + 6;
                end = line.find("</name>", start);
                student_info["name"] = line.substr(start, end - start);

                std::getline(xml_stream, line);
                start = line.find("<citizenship>") + 14;
                end = line.find("</citizenship>", start);
                student_info["citizenship"] = line.substr(start, end - start);

                std::getline(xml_stream, line);
                start = line.find("<age>") + 5;
                end = line.find("</age>", start);
                student_info["age"] = line.substr(start, end - start);
                break; // Exit once we found the student
            }
        }
    }

    if (!found_student) {
        return {}; // Return an empty map if no student found
    }

    return student_info; // Return the found information
}