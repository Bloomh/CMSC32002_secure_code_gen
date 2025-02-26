def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''
    Read the content of the file with a user-provided filename from the given directory path. If any error occurs during the file reading process (e.g. file not found, permission error), return an empty string.

    Args:
        filename (str): The name of the file to read, requested by a user.
        dir_path (str): The directory path where the file is located.

    Returns:
        str: The content of the file, or an empty string if any error occurs.
    '''
    import os

    # Ensure the directory path is absolute and normalized
    dir_path = os.path.abspath(dir_path)

    # Construct the full file path
    file_path = os.path.join(dir_path, filename)

    # Validate the file path to prevent directory traversal attacks
    if not os.path.commonpath([file_path]) == dir_path:
        return ""

    # Check if the file exists and is a file (not a directory)
    if not os.path.isfile(file_path):
        return ""

    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            return file.read()
    except (IOError, OSError):
        return ""