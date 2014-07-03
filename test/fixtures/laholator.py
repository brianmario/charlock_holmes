#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# @author:     starenka
# @email:      'moc]tod[liamg].T.E[0aknerats'[::-1]

import warnings, hashlib, simplejson, string
from os.path import dirname, abspath

from flask import Flask, render_template, request
from flaskext.sqlalchemy import SQLAlchemy
try:
    from sqlalchemy.exceptions import IntegrityError
except ImportError:
    from sqlalchemy.exc import IntegrityError

#Hey monkey patcher! NLTK's NgramModel is not serializable w/ pickle.HIGHEST_PROTOCOL (2)
from werkzeug.contrib import cache
cache.HIGHEST_PROTOCOL = 1
from werkzeug.contrib.cache import SimpleCache

from BeautifulSoup import BeautifulSoup
import nltk

PUNCT = list(unicode(string.punctuation))

app = Flask(__name__)
app.config.from_object('settings')
cache = SimpleCache()

app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///%s/db.sqlite3'%abspath(dirname(__file__))
db = SQLAlchemy(app)

class Sample(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    url = db.Column(db.String(80), unique=True)
    text = db.Column(db.String())
    enabled = db.Column(db.Boolean())

    def __unicode__(self):
        str = unicode(BeautifulSoup(self.text,convertEntities=BeautifulSoup.HTML_ENTITIES))
        return nltk.clean_html(str)

    @classmethod
    def get_all(self):
        cached = cache.get('samples')
        if cached is None:
            cached = self.query.filter_by(enabled=True).all()
            cache.set('samples', cached, timeout=app.config['CACHE_MINUTES'] * 60)
        return cached

class Output(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    hash = db.Column(db.String(128),unique=True)
    text = db.Column(db.String())
    params = db.Column(db.String(100))
    
    def __init__(self,text,**params):
        self.hash = hashlib.sha512(text.encode('utf8')).hexdigest()
        self.text = text
        self.params = simplejson.dumps(params)

@app.context_processor
def base_context():
    return dict(settings=app.config,
        hits = Output.query.count() + app.config['INIT_HITS']
    )

@app.errorhandler(404)
def page_not_found(error):
    return render_template('404.html',title=u"To tady nemáme!"), 404

@app.route('/faq')
def faq():
    return render_template('faq.html',title=u"Často kladené dotazy",samples=Sample.get_all())

@app.route('/permalink/<hash>')
def permalink(hash):
    one = Output.query.filter_by(hash=hash).first_or_404()
    return render_template('generator.html', title=u"Henrykuj!", 
                           text=one.text, hash=one.hash,  
                           **simplejson.loads(one.params)
    )

@app.route('/')
def index():
    bigrams = request.args.get('bigrams',False)
    try:
        words = int(request.args.get('words',app.config['WORDS']))
        if words > app.config['MAX_WORDS']:
            words = app.config['MAX_WORDS']
    except ValueError:
        words = app.config['WORDS']

    out = _generate(words,bigrams)
    output = Output(out,words=words,bigrams=bool(bigrams))
    try:
        db.session.add(output)
        db.session.commit()
    except IntegrityError:
        pass
    
    return render_template('generator.html', title=u"Henrykuj!",
                           text=out, hash=output.hash,
                           words=words, bigrams=bigrams
    )

def _get_ngram_model(bigrams):
    #NLTK produces a LOT of warnings - don't mess with my error log
    warnings.simplefilter("ignore")
    cached = cache.get('ngram_model')
    if cached is None:
        samples = Sample.get_all()
        if samples:
            text = [unicode(s) for s in samples]
            tokenizer = nltk.tokenize.WordPunctTokenizer()
            tokenized = tokenizer.tokenize(' '.join(text))
            cached = nltk.NgramModel(3-int(bool(bigrams)), tokenized)
            cache.set('ngram_model', cached, timeout=app.config['CACHE_MINUTES'] * 60)
    return cached

def _generate(words,bigrams):
    model = _get_ngram_model(bigrams)
    starts = model.generate(100)[-4:]
    starts = filter(lambda a: a not in PUNCT,starts)
    generated = model.generate(words, starts)
    out = ' '.join(generated).replace(' , ',', ').replace(' . ','. ')
    return '%s%s&hellip;'%(out[0].upper(),out[1:])

if __name__ == '__main__':
    app.run()