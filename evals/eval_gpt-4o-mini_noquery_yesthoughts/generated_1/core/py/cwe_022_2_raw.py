import os
import tarfile

BASE_DIR = '/safe/base/directory/'  # Define a safe base directory


def is_safe_path(base, target):
    # Resolve the absolute paths
    base = os.path.abspath(base)
    target = os.path.abspath(target)
    # Ensure target is a subdirectory of the base directory
    return os.path.commonpath([base]) == os.path.commonpath([base, target])


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
    # Validate destination path
    if not is_safe_path(BASE_DIR, dest_path):
        return False

    try:
        with tarfile.open(tar_path, 'r:*') as tar:
            # Extract members of the tar file to the specified path
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError) as e:
        print(f'Error occurred: {e}')  # Log the error for debugging
        return False