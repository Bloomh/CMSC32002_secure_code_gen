from typing import Dict, Optional

from lxml import etree


def get_student_info(
    xml_data: str, username: str, password: str
) -> Optional[Dict[str, str]]:
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

    Args:
        xml_data: The XML data containing the student information.
        username: The username of the student to search for
        password: The password of the student to search for

    Returns:
        Optional[Dict[str, str]]: A dictionary containing the student information if the student is found with the given username and password. Otherwise, return None.
    """
    try:
        # Parse the XML data
        root = etree.fromstring(xml_data)

        # Use parameterized XPath to prevent XPath injection
        xpath_query = ".//student[username = $username and password = $password]"
        student_element = root.xpath(xpath_query, username=username, password=password)

        # If a matching student is found, extract their information
        if student_element:
            student = student_element[0]
            return {
                'username': student.findtext('username'),
                'name': student.findtext('name'),
                'citizenship': student.findtext('citizenship'),
                'age': student.findtext('age'),
            }
        return None
    except etree.XMLSyntaxError:
        print("Error parsing XML data.")
        return None
    except Exception as e:
        print(f"An error occurred: {e}")
        return None