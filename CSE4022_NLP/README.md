# College - CSE4022: Travel log comparison using NLTK

### Sources 
-	http://www.natgeotraveller.in/six-years-and-counting/
-	http://www.natgeotraveller.in/train-to-nowhere/
-	http://www.natgeotraveller.in/what-dreams-may-come/
-	http://www.natgeotraveller.in/getting-saucy-about-food/
### Initial framework
-	Converting the text into the digital form: In case the received text is not in a standard digital form. In this case, we scrape data off the internet
-	Tokenization of the text: To segment the given piece of text 
-	Removing Stop words: To remove the non-English set of strings such as the html tags which we get from scraping
-	Taking the word count: To identify the number of words required to convey an idea without reader losing interest
-	Stemming & Lemmatization: To get the root words for better intuition as per what is he/she trying to talk about semantically
-	Vectorization:  we can find out the word similarities/semantics
-	POS Tagging: To differentiate the parts of speech to analyse the advantages and the disadvantages that come along with the excessive use of any POS. 
-	Confidence level > 0.8: Pass: All these parameters contribute to a certain confidence level, and a certain amount of points are required to be qualified
### My contribution
-	**Parameter-1**: Word count for optimal retention. Here I have considered the limits as 700-750 words for an optimal article and hence the highest confidence score. 
-	**Parameter-2**: Frequency distribution of words to recognise vocabulary level of the author by seeing the number of repeated words. Under 100 words repeated would give the highest confidence score.
-   **Parameter-3**: Cosine Similarity. For this, we need to consider multiple documents by the same author. Hence this parameter is not applicable for the confidence scores
-	**Parameter-4**: Part of Speech tagging for finding an optimal number of adjectives or “beautifying words” to keep the article interesting throughout but still avoid bloating of the real content. The limits are given in terms of the difference between the total number of words versus the number of adjectives, and an optimal number is assumed to be between 600-700
-	**Parameter-5**: Polysyllabic words do not necessarily increase the complexity of the words, but in a general case, assuming it does, I have given an optimal number to be between 25-35 words with 4 or more syllables
-	**Confidence Score**: Instead of a regular approach of pass/fail criteria, I’ve embedded score calculation in all the parameters to measure how each article (even if they’re from multiple authors) stand against the requirements/expectations of the employer and the articles qualifying will be mentioned with their scores.
<br />
  
# Author
#### ``Allen Ben Philipose`` - 18BIS0043
