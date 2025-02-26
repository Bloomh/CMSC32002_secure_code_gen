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
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    StudentInfo* studentInfo = NULL;

    // Parse the XML data
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL; // Parsing error
    }

    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL; // Context creation error
    }

    // Construct XPath query with sanitized input to prevent XPath injection
    char xpathQuery[512];
    xmlChar* safe_username = xmlEncodeEntitiesReentrant(doc, (const xmlChar*)username);
    xmlChar* safe_password = xmlEncodeEntitiesReentrant(doc, (const xmlChar*)password);
    snprintf(xpathQuery, sizeof(xpathQuery), "/students/student[username='%s' and password='%s']", safe_username, safe_password);
    xmlFree(safe_username);
    xmlFree(safe_password);

    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpathQuery, xpathCtx);
    if (xpathObj == NULL || !xpathObj->nodesetval || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // No student found or evaluation error
    }

    // Allocate memory for StudentInfo
    studentInfo = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (studentInfo == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // Memory allocation error
    }

    // Initialize the fields to NULL
    studentInfo->name = NULL;
    studentInfo->age = NULL;
    studentInfo->citizenship = NULL;

    // Extract information
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    for (xmlNodePtr currentNode = studentNode->children; currentNode; currentNode = currentNode->next) {
        if (currentNode->type == XML_ELEMENT_NODE) {
            if (strcmp((const char*)currentNode->name, "name") == 0) {
                studentInfo->name = (char*)xmlNodeGetContent(currentNode);
            } else if (strcmp((const char*)currentNode->name, "age") == 0) {
                studentInfo->age = (char*)xmlNodeGetContent(currentNode);
            } else if (strcmp((const char*)currentNode->name, "citizenship") == 0) {
                studentInfo->citizenship = (char*)xmlNodeGetContent(currentNode);
            }
        }
    }

    // Cleanup
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return studentInfo;
}