import os
import re

def check_for_logs(log_path):
    return os.path.exists(log_path)

def parse_logs(log_path):
    errors = []
    with open(log_path, 'r') as log_file:
        for line in log_file:
            if "error" in line.lower():
                errors.append(line.strip())
    return errors

def main():
    log_path = "build.log"
    if not check_for_logs(log_path):
        print("No logs found. Skipping error-checking step.")
        return

    errors = parse_logs(log_path)
    if not errors:
        print("No errors found in logs.")
    else:
        print("Errors found in logs:")
        for error in errors:
            print(error)

if __name__ == "__main__":
    main()
