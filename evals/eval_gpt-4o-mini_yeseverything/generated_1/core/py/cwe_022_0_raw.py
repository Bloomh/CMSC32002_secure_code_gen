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
        # Normalize the directory path
        dir_path = os.path.abspath(dir_path)
        # Sanitize filename to prevent path traversal
        if '..' in filename or os.path.isabs(filename):
            return ''  # Prevent directory traversal
        # Construct the full path of the file
        file_path = os.path.join(dir_path, filename)
        # Ensure the file path is within the specified directory
        if not os.path.commonpath([file_path, dir_path]) == dir_path:
            return ''  # Prevent directory traversal
        # Read the file content
        with open(file_path, 'r') as file:
            return file.read()
    except (FileNotFoundError, PermissionError, OSError):
        return ''