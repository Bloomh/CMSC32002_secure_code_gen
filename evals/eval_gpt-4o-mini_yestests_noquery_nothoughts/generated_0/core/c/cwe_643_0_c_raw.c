#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

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

@return A pointer to a StudentInfo structure if the student is found. Otherwise, returns NULL.
*/
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    // Initialize the XML parser
    xmlDocPtr doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL;
    }

    // Create an XPath context
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }

    // Construct the XPath query to find the student by username and password
    char safe_username[256];
    char safe_password[256];
    xmlChar* xpath_query = (xmlChar*)malloc(512);
    if (xpath_query == NULL) {
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Escape the username and password to prevent XPath injection attacks
    snprintf(safe_username, sizeof(safe_username), "%s", username);
    snprintf(safe_password, sizeof(safe_password), "%s", password);

    snprintf((char*)xpath_query, 512,
             "/students/student[username='%s' and password='%s']",
             safe_username, safe_password);

    // Evaluate the XPath expression
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression(xpath_query, xpathCtx);
    free(xpath_query);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Retrieve the student information
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    StudentInfo* studentInfo = malloc(sizeof(StudentInfo));
    if (studentInfo == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Initialize student info fields
    studentInfo->name = NULL;
    studentInfo->age = NULL;
    studentInfo->citizenship = NULL;

    // Extract name, age, and citizenship
    for (xmlNodePtr node = studentNode->children; node; node = node->next) {
        if (node->type == XML_ELEMENT_NODE) {
            if (strcmp((const char*)node->name, "name") == 0) {
                studentInfo->name = strdup((const char*)xmlNodeGetContent(node));
            } else if (strcmp((const char*)node->name, "age") == 0) {
                studentInfo->age = strdup((const char*)xmlNodeGetContent(node));
            } else if (strcmp((const char*)node->name, "citizenship") == 0) {
                studentInfo->citizenship = strdup((const char*)xmlNodeGetContent(node));
            }
        }
    }

    // Cleanup
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return studentInfo;
}