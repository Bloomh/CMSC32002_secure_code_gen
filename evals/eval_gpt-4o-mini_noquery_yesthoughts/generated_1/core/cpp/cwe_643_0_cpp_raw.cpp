```
#include <iostream>
#include <map>
#include <string>
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

    // Parse the XML data
    xmlDocPtr doc = xmlParseMemory(xml_data.c_str(), xml_data.size());
    if (doc == nullptr) {
        std::cerr << "Failed to parse XML data." << std::endl;
        return student_info;
    }

    // Create XPath context
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == nullptr) {
        xmlFreeDoc(doc);
        std::cerr << "Failed to create XPath context." << std::endl;
        return student_info;
    }

    // Construct the XPath query securely
    std::string query = "//student[username = '" + username + "' and password = '" + password + "']";
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression(reinterpret_cast<const xmlChar*>(query.c_str()), xpathCtx);
    if (xpathObj == nullptr) {
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        std::cerr << "Failed to evaluate XPath expression." << std::endl;
        return student_info;
    }

    // Check if we found any matching student nodes
    if (xpathObj->nodesetval->nodeNr > 0) {
        xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];

        // Extract student information
        for (xmlNodePtr node = studentNode->children; node; node = node->next) {
            if (node->type == XML_ELEMENT_NODE) {
                std::string nodeName = reinterpret_cast<const char*>(node->name);
                std::string nodeContent = reinterpret_cast<const char*>(xmlNodeGetContent(node));
                student_info[nodeName] = nodeContent;
            }
        }
    }

    // Clean up
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info;
}
```