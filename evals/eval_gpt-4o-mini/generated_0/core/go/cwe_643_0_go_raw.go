package main

import (
    "github.com/ChrisTrenkamp/goxpath"
    "github.com/ChrisTrenkamp/goxpath/tree"
    "github.com/ChrisTrenkamp/goxpath/tree/xmltree"
    "encoding/xml"
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
"github.com/ChrisTrenkamp/goxpath/tree"
"github.com/ChrisTrenkamp/goxpath/tree/xmltree"

We can construct a XPath query and then execute the query to search for the student information.

@param xmlData The XML data containing the student information.
@param username The username of the student to search for.
@param password The password of the student to search for.

@return A tuple (name, age, citizenship) if the student is found. Otherwise, returns empty strings.
*/
func getStudentInfo(xmlData, username, password string) (string, string, string) {
    // Validate inputs to prevent XML injection attacks
    if strings.TrimSpace(username) == "" || strings.TrimSpace(password) == "" {
        return "", "", ""
    }

    // Parse the XML data
    var students struct {
        Students []struct {
            Username   string `xml:"username"`
            Password   string `xml:"password"`
            Name       string `xml:"name"`
            Citizenship string `xml:"citizenship"`
            Age        string `xml:"age"`
        } `xml:"student"`
    }

    err := xml.Unmarshal([]byte(xmlData), &students)
    if err != nil {
        return "", "", "" // Return empty strings on error
    }

    // Search for the student
    for _, student := range students.Students {
        if student.Username == username && student.Password == password {
            return student.Name, student.Age, student.Citizenship
        }
    }

    // Return empty strings if student not found
    return "", "", ""
}