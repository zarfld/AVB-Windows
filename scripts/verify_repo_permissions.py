import os
import requests
from github import Github

def check_repo_permissions(repo_name):
    token = os.environ.get('GITHUB_TOKEN')
    if not token:
        raise ValueError("GITHUB_TOKEN environment variable not set")

    g = Github(token)
    repo = g.get_repo(repo_name)
    
    try:
        repo.get_contents("")
        print("Repository permissions are sufficient.")
    except Exception as e:
        print(f"Repository permissions are insufficient: {e}")

def main():
    repo_name = "zarfld/AVB-Windows"
    check_repo_permissions(repo_name)

if __name__ == "__main__":
    main()
