import os
import requests
from github import Github

def check_repo_existence(repo_name):
    token = os.environ.get('GITHUB_TOKEN')
    if not token:
        raise ValueError("GITHUB_TOKEN environment variable not set")

    g = Github(token)
    try:
        repo = g.get_repo(repo_name)
        print(f"Repository '{repo_name}' exists.")
    except Exception as e:
        print(f"Repository '{repo_name}' does not exist: {e}")

def main():
    repo_name = "zarfld/AVB-Windows"
    check_repo_existence(repo_name)

if __name__ == "__main__":
    main()
