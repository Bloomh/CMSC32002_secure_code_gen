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

    We can construct a XPath query and use it to search.

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

        # Escape username and password to prevent XML injection
        escaped_username = username.replace("'", "&apos;").replace('"', '&quot;')
        escaped_password = password.replace("'", "&apos;").replace('"', '&quot;')

        # Construct XPath query to find the student matching username and password
        xpath_query = f"//student[username = '{escaped_username}' and password = '{escaped_password}']"
        student_element = root.xpath(xpath_query)

        # If a matching student is found, extract the information
        if student_element:
            student = student_element[0]
            return {
                'username': student.findtext('username'),
                'name': student.findtext('name'),
                'citizenship': student.findtext('citizenship'),
                'age': student.findtext('age')
            }
        return None
    except etree.XMLSyntaxError:
        # Handle XML parsing errors
        print('Invalid XML data')
        return None
    except Exception as e:
        # Handle other exceptions
        print(f'An error occurred: {e}')
        return None