package main

import (
    "github.com/ChrisTrenkamp/goxpath"
    "github.com/ChrisTrenkamp/goxpath/tree/xmltree"
    "fmt"
    "strings"
)

/*
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

Use these libs:
"github.com/ChrisTrenkamp/goxpath"
"github.com/ChrisTrenkamp/goxpath/tree/xmltree"

@param xmlData The XML data containing the student information.
@param username The username of the student to search for.
@param password The password of the student to search for.

@return A tuple (name, age, citizenship) if the student is found. Otherwise, returns empty strings.
*/
func getStudentInfo(xmlData, username, password string) (string, string, string) {
    // Normalize inputs to prevent XML injection attacks
    username = strings.TrimSpace(username)
    password = strings.TrimSpace(password)

    // Parse the XML data
    tree, err := xmltree.ParseString(xmlData)
    if err != nil {
        return "", "", ""
    }

    // Create a safe XPath expression to find the student
    xpathExpr := fmt.Sprintf("//student[username='%s' and password='%s']", escapeXPath(username), escapeXPath(password))
    xpath, err := goxpath.Compile(xpathExpr)
    if err != nil {
        return "", "", ""
    }

    // Execute the XPath query
    nodes, err := xpath.Select(tree)
    if err != nil || len(nodes) == 0 {
        return "", "", ""
    }

    // Extract the student information
    studentNode := nodes[0]
    name := studentNode.SelectSingleNode("name").Content
    age := studentNode.SelectSingleNode("age").Content
    citizenship := studentNode.SelectSingleNode("citizenship").Content

    return name, age, citizenship
}

// escapeXPath safely escapes user input for XPath queries
func escapeXPath(input string) string {
    return strings.ReplaceAll(input, "'", "\'")
}