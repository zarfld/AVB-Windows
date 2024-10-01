import os
import json
import requests
from github import Github

def create_github_issue(repo_name, title, body, labels):
    token = os.environ.get('GITHUB_TOKEN')
    if not token:
        raise ValueError("GITHUB_TOKEN environment variable not set")

    g = Github(token)
    repo = g.get_repo(repo_name)
    
    # Check for existing issues with the same title
    existing_issues = repo.get_issues(state='open')
    for issue in existing_issues:
        if issue.title == title:
            # Update the existing issue with additional information
            issue.create_comment(body)
            return issue

    # Create a new issue if no duplicate is found
    issue = repo.create_issue(
        title=title,
        body=body,
        labels=labels
    )
    return issue

def main():
    repo_name = "zarfld/AVB-Windows"
    title = "Build Failure on Commit SHA"
    
    # Read the saved errors and metadata file
    try:
        with open("errors_and_metadata.json", "r") as file:
            data = json.load(file)
    except FileNotFoundError:
        print("Error: 'errors_and_metadata.json' file not found.")
        return
    
    errors = data["errors"]
    metadata = data["metadata"]
    log_link = data.get("build_logs_link", "<link-to-logs>")
    
    if not errors:
        print("No errors found in logs. Skipping issue creation.")
        return
    
    error_messages = "\n".join([f"Line {error['line_number']}: {error['line']}" for error in errors])
    
    body = f"""
    **Build Failure Details:**
    - **Commit SHA**: {os.environ.get('COMMIT_SHA', '<commit-sha>')}
    - **Error Message**: {error_messages}
    - **Total Lines**: {metadata["total_lines"]}
    - **Error Count**: {metadata["error_count"]}
    - **Build Logs**: {log_link if log_link != "<link-to-logs>" else "No build logs available"}
    - **Timestamp**: {os.environ.get('GITHUB_RUN_TIMESTAMP', '<timestamp>')}
    """
    labels = ["build-failure", "bug"]

    issue = create_github_issue(repo_name, title, body, labels)
    print(f"Issue created: {issue.html_url}")

if __name__ == "__main__":
    main()
