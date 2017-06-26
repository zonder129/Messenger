from gensim.models import Word2Vec
import re
import pymorphy2

model = Word2Vec.load("w2v")


morph = pymorphy2.MorphAnalyzer()
def get_clear(line):
    out = []
    line = line.lower()
    line = re.sub(r'[^\w\s]+|[\d]+', r'',line).strip()
    line = re.sub(r'\s+', ' ', line)
    line = re.sub(r'[^А-Яа-я]', r' ', line)
    line = line.split(' ')
    for word in line:
        p = morph.parse(word)[0]
        out.append(p.normal_form)
    return out

def get_like(words, num=5):
    words = words.decode()
    try:
        words = get_clear(words)
        output = ""
        for word, cosine in model.most_similar(positive=words, topn=num):
            output = output + word + ": "  + str(cosine) + "\n"
    except KeyError:
        return "Not found"
    return output.encode()

def get_summ(words):
    words = words.decode()
    try:
        words=get_clear(words)
    except KeyError:
        return "Not found"
    return model.most_similar(positive=words)[0][0].encode()

def get_raz(words):
    words = words.decode("utf-8")
    try:
        words = get_clear(words)
        words_positiv = words[0]
        words_negative = words[1]
    except KeyError:
        return "Not found"
    return model.most_similar(positive=words_positiv, negative=words_negative)[0][0].encode()
    
def get_not_mach(words):
    words = words.decode()
    print(words)
    try:
        words = get_clear(words)
    except KeyError:
        return "Not found"
    return model.doesnt_match(words).encode()

def echo(word):
    return word
