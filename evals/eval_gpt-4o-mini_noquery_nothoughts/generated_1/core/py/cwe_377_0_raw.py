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
    # Create a named temporary file that will be deleted after use
    with NamedTemporaryFile(delete=False) as temp_file:
        # Write the results to the temporary file
        temp_file.write(results.encode('utf-8'))
        # Return the name of the temporary file
        return temp_file.name

# Example usage
if __name__ == '__main__':
    filename = write_results('Sample results data.')
    print(f'Temporary file created at: {filename}')
    # Ensure to clean up the temporary file after usage
    os.remove(filename)  # Remove the temporary file to prevent resource leaks