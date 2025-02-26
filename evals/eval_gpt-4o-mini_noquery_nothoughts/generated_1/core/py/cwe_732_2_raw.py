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
    
    # Define the full path for the file
    file_path = os.path.join(directory, filename)
    
    # Write the content to the file
    with open(file_path, 'w') as secret_file:
        secret_file.write(content)
    
    # Set the file permissions to be accessible only by the owner
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)
