/*!
 * Sylphrena AI input program - https://github.com/ShardAi
 * Version - 1.0.0.0
 *
 * Copyright (c) 2017 Eirik Skjeggestad Dale
 */

pub struct Unigram{
    word: String,
    occurences: f64,
    probability: f64
}

pub struct Bigram{
    word1: String,
    word2: String,
    occurences: f64,
    probability: f64
}

impl Unigram{
    pub fn new(w: &str) -> Unigram{
        let ug = Unigram {
            word: w.to_string(),
            occurences: 1.0,
            probability: 0.0
        };
        return ug;
    }

    pub fn add_occurence(&mut self) {
        self.occurences += 1.0;
    } 

    pub fn calc_probability(&mut self, words_total: f64) {
        self.probability = (self.occurences)/words_total;
    } 

    pub fn get_probability(&mut self) -> f64 {
        return self.probability;
    }

    pub fn get_word(&mut self) -> String {
        return self.word.to_string();
    }

    pub fn matches(&mut self, w: &str) -> bool {
        if w == self.word {
            self.add_occurence();
            return true;
        }
        return false;
    }
}

impl Bigram{
    pub fn new(w1: &str, w2: &str) -> Bigram{
        let bg = Bigram {
            word1: w1.to_string(),
            word2: w2.to_string(),
            occurences: 1.0,
            probability: 0.0
        };
        return bg;
    }

    pub fn add_occurence(&mut self) {
        self.occurences += 1.0;
    } 

    pub fn calc_probability(&mut self, words_total: f64) {
        self.probability = (self.occurences)/words_total;
    } 

    pub fn get_probability(&mut self) -> f64 {
        return self.probability;
    }

    pub fn get_word1(&mut self) -> String {
        return self.word1.to_string();
    }

    pub fn get_word2(&mut self) -> String {
        return self.word2.to_string();
    }

    pub fn matches(&mut self, w1: &str, w2: &str) -> bool {
        if w1 == self.word1 && w2 == self.word2 {
            self.add_occurence();
            return true;
        }
        return false;
    }
}