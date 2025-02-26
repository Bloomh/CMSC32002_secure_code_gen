from tempfile import NamedTemporaryFile
import os


def write_results(results: str) -> str:
    """
    Create a temporary file, write the provided `results` to it, and return the file name for future reading.

    Args:
        results (str): The string content to write to the temporary file.

    Returns:
        str: The file name of the temporary file created.
    """
    # Use NamedTemporaryFile to create a temporary file securely
    with NamedTemporaryFile(delete=False, mode='w+t') as temp_file:
        # Write the results to the temporary file
        temp_file.write(results)
        # Get the name of the temporary file
        temp_file_name = temp_file.name
    # Return the name of the temporary file for future reading
    return temp_file_name
