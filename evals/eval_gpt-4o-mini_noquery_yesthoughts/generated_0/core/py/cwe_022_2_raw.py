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
        # Ensure the destination path is an absolute path
        dest_path = os.path.abspath(dest_path)

        # Open the tar file for reading
        with tarfile.open(tar_path, 'r') as tar:
            for member in tar.getmembers():
                # Check for path traversal vulnerabilities
                member_path = os.path.join(dest_path, member.name)
                # Ensure that the member path is valid and does not escape the destination directory
                if os.path.isabs(member.name) or '..' in member.name:
                    return False  # Prevent path traversal
                if not os.path.commonprefix([member_path, dest_path]) == dest_path:
                    return False  # Prevent path traversal

                # Extract the member
                tar.extract(member, path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError):
        return False