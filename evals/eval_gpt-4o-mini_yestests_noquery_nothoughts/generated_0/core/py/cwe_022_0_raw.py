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

    # Normalize and validate directory path
    dir_path = os.path.abspath(dir_path)
    if not os.path.exists(dir_path) or not os.path.isdir(dir_path):
        return ''

    # Construct the full file path
    file_path = os.path.join(dir_path, filename)

    # Prevent directory traversal attacks
    if not os.path.commonpath([file_path]) == os.path.commonpath([dir_path]):
        return ''

    # Try to read the file content
    try:
        with open(file_path, 'r') as file:
            return file.read()
    except (FileNotFoundError, PermissionError):
        return ''