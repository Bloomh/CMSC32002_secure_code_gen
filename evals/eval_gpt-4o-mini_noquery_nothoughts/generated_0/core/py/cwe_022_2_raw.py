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
            # Iterate through the members of the tar file
            for member in tar.getmembers():
                # Prevent path traversal by ensuring the member's path is safe
                member_path = os.path.join(dest_path, member.name)
                # Check for attempts to escape the destination directory
                if not os.path.commonprefix([os.path.abspath(member_path), dest_path]) == dest_path:
                    return False
            # Extract the contents of the tar file
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError):
        return False