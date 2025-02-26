```go
package main

import (
	"encoding/xml"
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

@param xmlData The XML data containing the student information.
@param username The username of the student to search for.
@param password The password of the student to search for.

@return A tuple (name, age, citizenship) if the student is found. Otherwise, returns empty strings.
*/
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Parse the XML data
	var students struct {
		Students []struct {
			Username    string `xml:"username"`
			Password    string `xml:"password"`
			Name        string `xml:"name"`
			Citizenship string `xml:"citizenship"`
			Age         string `xml:"age"`
		} `xml:"student"`
	} `xml:"students"`

	if err := xml.Unmarshal([]byte(xmlData), &students); err != nil {
		return "", "", ""
	}

	// Construct a secure XPath query to find matching student
	xpathQuery := fmt.Sprintf("/students/student[username='%%s' and password='%%s']", strings.ReplaceAll(username, "'", "''"), strings.ReplaceAll(password, "'", "''"))

	// Execute XPath query
	doc := xmltree.NewDocument([]byte(xmlData))
	result, err := goxpath.Query(doc, xpathQuery)
	if err != nil || len(result) == 0 {
		return "", "", ""
	}

	// Extract information from the result
	name := result[0].FindElement("name").Text
	age := result[0].FindElement("age").Text
	citizenship := result[0].FindElement("citizenship").Text

	return name, age, citizenship
}
```