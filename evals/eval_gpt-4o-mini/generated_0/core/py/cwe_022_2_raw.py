
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
        # Check if the tar file exists
        if not os.path.isfile(tar_path):
            return False

        # Ensure the destination path is an absolute path
        dest_path = os.path.abspath(dest_path)

        # Create the destination directory if it does not exist
        os.makedirs(dest_path, exist_ok=True)

        with tarfile.open(tar_path, 'r:*') as tar:
            for member in tar.getmembers():
                # Prevent directory traversal attacks by checking member name
                member_name = member.name
                member_path = os.path.join(dest_path, member_name)
                # Ensure the member name does not contain directory traversal sequences
                if '..' in member_name:
                    return False
                # Check if the member path is within the destination path
                if not os.path.commonpath([dest_path, member_path]) == dest_path:
                    return False

            tar.extractall(path=dest_path)
        return True
    except Exception:
        return False
