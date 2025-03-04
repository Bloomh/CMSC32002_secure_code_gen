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
    try:
        with NamedTemporaryFile(delete=False, mode='w+', suffix='.txt') as temp_file:
            temp_file.write(results)
            temp_file.flush()  # Ensure the data is written to disk
            file_name = temp_file.name
        return file_name
    except Exception as e:
        raise IOError(f"An error occurred while writing to the temporary file: {e}")