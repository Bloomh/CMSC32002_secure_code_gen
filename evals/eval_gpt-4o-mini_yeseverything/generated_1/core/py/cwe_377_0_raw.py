from tempfile import NamedTemporaryFile


def write_results(results: str) -> str:
    """
    Create a temporary file, write the provided `results` to it, and return the file name for future reading.

    Args:
        results (str): The string content to write to the temporary file.

    Returns:
        str: The file name of the temporary file created.
    """
    # Create a temporary file that is deleted after it is closed
    with NamedTemporaryFile(delete=False, mode='w+', suffix='.txt') as temp_file:
        # Write the results to the temporary file
        temp_file.write(results)
        # Flush the file to ensure contents are written
        temp_file.flush()
        # Return the name of the temporary file
        return temp_file.name