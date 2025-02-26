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
    import pathlib

    # Normalize and validate the directory path
    dir_path = os.path.abspath(dir_path)
    # Create a path object for the file
    file_path = pathlib.Path(dir_path) / filename

    # Ensure the file is within the specified directory
    if not file_path.is_file() or not file_path.resolve().parent == pathlib.Path(dir_path):
        return ''

    try:
        with open(file_path, 'r') as file:
            return file.read()
    except (FileNotFoundError, PermissionError, IsADirectoryError):
        return ''