from random import randint, shuffle

cyrillic = 'абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ'
latin = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
digits = '0123456789'
specials = '#$^%@'

dict = cyrillic + latin + digits + specials

def generate_word(max_word_len):
    word_len = randint(1, max_word_len)
    word = ''
    for _ in range(word_len):
        word += dict[randint(0, len(dict)-1)]
    return word


def generate_sentence(max_words_number, max_word_len):
    sentence = ' ' * randint(0, 2)
    words_number = randint(1, max_words_number)
    
    for j in range(words_number):
        word = generate_word(max_word_len)
        if (j != words_number-1):
            word += ','*randint(0, 1) + ' '*randint(1, 2) # you can add "+ '\t' * randint(...)" if you want (optional)
        sentence += word
    sentence += '.' + [' ', '\n'][randint(0, 1)]
    return sentence


def generate_text(sentences_number, max_words_number, max_word_len):
    text = []

    for i in range(sentences_number):
        sentence = generate_sentence(max_words_number, max_word_len)
        text += [sentence]
    for i in range(5, len(text), 5):
        text += [text[i]] * randint(1, 5)
    shuffle(text)
    return text

sentences_number = int(input('sentences_number: '))
max_words_number = int(input('max_words_number: '))
max_word_len = int(input('max_word_len: '))


text = generate_text(sentences_number, max_words_number, max_word_len)
print('text generated + duplicates added')
test = open('test.txt', 'w')
test.write(''.join(text))
test.close()