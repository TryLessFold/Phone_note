#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct tel_note
{
	char name[20];
	char lastname[20];
	char tel[20];
};
struct tel_srch
{
	struct tel_note *ptr;
	int size;
};
void display()
{
	printf("\n------------------\n");
	printf("1. Add\n");
	printf("2. Search\n");
	printf("3. Delete\n");
	printf("4. List\n");
	printf("0. Exit\n\n");
	printf("Input: ");
}

void Add (struct tel_note *note ,char *a, char *b, char *c)
{
	for(int i = 0; i<20; i++)
	{
		note->name[i] = a[i];
		note->lastname[i] = b[i];
		note->tel[i] = c[i];
	}
}
void Search(struct tel_note *note, char* key, int size, int **ptr)
{
	int i = 0;
	while(i<size)
	{
		if(note[i].tel[0]!=-1)
			if ((!strcmp(note[i].name,key))||(!strcmp(note[i].lastname,key))||(!strcmp(note[i].tel,key)))
			{
				((*ptr)[0])++;
				(*ptr) = realloc((*ptr), (((*ptr)[0])+1)*sizeof(struct tel_note));
				(*ptr)[(*ptr)[0]] = i;
			}
		i++;
	}
}
void OutSearched(struct tel_note *note, int *b)
{
	printf("  %10s %21s%21s%21s\n","№","Name","Last Name","Telephone number");
	for(int i = 1; i<=b[0]; i++)
	{
			printf("%10d.%21s%21s%21s\n",b[i]+1, note[b[i]].name, note[b[i]].lastname, note[b[i]].tel);
	}
}
void Remove(struct tel_note **note,int *size, int key)
{
	int diff = key, i = 0;
	if (key<(*size))
	{
		while ((i<=diff)&&(i<*size))
		{
			if ((*note)[i].tel[0]==-1) diff++;
			i++;
		}
		if (diff == (*size)-1)
		{
			if (((*note)[key].tel[0]==-1)||(diff==key))
				diff++;
			*size -= diff - key;
			(*note) = realloc((*note), sizeof(struct tel_note)*(*size));
		}
		else if (diff<*size)
			(*note)[diff].tel[0] = -1;
	}
}
void Outdirect (struct tel_note* note, int size)
{
	printf("  %10s %21s%21s%21s\n","№","Name","Last Name","Telephone number");
	int diff = 1;
	for(int i=0;i<size; i++)
	{
		if(note[i].tel[0]!=-1)
		{
			printf("%10d.%21s%21s%21s\n",i+diff, note[i].name, note[i].lastname, note[i].tel);
		}
		else
		{
			diff--;
		}
	}
}

void fgets_end(char *a, int length, FILE *f)
{
	fgets(a, length, f);
	int i = 0;
	while((a[i]!='\n')&&(i<length)){
		i++;
	}
	a[i] = '\0';
}

void clear_stdin()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF){
		continue;
	}
}

int main()
{
	char *ptr;
	char ch[3];
	struct tel_note *note = NULL;
	int *key = NULL;
	int size_direct = 0, tmp;
        char tmp_1[20], tmp_2[20], tmp_3[20];
	while(ch[0]!='0')
	{
		display();
		scanf("%s", ch);
		switch(ch[0])
		{
			case '1':
				tmp = 0;
				while ((tmp<size_direct)&&(note[tmp].tel[0]!=-1))
					tmp++;
				if (tmp == size_direct)
				{
					size_direct++;
					note = realloc(note,size_direct*sizeof(struct tel_note));
				}
				clear_stdin();
				printf("Input name: ");
				fgets_end(tmp_1,19,stdin);
				printf("Input lastname: ");
				fgets_end(tmp_2,19,stdin);
				printf("input telephone: ");
				fgets_end(tmp_3,19,stdin);
				Add(&note[tmp], tmp_1, tmp_2, tmp_3);
				break;
			case '2':
				key = malloc(sizeof(int));
				key[0] = 0;
				printf("Input elem: ");
				clear_stdin();
				fgets_end(tmp_1,19,stdin);
				Search(note, tmp_1, size_direct, &key);
				OutSearched(note, key);
				free(key);
				break;
			case '3':
				printf("Input number of deleting note: ");
				scanf("%d", &tmp);
				Remove(&note,&size_direct,tmp-1);
				break;
			case '4':
				Outdirect(note, size_direct);
				//printf("\n");
				break;
		}
	}
//	free(note);
	return 0;
}
