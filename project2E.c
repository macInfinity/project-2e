#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_word_count(char *str, char *delims);
void get_reigons(char *str, char *delims, int **reigons);
int is_delim(char c, char * delim);
int main(int argc, char *argv[])
{

	/* My intro setup just to make sure everything is there...
	 * going to delete at the end :) */	
	printf("Argc is: %d\n",argc);
	for(int i =0; i < argc; i++)
	{
		printf("arg[%d]: %s\n",i,argv[i]);
	}
	

	/* Project2E Starts here: 
	 * 
	 * USAGE: 
	 * 	$./project filename word1 word2 world3
	 * 	  The word "word1" occurs x times.
	 * 	  The word "word2" occurs y times.
	 * 	  the word "word3" occors z times.
	 * NOTE:
	 * 	* You also need to use (malloc) two times
	 *	* Must fail gracefully 	*/
	 
	 /* Check that there is at least three arguments: */
	if(argc <3)
	{
		printf("Too few arguments\n");
		printf("Usage is %s <file> <word1> <word2> ...\n",argv[0]);
		exit(1);
	}

	/* Opening the file: */ 
	FILE *f_in = fopen(argv[1],"r");
	
	/* Check if the file opens properly: */
	if(f_in == NULL)
	{
		printf("Error message: <%s> is not a valid file.\n", argv[1]);
		exit(1);
	}

	/* Find the size of the file using fseek: */
       	fseek(f_in, 0, SEEK_END);

	/* Now we know how many bytes we need: */
	int nbytes = ftell(f_in);
	
	/* Using Malloc to allocate all that space: */
	unsigned char *buff = malloc(nbytes);

	/* Return the FPI to the begining of the file: */
	fseek(f_in, 0, SEEK_SET);
	fread(buff,sizeof(unsigned char),nbytes,f_in);
	
	/* Now we can count up the number of words we
	 * have so we can begin to allocate the size
	 * of our 2d 'words' array 			*/
	char *delims = " ,.\n";
	int wc = get_word_count(buff,delims);
	printf("\nWord Count is: %d\n",wc);

	/* now im going to set up a reigons array to tell 
	 * me where exactly my words are in buff so I can
	 * get them and put them into words (also csn get 
	 * the word lengths for allocating ;) 		*/
	int **regions = (int**)malloc(sizeof(int)*2);
	for(int i = 0; i < 2; i++)
	{
		regions[i] = (int*)malloc(sizeof(int)*wc);
	}
	
	/* Calling get_reigons to... get the reigons... */
	get_reigons(buff,delims,regions);

	/* Now we know where the words are, how many, and 
	 * their lengths!So now its time to make our 
	 * 'words[][]' array that will not be a rectangle...
	 *  in theory?				 */ 
	char **words = (char **)malloc(sizeof(char)*wc);
	for(int i = 0; i < wc; i++) 
	{
		int temp_size = regions[1][i] - regions[0][i] + 1;
		words[i] = (char *)malloc(sizeof(char)*temp_size);
		int k = 0;
		for(int j = regions[0][i]; j <= regions[1][i]; j++)
		{
		
			words[i][k] = buff[j];
			k++;
		}
			printf("%s\n",words[i]);
	}
	
	for(int i = 0; i < wc; i++){
		if(strcmp(words[i], argv[2]) == 0){
			printf("we are so close buddy\n");
		}
	}

	/* Tying up all the loose ends: */
	fclose(f_in);
	free(buff);
	buff = NULL;
	for(int i = 0; i<wc;i++)
	{
		// this free causes a memory error
		// free(reigons[i]);
		// reigons[i] = NULL;
	}
	free(regions);
	regions = NULL;
	for(int i = 0; i < wc; i++) 
	{
		// free(words[i]);
	}
	free(words);
	words = NULL;


}

int get_word_count(char *str, char *delims)
{
	int on_delim = 1;
	int length = strlen(str);
	int wc = 0;
	if(is_delim(str[0],delims) == 0)
	{
		on_delim = 0;
		wc++;
	}
	for(int i = 1; i<length; i++ ){
		if(is_delim(str[i],delims)==0 && on_delim)
		{
			on_delim = 0;
			wc++;
		}	
		if(is_delim(str[i],delims) == 1 && !on_delim) {
			on_delim = 1;
		}
	}	
	return(wc);
}

int is_delim(char c, char * delim){
	
	for(int i = 0; i <  (int)strlen(delim); i++){
		if(c == delim[i]){
			return(1);
		}
	}
	return(0);	
}


void get_reigons(char *str, char *delims, int **reigons)
{
	/* Reigons should be set up like this:
	 * [begining of word1][end of word1]
	 * [begining of word2][end of word2]
	 * 	    ...		  ...
	 * 	    				*/
	int on_delim = 1;
	int length = strlen(str);
	int wc = 0;
	if(is_delim(str[0],delims) == 0)
	{
		on_delim = 0;
		reigons[wc][0] = 0;
		wc++;
	}
	for(int i = 1; i<length; i++ ){
		if(is_delim(str[i],delims)==0 && on_delim)
		{
			/* These should all be correct */
			on_delim = 0;
			reigons[0][wc] = i;					
			wc++;
		}	
		if(is_delim(str[i],delims) == 1 && !on_delim) {
			on_delim = 1;
			reigons[1][wc-1] = i-1;
		}
	}	
}
