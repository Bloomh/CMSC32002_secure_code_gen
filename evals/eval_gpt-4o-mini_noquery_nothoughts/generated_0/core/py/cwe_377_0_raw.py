from tempfile import NamedTemporaryFile


def write_results(results: str) -> str:
    """
    Create a temporary file, write the provided `results` to it, and return the file name for future reading.

    Args:
        results (str): The string content to write to the temporary file.

    Returns:
        str: The file name of the temporary file created.
    """
    # Create a named temporary file that is automatically deleted when closed
    with NamedTemporaryFile(delete=False, mode='w+', suffix='.txt', dir=None) as temp_file:
        # Write results to the temporary file
        temp_file.write(results)
        # Ensure the file is flushed to disk
        temp_file.flush()
        # Return the name of the temporary file
        return temp_file.name

# Note: The returned file name can be used while the file is open, but should be handled securely.