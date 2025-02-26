import os
import tarfile


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
        # Ensure the destination path is a safe directory
        if not os.path.isdir(dest_path):
            return False

        with tarfile.open(tar_path, 'r:*') as tar:
            # Ensure the members are extracted safely to prevent directory traversal attacks
            for member in tar.getmembers():
                # Normalize the member's path
                member_path = os.path.normpath(os.path.join(dest_path, member.name))
                # Prevent extracting files outside of the destination directory
                if not member_path.startswith(os.path.abspath(dest_path)):
                    return False
                # Check for potential extraction of special files
                if member.name.startswith('/'):
                    return False
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError):
        return False