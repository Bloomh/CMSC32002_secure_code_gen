#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse XML\n");
        return NULL;
    }

    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        fprintf(stderr, "Failed to create XPath context\n");
        return NULL;
    }

    // Construct the XPath query safely
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query), "/students/student[username='%s' and password='%s']", username, password);

    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL) {
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        fprintf(stderr, "Failed to evaluate XPath expression\n");
        return NULL;
    }

    StudentInfo* student_info = NULL;
    if (xpathObj->nodesetval->nodeNr > 0) {
        xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];

        char* name = (char*)xmlNodeGetContent(xmlGetChild(studentNode, 2)); // name node
        char* citizenship = (char*)xmlNodeGetContent(xmlGetChild(studentNode, 3)); // citizenship node
        char* age = (char*)xmlNodeGetContent(xmlGetChild(studentNode, 4)); // age node

        student_info = create_student_info(name, age, citizenship);

        xmlFree(name);
        xmlFree(citizenship);
        xmlFree(age);
    }

    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info;
}