#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    // Validate inputs
    if (xml_data == NULL || username == NULL || password == NULL) {
        return NULL;
    }

    // Initialize libxml2
    xmlDocPtr doc = xmlReadMemory(xml_data, strlen(xml_data), NULL, NULL, 0);
    if (doc == NULL) {
        return NULL;
    }

    // Create XPath context
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }

    // Construct XPath query safely
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query), "/students/student[username='%s' and password='%s']", username, password);

    // Evaluate the XPath expression
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL) {
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Check if student was found
    if (xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Extract student information
    StudentInfo* studentInfo = malloc(sizeof(StudentInfo));
    if (studentInfo == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    studentInfo->name = studentInfo->age = studentInfo->citizenship = NULL;

    for (xmlNodePtr node = studentNode->children; node; node = node->next) {
        if (node->type == XML_ELEMENT_NODE) {
            if (xmlStrcmp(node->name, (const xmlChar *)"name") == 0) {
                studentInfo->name = (char*)xmlNodeGetContent(node);
            } else if (xmlStrcmp(node->name, (const xmlChar *)"age") == 0) {
                studentInfo->age = (char*)xmlNodeGetContent(node);
            } else if (xmlStrcmp(node->name, (const xmlChar *)"citizenship") == 0) {
                studentInfo->citizenship = (char*)xmlNodeGetContent(node);
            }
        }
    }

    // Clean up
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return studentInfo;
}

// Function to free the allocated StudentInfo structure
void free_student_info(StudentInfo* studentInfo) {
    if (studentInfo) {
        free(studentInfo->name);
        free(studentInfo->age);
        free(studentInfo->citizenship);
        free(studentInfo);
    }
}