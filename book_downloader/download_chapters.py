import wget
import os
import requests
from urllib.parse import urljoin
from bs4 import BeautifulSoup
import numpy as np

url = "https://pages.cs.wisc.edu/~remzi/OSTEP/"
save_dir = "chapters"
os.makedirs(save_dir, exist_ok=True)

response = requests.get(url)
soup = BeautifulSoup(response.text, 'html.parser')

table = soup.find_all("table")[3]
rows = table.find_all('tr')

num_rows = len(rows)
num_cols = max(len(row.find_all('td')) for row in rows)

files = np.empty((num_rows, num_cols), dtype=object)

for row_idx, row in enumerate(rows):
    col_data = row.find_all('td')
    col_idx = 0
    for col_idx, col_info in enumerate(col_data):
        file_paths = col_info.find_all("a", href=True)
        file_name = [file_path['href'] for file_path in file_paths if file_path['href'].endswith(".pdf")]
        file_name = file_name[0] if len(file_name) > 0 else None

        files[row_idx][col_idx] = file_name

index = 0
for col_idx in range(files.shape[1]):
    for row_idx in range(files.shape[0]):
        file_name = files[row_idx][col_idx]
        if file_name is not None:
            file_url = urljoin(url, f"{file_name}")
            save_path = os.path.join(save_dir, f"{index}_{file_name}")

            wget.download(file_url, save_path)

            print(f"\nDownloaded file {file_name} to {save_path}\n")
            index += 1
