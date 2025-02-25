from tempfile import NamedTemporaryFile


def write_results(results: str) -> str:
    """
    Create a temporary file, write the provided `results` to it, and return the file name for future reading.

    Args:
        results (str): The string content to write to the temporary file.

    Returns:
        str: The file name of the temporary file created.
    """
    try:
        with NamedTemporaryFile(delete=True, mode='w+', suffix='.txt', prefix='results_', dir=None) as temp_file:
            temp_file.write(results)
            temp_file.flush()  # Ensure data is written to disk
            return temp_file.name  # Return the name of the temporary file
    except IOError as io_error:
        raise RuntimeError(f"IO error occurred while writing to temporary file: {io_error}")
    except Exception as e:
        raise RuntimeError(f"An unexpected error occurred: {e}")