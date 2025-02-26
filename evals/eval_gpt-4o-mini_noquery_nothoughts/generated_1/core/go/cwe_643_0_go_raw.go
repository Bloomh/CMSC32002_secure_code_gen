```
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
    // Parse the XML data
    xmlTree, err := xmltree.Parse([]byte(xmlData))
    if err != nil {
        return "", "", "" // return empty strings on error
    }

    // Sanitize inputs to prevent XPath injection
    safeUsername := strings.ReplaceAll(username, "'", "\'")
    safePassword := strings.ReplaceAll(password, "'", "\'")

    // Create a query to find the student with the given username and password
    query := fmt.Sprintf("//student[username='%s' and password='%s']", safeUsername, safePassword)

    // Execute the XPath query
    nodes, err := goxpath.Query(xmlTree, query)
    if err != nil || len(nodes) == 0 {
        return "", "", "" // return empty if no match found
    }

    // Extract student information
    name := nodes[0].FindElement("name").Text
    age := nodes[0].FindElement("age").Text
    citizenship := nodes[0].FindElement("citizenship").Text

    return name, age, citizenship
}
```