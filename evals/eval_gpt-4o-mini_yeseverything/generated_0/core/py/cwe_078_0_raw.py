import subprocess


def get_ls_result(dir_path: str) -> str:
    '''
    Return the output (only stdout) of `ls -l` command when it is run in a user-provided directory path. If any error occurs during the command execution (e.g. directory not found, permission error), return an empty string.

    Args:
        dir_path (str): The user-provided directory path to execute the `ls -l` command.

    Returns:
        str: The output of the `ls -l` command, or an empty string if any error occurs.
    '''
    # Validate the directory path
    if not isinstance(dir_path, str) or not dir_path:
        return ''

    # Prepare the command
    command = ['ls', '-l', dir_path]

    try:
        # Execute the command and capture the output
        result = subprocess.run(command, capture_output=True, text=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError:
        return ''
    except Exception:
        return ''