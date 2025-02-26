```
#include <string>
#include <map>
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/xpath.h>
#include <libxml2/libxml/xpathInternals.h>

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
    // Initialize the map to hold student information
    std::map<std::string, std::string> student_info;

    // Validate inputs (simple validation)
    if (username.empty() || password.empty()) {
        return student_info; // Return empty map if input is invalid
    }

    // Initialize the XML parser
    xmlDocPtr doc = xmlParseMemory(xml_data.c_str(), xml_data.size());
    if (doc == nullptr) {
        return student_info; // Return empty map on parse error
    }

    // Create an XPath context
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == nullptr) {
        xmlFreeDoc(doc);
        return student_info; // Return empty map on context error
    }

    // Escape username and password to prevent XPath injection
    std::string safe_username = xmlXPathEscape(username);
    std::string safe_password = xmlXPathEscape(password);

    // Construct the XPath query to find the student
    std::string xpathQuery = "/students/student[username='" + safe_username + "' and password='" + safe_password + "']";
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression(reinterpret_cast<const xmlChar*>(xpathQuery.c_str()), xpathCtx);
    if (xpathObj == nullptr) {
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return student_info; // Return empty map on evaluation error
    }

    // Check if we found a student
    if (xpathObj->nodesetval->nodeNr > 0) {
        xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
        // Extract the name, age, and citizenship
        for (xmlNodePtr child = studentNode->children; child; child = child->next) {
            if (child->type == XML_ELEMENT_NODE) {
                std::string nodeName = reinterpret_cast<const char*>(child->name);
                std::string nodeValue = reinterpret_cast<const char*>(xmlNodeGetContent(child));
                student_info[nodeName] = nodeValue;
            }
        }
    }

    // Clean up
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info;
}

// Helper function to escape XPath input
std::string xmlXPathEscape(const std::string& input) {
    std::string escaped;
    for (char c : input) {
        // Escape single quotes and backslashes
        if (c == '\' || c == '"' || c == '\n' || c == '\r' || c == '\t') {
            escaped += '\';
        }
        escaped += c;
    }
    return escaped;
}
```