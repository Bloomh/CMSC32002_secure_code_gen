import os


def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''
    Read the content of the file with a user-provided filename from the given directory path. If any error occurs during the file reading process (e.g. file not found, permission error), return an empty string.

    Args:
        filename (str): The name of the file to read, requested by a user.
        dir_path (str): The directory path where the file is located.

    Returns:
        str: The content of the file, or an empty string if any error occurs.
    '''
    # Validate the filename to prevent directory traversal
    if any(part in filename for part in ['..', '/', '\']):
        return ''

    # Construct the full file path
    file_path = os.path.join(dir_path, filename)

    # Normalize and resolve the absolute paths
    normalized_dir_path = os.path.abspath(dir_path)
    normalized_file_path = os.path.abspath(file_path)

    # Ensure the file path is within the intended directory
    if not normalized_file_path.startswith(normalized_dir_path + os.sep):
        return ''

    # Check if the file exists and is a file
    if not os.path.isfile(normalized_file_path):
        return ''

    try:
        with open(normalized_file_path, 'r') as file:
            return file.read()
    except (IOError, OSError):
        return ''