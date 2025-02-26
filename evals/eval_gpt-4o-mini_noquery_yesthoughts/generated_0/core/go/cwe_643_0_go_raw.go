```go
import (
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
    // Sanitize input to prevent injection attacks
    username = strings.TrimSpace(username)
    password = strings.TrimSpace(password)

    // Parse the XML data
    doc, err := xmltree.Parse([]byte(xmlData))
    if err != nil {
        return "", "", "" // Return empty strings on error
    }

    // Escape username and password for XPath to prevent injection
    escapedUsername := goxpath.Escape(username)
    escapedPassword := goxpath.Escape(password)

    // Construct XPath query safely
    xpathQuery := "/students/student[username = '" + escapedUsername + "' and password = '" + escapedPassword + "']"

    // Execute XPath query
    selectedNodes, err := goxpath.Query(doc, xpathQuery)
    if err != nil || len(selectedNodes) == 0 {
        return "", "", "" // Return empty strings if no student found or error occurred
    }

    // Extract student information
    studentNode := selectedNodes[0]
    name := studentNode.Child("name").Text()
    age := studentNode.Child("age").Text()
    citizenship := studentNode.Child("citizenship").Text()

    return name, age, citizenship
}
```