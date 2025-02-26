import tarfile
import os


def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''
    Extract the content of the tar file to the given destination path.
    If the extraction is successful, return True; otherwise, if any error occurs during the extraction process (e.g. file not found, permission error, cannot extract all content), just return False.

    Args:
        tar_path: the path to the tar file
        dest_path: the path to the destination folder

    Returns:
        True if the extraction is successful; otherwise, False
    '''
    try:
        # Ensure the destination path is an absolute path
        dest_path = os.path.abspath(dest_path)

        # Open the tar file
        with tarfile.open(tar_path, 'r:*') as tar:
            # Iterate over each member in the tar file
            for member in tar.getmembers():
                # Prevent directory traversal attacks by checking the member's name
                if os.path.isabs(member.name) or '..' in member.name:
                    print(f'Invalid member found: {member.name}')  # Log the invalid member
                    return False
            # Extract all members to the destination path
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError) as e:
        print(f'Error during extraction: {e}')  # Log the error
        return False