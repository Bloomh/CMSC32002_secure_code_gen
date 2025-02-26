```
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

@param xmlData The XML data containing the student information.
@param username The username of the student to search for.
@param password The password of the student to search for.

@return A tuple (name, age, citizenship) if the student is found. Otherwise, returns empty strings.
*/
func getStudentInfo(xmlData, username, password string) (string, string, string) {
    // Validate input parameters
    if strings.TrimSpace(username) == "" || strings.TrimSpace(password) == "" {
        return "", "", ""
    }

    // Parse the XML data
    node, err := xmltree.Parse([]byte(xmlData))
    if err != nil {
        return "", "", ""
    }

    // Escape username and password to prevent XML injection
    safeUsername := strings.ReplaceAll(username, "'", "&apos;")
    safePassword := strings.ReplaceAll(password, "'", "&apos;")

    // Construct a safe XPath query to find the student
    query := fmt.Sprintf("/students/student[username='%s' and password='%s']", safeUsername, safePassword)
    result, err := goxpath.Query(node, query)
    if err != nil || len(result) == 0 {
        return "", "", ""
    }

    // Extract student information
    student := result[0]
    name := student.SelectElement("name").Content
    age := student.SelectElement("age").Content
    citizenship := student.SelectElement("citizenship").Content

    return name, age, citizenship
}
```