# SemanticContentSearchP2P

A peer-to-peer (P2P) network is created when two or more PCs are connected and they share resources without going through a separate server computer. Each node has the same capabilities and can act as both a client and server.
We can a p2p network by connecting systems using their IP address by using tools like gnutella, ducto, nitroShare etc. and then after creating the network, we can use the shared folder to search for the contents inside files.
For semantic content searching, we have used a built in tool i.e. Google's word2vec tool. WE have used CBOW model of word2vec and for clustering of data, we have used K-mean technique.

For testing of code, we have given a sampleData.txt file.

How to run?
1. By using "make" command, we can compile and make all files as executable file.
2. preprocess the text data files to remove special symbols and extra blank spaces using 
   "cd <training_data_dir>;
   python pre_process_4_word2vec.py <file_name>"
3. Combine all in one file
   "cat *.processed/* >> /<path_to_new_file>"
4. We need to create vectors of the text data files. 
   Use "./createVector.sh" in each system to create vectors.
5. Use "./semanticSearch <WORD_TO_BE_SEARCHED>" to search for the word.
6. Output will be the semnatically related words and the node number in peer to peer connection.


