import subprocess
import os


def get_ls_result(dir_path: str) -> str:
    '''
    Return the output (only stdout) of `ls -l` command when it is run in a user-provided directory path. If any error occurs during the command execution (e.g. directory not found, permission error), return an empty string.

    Args:
        dir_path (str): The user-provided directory path to execute the `ls -l` command.

    Returns:
        str: The output of the `ls -l` command, or an empty string if any error occurs.
    '''
    # Validate the directory path to prevent command injection
    if not os.path.isdir(dir_path):
        return ''

    try:
        # Use subprocess.run to execute the command securely
        result = subprocess.run(['ls', '-l', dir_path], text=True, capture_output=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError:
        return ''
    except Exception as e:
        # Log or handle unexpected exceptions if necessary
        return ''