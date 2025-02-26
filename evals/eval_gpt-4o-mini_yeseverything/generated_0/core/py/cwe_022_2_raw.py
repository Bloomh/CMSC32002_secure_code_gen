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
        # Ensure destination path is absolute and exists
        dest_path = os.path.abspath(dest_path)
        if not os.path.exists(dest_path) or not os.path.isdir(dest_path):
            return False

        with tarfile.open(tar_path, 'r:*') as tar:
            for member in tar.getmembers():
                # Prevent path traversal by checking if the member name is valid
                member_name = member.name
                # Normalize the member path to prevent directory traversal
                member_path = os.path.normpath(os.path.join(dest_path, member_name))
                if not member_path.startswith(dest_path) or '..' in member_name:
                    return False

                # Extract the member
                tar.extract(member, path=dest_path)
        return True
    except (FileNotFoundError, tarfile.TarError, PermissionError):
        return False