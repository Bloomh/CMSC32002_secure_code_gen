```
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

@param xmlData The XML data containing the student information.
@param username The username of the student to search for.
@param password The password of the student to search for.

@return A tuple (name, age, citizenship) if the student is found. Otherwise, returns empty strings.
*/
func getStudentInfo(xmlData, username, password string) (string, string, string) {
    // Parse the XML data
    root, err := xmltree.ParseString(xmlData)
    if err != nil {
        return "", "", "" // Return empty strings on parse error
    }

    // Sanitize input to prevent XPath injection
    sanitizedUsername := xmlEscape(username)
    sanitizedPassword := xmlEscape(password)

    // Construct XPath query to find the student with given username and password
    query := fmt.Sprintf("/students/student[username='%s' and password='%s']", sanitizedUsername, sanitizedPassword)

    // Execute the query
    nodes, err := goxpath.Query(root, query)
    if err != nil || len(nodes) == 0 {
        return "", "", "" // Return empty strings if no student found
    }

    // Extract student information
    studentNode := nodes[0]
    name := studentNode.SelectSingleNode("name").InnerText()
    age := studentNode.SelectSingleNode("age").InnerText()
    citizenship := studentNode.SelectSingleNode("citizenship").InnerText()

    return name, age, citizenship
}

// xmlEscape escapes special characters in the given string to prevent XPath injection
func xmlEscape(s string) string {
    return strings.ReplaceAll(strings.ReplaceAll(strings.ReplaceAll(s, "&", "&amp;"), "'", "&apos;"), "<", "&lt;")
}
```