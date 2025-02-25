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
    // Validate input types to ensure they are strings
    if (typeof username !== 'string' || typeof password !== 'string') {
        throw new Error('Invalid input types. Both username and password must be strings.');
    }

    // Load the XML data
    let dom;
    try {
        dom = new JSDOM(xml_data, { contentType: "application/xml" });
    } catch (error) {
        throw new Error('Error parsing XML data: ' + error.message);
    }
    const doc = dom.window.document;

    // Sanitize inputs to prevent XPath injection
    const sanitizedUsername = username.replace(/["'&]/g, '');
    const sanitizedPassword = password.replace(/["'&]/g, '');

    // Construct XPath query to find the student with the sanitized username and password
    const query = `//student[username = \