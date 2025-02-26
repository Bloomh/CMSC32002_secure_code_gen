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
        root = etree.fromstring(xml_data)
        # Use parameterized XPath to find the student with the given username and password
        student = root.xpath("//student[username = $username and password = $password]", username=username, password=password)
        if student:
            # Extract information from the found student
            student_info = student[0]
            return {
                'name': student_info.findtext('name'),
                'citizenship': student_info.findtext('citizenship'),
                'age': student_info.findtext('age'),
            }
    except etree.XMLSyntaxError:
        print('Error: Invalid XML data.')
    except Exception as e:
        print(f'An error occurred: {e}')  # Log other exceptions
    return None