/*!
 * Sylphrena AI input program - https://github.com/ShardAi
 * Version - 1.0.0.0
 *
 * Copyright (c) 2017 Eirik Skjeggestad Dale
 */

use input::syl_wordgram::Unigram;
use input::syl_wordgram::Bigram;
use std::fs::File;
use std::io::prelude::*;

pub struct Sylnlp{
    id: String,
    unigrams: Vec<Unigram>,
    bigrams: Vec<Bigram>
}

impl Sylnlp {
    pub fn new(id: &str) -> Sylnlp{
        let nlp = Sylnlp {
            id: id.to_string(),
            unigrams: Vec::new(),
            bigrams: Vec::new() 
        };
        println!("Created {}!", nlp.id.to_string());
        return nlp;
    }

    pub fn train_nlp(&mut self, training_text: &str) {
        println!("Training {0} using training text: {1}!", self.id.to_string(), training_text.to_string());
        let mut f = File::open(training_text).expect("file not found");

        let mut contents = String::new();
        f.read_to_string(&mut contents).expect("Something went wrong reading the file");

        contents = contents.replace("_", "");
        contents = contents.replace("--", " ");
        contents = contents.replace(".", "");
        contents = contents.replace(",", "");
        contents = contents.replace("=", "");
        contents = contents.replace("+", "");
        contents = contents.replace("?", "");
        contents = contents.replace("!", "");
        contents = contents.replace(":", "");
        contents = contents.replace(";", "");
        contents = contents.replace("[", "");
        contents = contents.replace("]", "");
        contents = contents.replace("/", "");
        contents = contents.replace("{", "");
        contents = contents.replace("}", "");
        contents = contents.replace("(", "");
        contents = contents.replace(")", "");
        contents = contents.replace("\n", " ");
        contents = contents.replace("  ", " ");

        let training_set: Vec<&str> = contents.split(" ").collect();

        let number_of_words = training_set.len();

        let mut prev_word = "";
        let mut debugc = 0.0;
        for word in training_set.iter() {
            debugc = debugc + 1.0;
            if debugc % 1000.0 == 0.0 {
                println!("TRAINING ITERATION NUMBER: {0}/{1}", debugc, number_of_words);
            }
            let mut unigrams_exist = false;
            for i in 0..self.unigrams.len() {
                if self.unigrams[i].matches(word) {
                    unigrams_exist = true;
                    break;
                }
            }
            if !unigrams_exist {
                self.unigrams.push(Unigram::new(word));
            }
            if prev_word != "" && word.to_string() != "" {
                let mut bigrams_exist = false;
                for i in 0..self.bigrams.len() {
                    if self.bigrams[i].matches(prev_word, word) {
                        bigrams_exist = true;
                        break;
                    }
                }
                if !bigrams_exist {
                    self.bigrams.push(Bigram::new(prev_word, word));
                }
            }
            prev_word = word;
        }


        let mut top_prio = 0.0;
        let mut top_i = 0;
        for i in 0..self.unigrams.len() {
            self.unigrams[i].calc_probability(number_of_words as f64);
            if self.unigrams[i].get_probability() > top_prio {
                top_prio = self.unigrams[i].get_probability();
                top_i = i;
            }
        }
        println!("Total of {0} unigrams found. Top unigram is number {1}; wordgram: \"{2}\", probability: {3}", self.unigrams.len(),
        top_i, self.unigrams[top_i].get_word(), self.unigrams[top_i].get_probability());


        top_prio = 0.0;
        top_i = 0;
        for i in 0..self.bigrams.len() {
            self.bigrams[i].calc_probability(number_of_words as f64);
            if self.bigrams[i].get_probability() > top_prio {
                top_prio = self.bigrams[i].get_probability();
                top_i = i;
            }
        }
        println!("Total of {0} bigrams found. Top bigram is number {1}; wordgram: \"{2} {3}\", probability: {4}", self.unigrams.len(),
        top_i, self.bigrams[top_i].get_word1(), self.bigrams[top_i].get_word2(), self.bigrams[top_i].get_probability());
    }
}