import re

# Open the file
with open('french_words.txt', 'r') as file:
    # Read the content of the file
    content = file.read()

# Use a regular expression to remove all characters that are not a-z
cleaned_content = re.sub('[^a-z\n]', '', content.lower())

# Open the file in write mode
with open('french_words.txt', 'w') as file:
    # Write the cleaned content back to the file
    file.write(cleaned_content)