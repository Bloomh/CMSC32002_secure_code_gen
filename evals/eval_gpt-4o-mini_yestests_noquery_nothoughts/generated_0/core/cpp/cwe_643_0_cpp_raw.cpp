```
#include <string>
#include <map>
#include <stdexcept>
#include <iostream>
#include <libxml/parser.h>
#include <libxml/xpath.h>

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
    xmlDocPtr doc = xmlParseMemory(xml_data.c_str(), xml_data.size());
    if (doc == nullptr) {
        throw std::runtime_error("Failed to parse XML data");
    }
    
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == nullptr) {
        xmlFreeDoc(doc);
        throw std::runtime_error("Failed to create XPath context");
    }
    
    // Escape user input to prevent XPath injection
    std::string safe_username = xmlXPathEscape(username);
    std::string safe_password = xmlXPathEscape(password);
    
    // Construct the XPath query
    std::string xpath_query = "/students/student[username='" + safe_username + "' and password='" + safe_password + "']";
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression(reinterpret_cast<const xmlChar*>(xpath_query.c_str()), xpathCtx);
    if (xpathObj == nullptr) {
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        throw std::runtime_error("Failed to evaluate XPath expression");
    }
    
    if (xpathObj->nodesetval->nodeNr > 0) {
        xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
        for (xmlNodePtr child = studentNode->children; child; child = child->next) {
            if (child->type == XML_ELEMENT_NODE) {
                std::string content = reinterpret_cast<const char*>(xmlNodeGetContent(child));
                std::string nodeName = reinterpret_cast<const char*>(child->name);
                student_info[nodeName] = content;
            }
        }
    }
    
    // Cleanup
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    
    return student_info;
}

std::string xmlXPathEscape(const std::string& input) {
    std::string output;
    for (char ch : input) {
        if (ch == '"') output += "&quot;";
        else if (ch == '&') output += "&amp;";
        else if (ch == '<') output += "&lt;";
        else if (ch == '>') output += "&gt;";
        else output += ch;
    }
    return output;
}
```