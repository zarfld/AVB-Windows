import os
import re
import json
from github import Github
import requests

def check_for_logs(log_paths):
    existing_logs = []
    for log_path in log_paths:
        if os.path.exists(log_path):
            existing_logs.append(log_path)
        else:
            print(f"No logs found for {log_path}. Skipping error-checking step.")
    if not os.environ.get('GITHUB_TOKEN'):
        print("GITHUB_TOKEN environment variable is not set. Please check repository settings.")
        return []
    return existing_logs

def parse_logs(log_paths):
    errors = []
    metadata = {
        "total_lines": 0,
        "error_count": 0
    }
    for log_path in log_paths:
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
    if not os.environ.get('GITHUB_TOKEN'):
        print("GITHUB_TOKEN environment variable is not set. Please check repository settings.")
        return [], metadata
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
        "build_logs_link": log_link,
        "github_token_status": "set" if os.environ.get('GITHUB_TOKEN') else "not set"
    }
    with open(output_path, 'w') as output_file:
        json.dump(data, output_file, indent=4)

def update_issue_labels(issue, labels):
    issue_labels = [label.name for label in issue.labels]
    for label in labels:
        if label not in issue_labels: issue_labels.append(label)
    issue.edit(labels=issue_labels)

def verify_build_logs_link(log_link):
    try:
        response = requests.head(log_link)
        return response.status_code == 200
    except requests.RequestException:
        return False

def check_log_file_existence(log_path):
    return os.path.exists(log_path)

def create_dynamic_path_string(log_paths):
    existing_logs = [log_path for log_path in log_paths if check_log_file_existence(log_path)]
    return " ".join(existing_logs)

def get_github_token():
    token = os.environ.get('GITHUB_TOKEN')
    if not token:
        raise ValueError("GITHUB_TOKEN environment variable not set")
    return token

def main():
    log_paths = [
        "build.log",
        "install_dependencies.log",
        "install_windows_sdk.log",
        "install_windows_driver_kit.log",
        "install_kmdf_build_tools.log",
        "C:\\ProgramData\\chocolatey\\logs\\chocolatey.log"
    ]
    output_path = "errors_and_metadata.json"
    log_link = os.environ.get('BUILD_LOGS_LINK', '<link-to-logs>')
    existing_logs = check_for_logs(log_paths)
    if not existing_logs:
        print("No logs found. Skipping error-checking step.")
        return

    errors, metadata = parse_logs(existing_logs)
    if not errors:
        print("No errors found in logs.")
    else:
        print("Errors found in logs:")
        for error in errors:
            print(f"Line {error['line_number']}: {error['line']}")
        save_errors_and_metadata(errors, metadata, output_path, log_link)
        print(f"Errors and metadata saved to {output_path}")

    # Automate status updates using labels based on CI pipeline progress
    token = get_github_token()

    g = Github(token)
    repo_name = "zarfld/AVB-Windows"
    repo = g.get_repo(repo_name)
    commit_sha = os.environ.get('COMMIT_SHA', '<commit-sha>')
    issue_title = f"Build Failure on Commit {commit_sha}"
    issues = repo.get_issues(state='open')
    for issue in issues:
        if issue.title == issue_title:
            if metadata["error_count"] > 0:
                update_issue_labels(issue, ["failed CI"])
            else:
                update_issue_labels(issue, ["passed CI"])
            break
    else:
        if metadata["error_count"] > 0:
            labels = ["build-failure", "failed CI"]
        else:
            labels = ["build-failure", "passed CI"]
        if verify_build_logs_link(log_link):
            build_logs_message = f"Build logs: {log_link}"
        else:
            build_logs_message = "Build logs: No build logs available or link is inaccessible"
        repo.create_issue(
            title=issue_title,
            body=build_logs_message,
            labels=labels
        )

    dynamic_path_string = create_dynamic_path_string(log_paths)
    print(f"Dynamic path string: {dynamic_path_string}")

if __name__ == "__main__":
    main()
