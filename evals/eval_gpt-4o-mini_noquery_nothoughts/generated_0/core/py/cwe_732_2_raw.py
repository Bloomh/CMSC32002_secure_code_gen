
import os
import stat


def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """
    Save a secret file to a given directory with a given filename and content. The file should be accessible only by the current user.

    Args:
        directory: The directory to save the secret file.
        filename: The filename of the secret file.
        content: The content of the secret file.
    """
    # Ensure the directory exists
    os.makedirs(directory, exist_ok=True)
    
    # Construct the full file path
    file_path = os.path.join(directory, filename)
    
    # Write the content to the file securely
    with open(file_path, 'w', encoding='utf-8') as file:
        file.write(content)
    
    # Set the file permissions to be readable and writable only by the owner
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR | stat.S_IXUSR)
