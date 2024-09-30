import os
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
    title = "Build Failure Detected"
    body = """
    **Build Failure Details:**
    - **Commit SHA**: <commit-sha>
    - **Error Message**: <error-message>
    - **Stack Trace**: <stack-trace>
    - **Build Logs**: <link-to-logs>
    - **Timestamp**: <timestamp>
    """
    labels = ["build-failure"]

    issue = create_github_issue(repo_name, title, body, labels)
    print(f"Issue created: {issue.html_url}")

if __name__ == "__main__":
    main()
