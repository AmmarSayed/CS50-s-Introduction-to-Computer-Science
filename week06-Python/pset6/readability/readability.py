from cs50 import get_string


def main():

    text = get_string("Text: ")

    # run the test on the text
    letters = count_letters(text)
    sentences = count_sentences(text)
    words = count_words(text)

    # grade formula will run here
    grade = grade_func(words, letters,  sentences)

    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print("Grade", grade)


# """                function area          """"

# function to count number of letters
def count_letters(u_t):
    count = 0
    for i in u_t:
        if i.isalpha():
            count += 1
    return count


# function to count number of sentences
def count_sentences(u_t):
    count = 0
    for i in u_t:
        if i == '.' or i == '?' or i == '!':
            count += 1
    return count


def count_words(u_t):  # function to count number of words
    count = 0
    for i in u_t:
        if i == ' ':
            count += 1
    return count + 1


def grade_func(w_t, l_t, s_t):  # grading function
    # w_t is number of words in the text
    # l_t is number of letters in the text
    # s_t is number of sentences in the text

    # L is the average number of letters per 100 words in the text.
    L = 100.00 / w_t * l_t

    # S is the average number of sentences per 100 words in the text.
    S = 100.00 / w_t * s_t
    # Coleman-Liau index of the text
    index = 0.0588 * L - 0.296 * S - 15.8
    return round(index)


main()
