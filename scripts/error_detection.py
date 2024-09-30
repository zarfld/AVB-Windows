import os
import re

def check_for_logs(log_path):
    return os.path.exists(log_path)

def parse_logs(log_path):
    errors = []
    with open(log_path, 'r') as log_file:
        for line in log_file:
            if "error" in line.lower():
                error_message = line.strip()
                suggestion = get_suggestion_for_error(error_message)
                errors.append((error_message, suggestion))
    return errors

def get_suggestion_for_error(error_message):
    suggestions = {
        "nuget restore": "Check if the NuGet packages are correctly configured and available.",
        "msbuild": "Ensure that the solution builds correctly in Visual Studio.",
        "vstest.console": "Verify that all unit tests pass locally.",
        "PVS-Studio": "Check the PVS-Studio log for detailed analysis results.",
        "clang-format": "Ensure that the code follows the specified formatting guidelines."
    }
    for key in suggestions:
        if key in error_message:
            return suggestions[key]
    return "No suggestion available."

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
        for error, suggestion in errors:
            print(f"Error: {error}")
            print(f"Suggestion: {suggestion}")

if __name__ == "__main__":
    main()
