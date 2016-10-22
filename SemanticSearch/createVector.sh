make
if [ "$1" == "" ]; then
    echo "Pass the file name to create vector"
else

    time ./word2vec -train $1 -output System$1.bin -cbow 1 -size 200 -window 8 -negative 25 -hs 0 -sample 1e-4 -threads 20 -binary 1 -iter 15
   ./semanticSearch System$1.bin

fi
