import os
from PyPDF2 import PdfMerger

chapters_path = "chapters"

save_path = "ostep.pdf"
merger = PdfMerger()



for file in sorted(os.listdir(chapters_path), key=lambda x: int(x.split("_")[0])):
    file_path = os.path.join(chapters_path, file)
    merger.append(file_path)

merger.write(save_path)
merger.close()

print(f"Book saved to {save_path}\n")
