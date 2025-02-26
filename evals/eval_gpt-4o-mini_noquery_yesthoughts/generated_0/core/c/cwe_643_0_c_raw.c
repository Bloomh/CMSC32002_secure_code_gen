#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

// Helper function to escape special characters in XPath
void escape_xpath(const char* input, char* output, size_t output_size) {
    size_t j = 0;
    for (size_t i = 0; input[i] != '\0' && j < output_size - 1; i++) {
        if (input[i] == '"' || input[i] == '\') {
            if (j < output_size - 2) {
                output[j++] = '\';
            }
        }
        output[j++] = input[i];
    }
    output[j] = '\0';
}

StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL;
    }
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }

    // Sanitize username and password
    char sanitized_username[256];
    char sanitized_password[256];
    escape_xpath(username, sanitized_username, sizeof(sanitized_username));
    escape_xpath(password, sanitized_password, sizeof(sanitized_password));

    // Construct the XPath query to find the student
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query), "/students/student[username='%s' and password='%s']", sanitized_username, sanitized_password);

    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL) {
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    StudentInfo* student = NULL;
    if (xpathObj->nodesetval->nodeNr > 0) {
        student = malloc(sizeof(StudentInfo));
        if (student == NULL) {
            xmlXPathFreeObject(xpathObj);
            xmlXPathFreeContext(xpathCtx);
            xmlFreeDoc(doc);
            return NULL;
        }

        // Retrieve student information
        xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
        student->name = (char*)xmlNodeGetContent(xmlFindNode(studentNode, (const xmlChar*)"name"));
        student->age = (char*)xmlNodeGetContent(xmlFindNode(studentNode, (const xmlChar*)"age"));
        student->citizenship = (char*)xmlNodeGetContent(xmlFindNode(studentNode, (const xmlChar*)"citizenship"));
    }

    // Free resources
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student;
}

// Helper function to find a child node by name
xmlNodePtr xmlFindNode(xmlNodePtr parent, const xmlChar* name) {
    for (xmlNodePtr cur = parent->children; cur; cur = cur->next) {
        if (cur->type == XML_ELEMENT_NODE && xmlStrcmp(cur->name, name) == 0) {
            return cur;
        }
    }
    return NULL;
}