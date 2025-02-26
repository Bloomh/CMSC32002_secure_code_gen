package main

import (
    "fmt"
    "github.com/ChrisTrenkamp/goxpath"
    "github.com/ChrisTrenkamp/goxpath/tree"
    "github.com/ChrisTrenkamp/goxpath/tree/xmltree"
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
"github.com/ChrisTrenkamp/goxpath/tree"
"github.com/ChrisTrenkamp/goxpath/tree/xmltree"

We can construct a XPath query and then execute the query to search for the student information.

@param xmlData The XML data containing the student information.
@param username The username of the student to search for.
@param password The password of the student to search for.

@return A tuple (name, age, citizenship) if the student is found. Otherwise, returns empty strings.
*/
func getStudentInfo(xmlData, username, password string) (string, string, string) {
    // Sanitize inputs to prevent XML injection
    username = sanitizeInput(username)
    password = sanitizeInput(password)

    // Parse the XML data
    root, err := xmltree.Parse(strings.NewReader(xmlData))
    if err != nil {
        return "", "", "" // Return empty strings on error
    }

    // Create an XPath expression to find the student with the specified username and password
    xpathExpr := fmt.Sprintf("/students/student[username='%s' and password='%s']", username, password)

    // Execute the XPath query
    nodes, err := goxpath.Query(root, xpathExpr)
    if err != nil || len(nodes) == 0 {
        return "", "", "" // Return empty strings if no student is found or on error
    }

    // Extract the student information
    studentNode := nodes[0]
    name := studentNode.SelectElement("name").Content
    age := studentNode.SelectElement("age").Content
    citizenship := studentNode.SelectElement("citizenship").Content

    return name, age, citizenship
}

// sanitizeInput sanitizes the input to prevent XML injection attacks
func sanitizeInput(input string) string {
    // A simple sanitization function to escape problematic characters
    return strings.ReplaceAll(input, "'", "&apos;") // Escape single quotes
}

func main() {
    xmlData := `<students>
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
</students>`
    name, age, citizenship := getStudentInfo(xmlData, "john_doe", "jdpassword")
    fmt.Printf("Name: %s, Age: %s, Citizenship: %s\n", name, age, citizenship)
}