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
    # Create a named temporary file that is securely created and automatically deleted
    with NamedTemporaryFile(delete=False, mode='w+t') as temp_file:
        # Write the results to the temporary file
        temp_file.write(results)
        # Flush the file to ensure all data is written
        temp_file.flush()
        # Return the name of the temporary file
        return temp_file.name

    # Note: The file will not be deleted automatically here,
    # as we want to return the name for future reading.