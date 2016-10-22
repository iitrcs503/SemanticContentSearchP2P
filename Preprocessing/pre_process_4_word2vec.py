import sys
import re
import os
import glob

def clean(f_in, f_out):
    text            = open(f_in).read()
    text            = text.lower()
    cleaned_text    = re.sub('[^a-zA-Z]', ' ', text)
    cleaned_text    = re.sub(' +', ' ', cleaned_text)
    open(f_out, "w").write(cleaned_text)

def main(args):
    dirs = args
    for each_dir in dirs:
        each_dir = each_dir.rstrip("/")
        processed_dir = "%s.processed" % each_dir
        os.system("mkdir %s" % processed_dir)
        #import pdb; pdb.set_trace()
        files = glob.glob("%s/*" % each_dir)
        for each_file in files:
            print "Processing %s" % each_file
            processed_file = "%s/%s" % (processed_dir, os.path.basename(each_file))
            clean(each_file, processed_file)

if __name__ == '__main__':
    main(sys.argv[1:])
