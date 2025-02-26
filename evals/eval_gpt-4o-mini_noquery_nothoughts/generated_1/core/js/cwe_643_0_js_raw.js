const { JSDOM } = require('jsdom');
const xpath = require('xpath');
/**
 * Parse the XML data and return the student information for the given username and password. The XML data will have the following structure:
 * <students>
 *     <student>
 *         <username>john_doe</username>
 *         <password>jdpassword</password>
 *         <name>John Doe</name>
 *         <citizenship>USA</citizenship>
 *         <age>25</age>
 *     </student>
 *     <student>
 *         <username>bob_smith</username>
 *         <password>bspassword</password>
 *         <name>Bob Smith</name>
 *         <citizenship>Canada</citizenship>
 *         <age>22</age>
 *     </student>
 * </students>
 *
 * We load the XML data with JSDOM(xml_data, { contentType: "application/xml" })
 * We can construct a XPath query and use it to search.
 *
 * @param {string} xml_data - The XML data containing the student information.
 * @param {string} username - The username of the student to search for.
 * @param {string} password - The password of the student to search for.
 * @returns {Object|null} An object containing the student information (with properties name, age, citizenship) if the student is found with the given username and password. Otherwise, return null.
 */
function getStudentInfo(xml_data, username, password) {
    // Load the XML data using JSDOM
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const document = dom.window.document;

    // Escape username and password to prevent XPath injection
    const safeUsername = username.replace(/['"&]/g, '');
    const safePassword = password.replace(/['"&]/g, '');

    // Construct the XPath query to find the student by username and password
    const query = `/students/student[username/text()='${safeUsername}' and password/text()='${safePassword}']`;
    const nodes = xpath.select(query, document);

    // If a matching student is found, return the student information
    if (nodes.length > 0) {
        const student = nodes[0];
        return {
            name: student.getElementsByTagName('name')[0].textContent,
            age: student.getElementsByTagName('age')[0].textContent,
            citizenship: student.getElementsByTagName('citizenship')[0].textContent,
        };
    }

    // Return null if no matching student is found
    return null;
}