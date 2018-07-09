#!/usr/bin/ruby -w

# Main program goes here
def unigram_exists(word)
	$unigrams.each do |x|
		if x.matches(word)
			x.increase_count
			return true
		end	
	end
	return false
end

def bigram_exists(word1, word2)
	$bigrams.each do |x|
		if x.matches(word1, word2)
			x.increase_count
			return true
		end	
	end
	return false
end

def get_training_set(filename)
	data = ''
	f = File.open(filename, "r") 
	f.each_line do |line|
		data += line
	end
	replacements = [ ["_", ""] , [".", ""] , [",", ""] , ["=", ""] , ["+", ""] , ["?", ""] , ["!", ""] , [":", ""] , [";", ""] , ["[", ""] , ["]", ""] , ["/", ""] , ["{", ""] , ["}", ""] , ["(", ""] , [")", ""] ]
	replacements.each {|replacement| data.gsub!(replacement[0], replacement[1])}
	return data.split(/\W+/)
end

def viterbi(input_string)
	puts "Viterbi algorithm started! The input for this run is:"
	puts input_string
	
	output = Array.new
	tmp_string = input_string
	k = 0
	begin
		working_string = ''
		un = 0
		bn = 0
		iteration_unigrams = Array.new
		iteration_bigrams = Array.new
		# Find matching unigrams and bigrams and add it to list.
		for j in 0..(tmp_string.length-1)
			working_string += tmp_string[j]
			$unigrams.each do |x|
				if x.matches(working_string)
					puts "MATCH FOUND:UNIGRAM:: " + working_string + " -> " + x.get_probability.to_s
					iteration_unigrams[un] = [x.get_word, x.get_probability]
					un += 1
				end	
			end
			$bigrams.each do |x|
				if working_string == (x.get_word1+x.get_word2)
					puts "MATCH FOUND:BIGRAM:: " + working_string + ", " + x.get_word1+" "+x.get_word2 + " -> " + x.get_probability.to_s
					iteration_bigrams[bn] = [x.get_word1, x.get_probability]
					bn += 1
				end	
			end
		end
		# Find the most likely unigram that gives the next word
		top_unigram = ''
		top_unigram_probability = 0.0
		iteration_unigrams.each do |x|
			if x[1] > top_unigram_probability
				top_unigram = x[0]
				top_unigram_probability = x[1]
			end
		end
		# Find the most likely bigram that gives the next word
		top_bigram = ''
		top_bigram_probability = 0.0
		iteration_bigrams.each do |x|
			if x[1] > top_bigram_probability
				top_bigram = x[0]
				top_bigram_probability = x[1]
			end
		end
		puts "The top priority unigram is \"#{top_unigram}\":#{top_unigram_probability}, while the top bigram word is: \"#{top_bigram}\":#{top_bigram_probability}"
		wordfound = ''
		# Choose which of the two sets the found word. Bigram gets a boost, but ideally these will be the same
		if top_unigram == top_bigram
			wordfound = top_unigram
		else
			if top_unigram_probability > (top_bigram_probability*100)
				wordfound = top_unigram
			else
				wordfound = top_bigram
			end
		end
		if top_unigram == '' && top_bigram == ''
			wordfound = tmp_string[0]
			puts "HACK to get wordfound: " + wordfound
		end
		# Check if a concatination of the found word with the previous word makes more sense (for -est, -er, -y etc. in fully, longer, longest)
		if k > 0 && wordfound.length > 0
			concatinated_word = output[k-1] + wordfound
			$unigrams.each do |x|
				if x.matches(concatinated_word) && x.get_probability > top_unigram_probability
					tmp_string = output[k-1] + tmp_string
					wordfound = output[k-1] + wordfound
					k = k-1
				end	
			end
		end
		# Deduct the new word from the start of tmp_string and add it to output array.
		if wordfound.length > 0
			output[k] = wordfound
			k += 1
			tmp_string = tmp_string[wordfound.length..-1]
		else
			output[k] = tmp_string[0]
			k += 1
			tmp_string = tmp_string[1..-1]
		end
	end until tmp_string.length <= 0 #Repeat until the tmp_string is empty
	puts "Split sentence: " + output.join(" ")
end

class Unigram 
	def initialize(word)
		@m_word = word
		@no_occurences = 1.0
		@m_probability = 1.0
	end
	def print_n_gram
		puts "Printing wordgram: #@m_word|#@no_occurences|#@m_probability"
	end
	def matches(word)
		if @m_word == word
			return true
		else
			return false
		end
	end
	def get_word
		return @m_word
	end
	def get_probability
		return @m_probability
	end
	def increase_count
		@no_occurences += 1.0
	end
	def calculate_probability(total_number)
		@m_probability = @no_occurences/total_number
	end
end

class Bigram 
	def initialize(word1, word2)
		@m_word1 = word1
		@m_word2 = word2
		@no_occurences = 1.0
		@m_probability = 0.0
	end
	def print_n_gram
		puts "Printing wordgram: #@m_word1 #@m_word2|#@no_occurences|#@m_probability"
	end
	def matches(word1, word2)
		if @m_word1 == word1 && @m_word2 == word2
			return true
		else
			return false
		end
	end
	def get_word1
		return @m_word1
	end
	def get_word2
		return @m_word2
	end
	def get_probability
		return @m_probability
	end
	def increase_count
		@no_occurences += 1.0
	end
	def calculate_probability(total_number)
		@m_probability = @no_occurences/total_number
	end
end

start_time = Time.now

test_string = "thattextdidnotworkverywellmaybethisonewilldobetter" #"nowletustryamoreambiguoustextasentryfortheprogramiammaking"
training_set = get_training_set "bigtext"
number_of_words = training_set.size

puts number_of_words.to_s

$unigrams = []
unknown_unigram = Unigram.new("<UNK>")

$bigrams = []

previous_word = ""
training_set.each do |word|
	if not unigram_exists(word)
		$unigrams.push Unigram.new(word)
		unknown_unigram.increase_count
	end
	if previous_word != ""
		if not bigram_exists(previous_word, word)
			$bigrams.push Bigram.new(previous_word, word)
		end
	end
	previous_word = word
end

no_of_unigrams = $unigrams.size
no_of_bigrams = $bigrams.size
puts "DONE CREATING N-GRAMS!!! Number of n-grams: " + no_of_unigrams.to_s + "|" + no_of_bigrams.to_s

$unigrams.each do |x|
	x.calculate_probability(number_of_words)
end
$bigrams.each do |x|
	x.calculate_probability(number_of_words)
end

viterbi(test_string)

$run_time = Time.now - start_time

BEGIN {
	puts "NLP Testing application started!";
}
END {
	puts "NLP Testing application finished running! duration: " + $run_time.to_s;
}

