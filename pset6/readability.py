# Count all letters in string
def count_letter(text):
    sum_letter = 0

    for letter in range(len(text)):
        if text[letter].isalpha():
            sum_letter += 1

    return sum_letter


# Count all words in string
def count_word(text):
    word_list = text.split(" ")

    return len(word_list)


# Count all sentences
def count_sentences(text):
    sum_string = 0

    for word in range(len(text)):
        if text[word] == "." or text[word] == "!" or text[word] == "?":
            sum_string += 1

    return sum_string


# Count grade
def formula(letters, words, sentences):
    l = float(int(letters) / int(words) * 100)
    s = float(int(sentences) / int(words) * 100)

    index = int(round(0.0588 * l - (0.296 * s) - 15.8, 0))

    return index


# Main function
def main():
    # taking input
    text = input("Text: ")

    # Prepare for calculate formula
    letters = count_letter(text)
    words = count_word(text)
    sentences = count_sentences(text)

    # Formula count grade
    grade = formula(letters, words, sentences)

    # Output
    if grade > 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print("Grade ", grade)


# Call main function
main()