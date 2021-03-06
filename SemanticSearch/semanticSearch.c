#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>  // for malloc()

const long long max_size = 2000;         // max length of strings
const long long N = 10;                  // number of closest words that will be shown
const long long max_w = 50;              // max length of vocabulary entries

int main(int argc, char **argv) {
  FILE *f;
  char st1[max_size];
  char *bestw[N];
  char st[100][max_size];
  float dist, len, bestd[N], vec[max_size];
  long long a, b, c, d, cn, bi[100];
  char ch;
  //char *vocab = NULL;
  int tot_models = argc - 1;
  char **vocabs = (char**)malloc(sizeof(char*) * tot_models);
  long long *sizes = (long long*)malloc(sizeof(long long *) * tot_models);
  long long *words = (long long*)malloc(sizeof(long long *) * tot_models);
  char **files = (char**)malloc(sizeof(char*) * tot_models);
  float **M = (float**)malloc(sizeof(float*) * tot_models);
  int model_no = 0;
  long long this_model_size;
  long long this_model_words;
  char *this_model_vocab;
  float *this_model_M;

  int i = 0;
  
  if (argc < 2) {
    printf("Provide text files to train\n");
    return 0;
  }
  

  //Loading models
  for(i = 1; i < argc; i++)
  {
	  model_no = i-1;
	  printf("Loading models from %s\n", argv[i]);
	  files[model_no] = (char*)calloc(sizeof(char), max_size);
	  strcpy(files[model_no], argv[i]);
	  f = fopen(files[model_no], "rb");
	  if (f == NULL) {
		  printf("Input file not found\n");
		  return -1;
	  }

	  fscanf(f, "%lld", &this_model_words);
	  fscanf(f, "%lld", &this_model_size);
	  words[model_no] = this_model_words;
	  sizes[model_no] = this_model_size;
	  vocabs[model_no] = (char *)malloc((long long)this_model_words * max_w * sizeof(char));

	  for (a = 0; a < N; a++) bestw[a] = (char *)malloc(max_size * sizeof(char));

	  M[model_no] = (float *)malloc((long long)this_model_words * (long long)this_model_size * sizeof(float));
	  if (M[model_no] == NULL) {
		  printf("Cannot allocate memory: %lld MB    %lld  %lld\n", (long long)this_model_words * this_model_size * sizeof(float) / 1048576, this_model_words, this_model_size);
		  return -1;
	  }

	  for (b = 0; b < this_model_words; b++) {
		  fscanf(f, "%s%c", &vocabs[model_no][b * max_w], &ch);
		  for (a = 0; a < this_model_size; a++) fread(&M[model_no][a + b * this_model_size], sizeof(float), 1, f);
		  len = 0;
		  for (a = 0; a < this_model_size; a++) len += M[model_no][a + b * this_model_size] * M[model_no][a + b * this_model_size];
		  len = sqrt(len);
		  for (a = 0; a < this_model_size; a++) M[model_no][a + b * this_model_size] /= len;
	  }

	  fclose(f);
  }

  while (1) {
    printf("Enter word (EXIT to break): ");
    a = 0;
    while (1) {
      st1[a] = fgetc(stdin);
      if ((st1[a] == '\n') || (a >= max_size - 1)) {
        st1[a] = 0;
        break;
      }
      a++;
    }
    if (!strcmp(st1, "EXIT")) break;
    cn = 0;
    b = 0;
    c = 0;
    while (1) {
      st[cn][b] = st1[c];
      b++;
      c++;
      st[cn][b] = 0;
      if (st1[c] == 0) break;
      if (st1[c] == ' ') {
        cn++;
        b = 0;
        c++;
      }
    }
    cn++;

	//Getting similar words from each model
	for(i = 0; i < tot_models; i++)
	{
		for (a = 0; a < N; a++) bestd[a] = 0;
		for (a = 0; a < N; a++) bestw[a][0] = 0;

		this_model_words = words[i];
		this_model_vocab = vocabs[i];
		this_model_size  = sizes[i];
		this_model_M     = M[i];

		for (a = 0; a < cn; a++) {
			for (b = 0; b < this_model_words; b++) if (!strcmp(&this_model_vocab[b * max_w], st[a])) break;
			if (b == this_model_words) b = -1;
			bi[a] = b;
			printf("\nWord: %s  |  File: %s  |  Position in vocabulary: %lld\n", st[a], files[i], bi[a]);
			if (b == -1) {
				printf("Out of dictionary word!\n");
				break;
			}
		}
		if (b == -1) continue;
		printf("\n                                              Word \n------------------------------------------------------------------------\n");
		for (a = 0; a < this_model_size; a++) vec[a] = 0;
		for (b = 0; b < cn; b++) {
			if (bi[b] == -1) continue;
			for (a = 0; a < this_model_size; a++) vec[a] += this_model_M[a + bi[b] * this_model_size];
		}
		len = 0;
		for (a = 0; a < this_model_size; a++) len += vec[a] * vec[a];
		len = sqrt(len);
		for (a = 0; a < this_model_size; a++) vec[a] /= len;
		for (a = 0; a < N; a++) bestd[a] = -1;
		for (a = 0; a < N; a++) bestw[a][0] = 0;
		for (c = 0; c < this_model_words; c++) {
			a = 0;
			for (b = 0; b < cn; b++) if (bi[b] == c) a = 1;
			if (a == 1) continue;
			dist = 0;
			for (a = 0; a < this_model_size; a++) dist += vec[a] * this_model_M[a + c * this_model_size];
			for (a = 0; a < N; a++) {
				if (dist > bestd[a]) {
					for (d = N - 1; d > a; d--) {
						bestd[d] = bestd[d - 1];
						strcpy(bestw[d], bestw[d - 1]);
					}
					bestd[a] = dist;
					strcpy(bestw[a], &this_model_vocab[c * max_w]);
					break;
				}
			}
		}
		for (a = 0; a < N; a++) printf("%50s\t\t\n", bestw[a]);
	}
  }
  return 0;
}
