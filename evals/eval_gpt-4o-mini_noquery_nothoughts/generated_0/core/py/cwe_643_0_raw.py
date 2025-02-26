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

        # Escape username and password to prevent XPath injection
        safe_username = etree.XPath('string(.)')(etree.XML(etree.tostring(etree.Element('username', text=username))))
        safe_password = etree.XPath('string(.)')(etree.XML(etree.tostring(etree.Element('password', text=password))))

        # Construct XPath query to find student with matching username and password
        query = f"//student[username/text()='{safe_username}' and password/text()='{safe_password}']"
        student_element = root.xpath(query)

        # If a matching student is found, extract their information
        if student_element:
            student_info = student_element[0]
            return {
                'username': student_info.findtext('username'),
                'name': student_info.findtext('name'),
                'citizenship': student_info.findtext('citizenship'),
                'age': student_info.findtext('age')
            }
        return None
    except etree.XMLSyntaxError:
        # Handle XML parsing errors
        print('Invalid XML data provided.')
        return None
    except Exception as e:
        # Log unexpected errors for debugging
        print(f'An error occurred: {e}')
        return None