#!/bin/zsh

echo -e "Downloading individual chapters...\n"
python download_chapters.py

echo -e "Chapters downloaded to chapter/ \n"
echo -e "Merging the pdfs in one pdf...\n"
python merge_pdf.py

echo -e "Deleting individual chapters...\n"
rm -r chapters

echo -e "Finished!"
