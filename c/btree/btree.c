#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

	struct btree
	{
		char node;
		int count;
		struct btree *left;
		struct btree *right;
	};
 	void btree_print(struct btree *p)
		{
			if(p != NULL)
			{
				btree_print(p->left);
				printf("%c\t%d\n",p->node,p->count);
				btree_print(p->right);
			}
		} 
		
	struct btree *btree_malloc()
		{
			return (struct btree *) malloc(sizeof(struct btree));
		}			
		
	struct btree *btree_initial(struct btree *p,char node)
		{
				if (p == NULL)
				{
					p = btree_malloc();
					p->node = node;
					p->count = 1;
					p->left = NULL;
					p->right = NULL;
				}
				else if (node == p->node)
						p->count ++;
					else if (node < p->node)
							p->left = btree_initial(p->left,node);
						else  
							p->right = btree_initial(p->right,node);	
					
			return p;
		}

void main()
{
	char node;
	struct btree *test = NULL;
	printf("input chars\n");
	while((node = getchar()) != '#')
	 test = btree_initial(test,node);
	printf("the result is:\n");
	btree_print(test);
	
}