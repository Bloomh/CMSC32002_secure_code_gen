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
    try:
        # Construct the full file path
        full_path = os.path.join(dir_path, filename)
        # Normalize the path to prevent directory traversal
        normalized_path = os.path.normpath(full_path)
        # Ensure the normalized path starts with the directory path
        if not normalized_path.startswith(os.path.abspath(dir_path)):
            return ''  # Invalid path, return empty string

        # Read the file content
        with open(normalized_path, 'r') as file:
            return file.read()
    except (OSError, IOError):
        return ''  # Return empty string on any file access error