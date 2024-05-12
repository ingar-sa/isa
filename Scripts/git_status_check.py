import os
import subprocess

def is_git_repository(directory):
    return os.path.isdir(os.path.join(directory, '.git'))

def has_uncommitted_changes(directory):
    result = subprocess.run(['git', 'status', '--porcelain'], cwd=directory, capture_output=True, text=True)
    return bool(result.stdout.strip())

def check_and_report_changes(starting_directory, ignore_list):
    for root, dirs, _ in os.walk(starting_directory):
        dirs[:] = [d for d in dirs if os.path.join(root, d) not in ignore_list]
        
        for d in dirs:
            directory = os.path.join(root, d)
            if is_git_repository(directory):
                if has_uncommitted_changes(directory):
                    print(f"Uncommitted or unstaged changes found in {directory}")

if __name__ == "__main__":
    ignore_list = [
        'W:\\Tools\\luajit',
    ]

    ignore_list = [os.path.abspath(path) for path in ignore_list]

    check_and_report_changes('W:\\', ignore_list)

