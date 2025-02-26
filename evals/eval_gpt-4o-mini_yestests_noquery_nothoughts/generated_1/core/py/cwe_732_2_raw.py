def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """
    Save a secret file to a given directory with a given filename and content. The file should be accessible only by the current user.

    Args:
        directory: The directory to save the secret file.
        filename: The filename of the secret file.
        content: The content of the secret file.
    """
    import os
    import stat
    
    # Ensure the directory exists
    os.makedirs(directory, exist_ok=True)
    
    # Construct the full file path
    file_path = os.path.join(directory, filename)
    
    # Write content to the file
    with open(file_path, 'w') as file:
        file.write(content)
    
    # Set file permissions to allow only the current user to read and write
    uid = os.getuid()
    os.chown(file_path, uid, uid)
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)
