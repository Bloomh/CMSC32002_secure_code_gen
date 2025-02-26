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
    # Validate the directory
    if not os.path.isdir(directory):
        raise ValueError('Invalid directory provided.')

    # Create the full file path
    file_path = os.path.join(directory, filename)

    # Validate the filename to prevent directory traversal
    if os.path.abspath(file_path).startswith(os.path.abspath(directory)):
        # Save the content to the file
        with open(file_path, 'w') as file:
            file.write(content)
        # Set file permissions to be accessible only by the user
        os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)  # Owner can read and write
    else:
        raise ValueError('Invalid filename provided, potential directory traversal detected.')