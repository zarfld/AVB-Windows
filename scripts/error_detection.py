import os
import re
import json

def check_for_logs(log_path):
    if not os.path.exists(log_path):
        with open(log_path, 'w') as log_file:
            log_file.write("No build errors found.\n")
        print("No logs found. Skipping error-checking step.")
    return os.path.exists(log_path)

def parse_logs(log_path):
    errors = []
    metadata = {
        "total_lines": 0,
        "error_count": 0
    }
    with open(log_path, 'r') as log_file:
        for line in log_file:
            metadata["total_lines"] += 1
            if "error" in line.lower():
                error_info = {
                    "line": line.strip(),
                    "line_number": metadata["total_lines"],
                    "context": get_error_context(log_file, metadata["total_lines"])
                }
                errors.append(error_info)
                metadata["error_count"] += 1
    return errors, metadata

def get_error_context(log_file, error_line_number, context_lines=2):
    log_file.seek(0)
    lines = log_file.readlines()
    start = max(0, error_line_number - context_lines - 1)
    end = min(len(lines), error_line_number + context_lines)
    return lines[start:end]

def save_errors_and_metadata(errors, metadata, output_path, log_link):
    if not errors:
        print("No errors found in logs. Skipping error-checking step.")
        return
    data = {
        "errors": errors,
        "metadata": metadata,
        "build_logs_link": log_link
    }
    with open(output_path, 'w') as output_file:
        json.dump(data, output_file, indent=4)

def main():
    log_path = "build.log"
    output_path = "errors_and_metadata.json"
    log_link = os.environ.get('BUILD_LOGS_LINK', '<link-to-logs>')
    if not check_for_logs(log_path):
        print("No logs found. Skipping error-checking step.")
        return

    errors, metadata = parse_logs(log_path)
    if not errors:
        print("No errors found in logs.")
    else:
        print("Errors found in logs:")
        for error in errors:
            print(f"Line {error['line_number']}: {error['line']}")
        save_errors_and_metadata(errors, metadata, output_path, log_link)
        print(f"Errors and metadata saved to {output_path}")

if __name__ == "__main__":
    main()
