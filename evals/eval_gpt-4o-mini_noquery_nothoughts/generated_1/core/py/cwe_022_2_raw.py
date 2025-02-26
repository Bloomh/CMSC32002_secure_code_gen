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
        # Ensure destination path is absolute and exists
        dest_path = os.path.abspath(dest_path)
        if not os.path.exists(dest_path):
            os.makedirs(dest_path)

        with tarfile.open(tar_path, 'r:*') as tar:
            for member in tar.getmembers():
                # Prevent directory traversal vulnerabilities
                member_path = os.path.join(dest_path, member.name)
                # Ensure the member path is within the destination path
                if not os.path.commonpath([member_path, dest_path]) == dest_path:
                    raise Exception('Potential directory traversal detected.')  
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError, Exception) as e:
        # Optionally log the exception for debugging purposes
        print(f'Error during extraction: {e}')  
        return False