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

StudentInfo* create_student_info(const char* name, const char* age, const char* citizenship) {
    StudentInfo* info = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (info) {
        info->name = strdup(name);
        info->age = strdup(age);
        info->citizenship = strdup(citizenship);
    }
    return info;
}

void free_student_info(StudentInfo* info) {
    if (info) {
        free(info->name);
        free(info->age);
        free(info->citizenship);
        free(info);
    }
}

void escape_xpath_string(const char* input, char* output, size_t output_size) {
    size_t i, j = 0;
    for (i = 0; input[i] != '\0' && j < output_size - 1; i++) {
        switch (input[i]) {
            case '"':
            case '\':
            case '"':
                if (j < output_size - 2) {
                    output[j++] = '\';
                }
                break;
            default:
                break;
        }
        output[j++] = input[i];
    }
    output[j] = '\0';
}

StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    // Initialize the XML parser
    xmlDocPtr doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse XML data\n");
        return NULL;
    }

    // Create an XPath context
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        fprintf(stderr, "Failed to create XPath context\n");
        xmlFreeDoc(doc);
        return NULL;
    }

    // Escape user input for XPath query
    char escaped_username[256];
    char escaped_password[256];
    escape_xpath_string(username, escaped_username, sizeof(escaped_username));
    escape_xpath_string(password, escaped_password, sizeof(escaped_password));

    // Construct the XPath query to find the student with the given username and password
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query), "/students/student[username='%s' and password='%s']", escaped_username, escaped_password);

    // Evaluate the XPath expression
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Extract the student information
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    StudentInfo* studentInfo = create_student_info(
        (const char*)xmlNodeGetContent(xmlXPathNodeEval(studentNode, (const xmlChar*)"name", xpathCtx)),
        (const char*)xmlNodeGetContent(xmlXPathNodeEval(studentNode, (const xmlChar*)"age", xpathCtx)),
        (const char*)xmlNodeGetContent(xmlXPathNodeEval(studentNode, (const xmlChar*)"citizenship", xpathCtx))
    );

    // Clean up
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return studentInfo;
}