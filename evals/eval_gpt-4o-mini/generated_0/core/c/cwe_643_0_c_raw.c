#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

// Function to free the allocated memory for StudentInfo
void free_student_info(StudentInfo* student) {
    if (student != NULL) {
        free(student->name);
        free(student->age);
        free(student->citizenship);
        free(student);
    }
}

StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    if (xml_data == NULL || username == NULL || password == NULL) {
        return NULL;
    }

    // Initialize the XML parser
    xmlDocPtr doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL;
    }

    // Create XPath context
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }

    // Construct the XPath query safely
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query),
        "/students/student[username='%s' and password='%s']",
        username, password);

    // Evaluate the XPath expression
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Extract student information
    StudentInfo* student = malloc(sizeof(StudentInfo));
    if (student == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];

    // Get content safely
    student->name = (char*)xmlNodeGetContent(xmlGetFirstChild(studentNode));
    student->age = (char*)xmlXPathEvalExpression((const xmlChar*)"age", xpathCtx)->nodesetval->nodeTab[0] ? (char*)xmlNodeGetContent(xmlXPathEvalExpression((const xmlChar*)"age", xpathCtx)->nodesetval->nodeTab[0]) : NULL;
    student->citizenship = (char*)xmlXPathEvalExpression((const xmlChar*)"citizenship", xpathCtx)->nodesetval->nodeTab[0] ? (char*)xmlNodeGetContent(xmlXPathEvalExpression((const xmlChar*)"citizenship", xpathCtx)->nodesetval->nodeTab[0]) : NULL;

    // Clean up
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student;
}