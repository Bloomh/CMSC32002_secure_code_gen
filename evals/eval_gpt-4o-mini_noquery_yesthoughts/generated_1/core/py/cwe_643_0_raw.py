from typing import Dict

from lxml import etree


def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """
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

    We can construct an XPath query and use it to search.

    Args:
        xml_data: The XML data containing the student information.
        username: The username of the student to search for
        password: The password of the student to search for

    Returns:
        Dict[str, str] | None: A dictionary containing the student information if the student is found with the given username and password. Otherwise, return None.
    """
    try:
        # Parse the XML data
        root = etree.fromstring(xml_data)

        # Use parameterized XPath to prevent injection
        student = root.xpath('//student[username = $username and password = $password]', username=username, password=password)

        if student:
            # Extract student information if found
            return {
                'username': student[0].findtext('username'),
                'name': student[0].findtext('name'),
                'citizenship': student[0].findtext('citizenship'),
                'age': student[0].findtext('age'),
            }

    except (etree.XMLSyntaxError, ValueError):
        return None  # Handle XML parsing errors

    return None  # Return None if no matching student is found