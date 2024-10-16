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

def verify_build_logs_link(log_link):
    try:
        response = requests.head(log_link)
        return response.status_code == 200
    except requests.RequestException:
        return False

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
    
    if verify_build_logs_link(log_link):
        build_logs_message = f"**Build Logs**: {log_link}"
    else:
        build_logs_message = "**Build Logs**: No build logs available or link is inaccessible"
    
    body = f"""
    **Build Failure Details:**
    - **Commit SHA**: {os.environ.get('COMMIT_SHA', '<commit-sha>')}
    - **Error Message**: {error_messages}
    - **Total Lines**: {metadata["total_lines"]}
    - **Error Count**: {metadata["error_count"]}
    - {build_logs_message}
    - **Timestamp**: {os.environ.get('GITHUB_RUN_TIMESTAMP', '<timestamp>')}
    """
    labels = ["build-failure", "bug"]

    # Link issues to specific CI pipeline stages using keywords in commit messages and PR descriptions
    if "Closes" in os.environ.get('COMMIT_MESSAGE', ''):
        body += "\n\n**Linked to CI Pipeline Stage**: Deployment"
        labels.append("deployment")

    issue = create_github_issue(repo_name, title, body, labels)
    print(f"Issue created: {issue.html_url}")

    # Automatically close issues when the CI pipeline successfully completes a deployment
    if "Closes" in os.environ.get('COMMIT_MESSAGE', ''):
        issue.edit(state="closed")
        print(f"Issue closed: {issue.html_url}")

if __name__ == "__main__":
    main()
