#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define MAX_CHILDREN 4
struct inode {
    char *name; 
    struct inode *parent;
    struct inode *children[MAX_CHILDREN];
};

struct inode *addInode(struct inode *fs, char *name)
{
    int poz_libera = MAX_CHILDREN;
    if(fs != NULL)
    {
        for(int i=0; i<MAX_CHILDREN; i++)
            if(fs->children[i]!=NULL)
                if(strcmp(fs->children[i]->name,name)==0)
                {
                    printf("File %s already exists in %s\n", name, fs->name);
                    return fs;
                }

        for(int i=0; i<MAX_CHILDREN; i++)
            if(fs->children[i] == NULL)
            {
                poz_libera = i;
                break;
            }
    }else
    {
        poz_libera = -1;
    }

    if(poz_libera == MAX_CHILDREN)
    {
        printf("Directory %s is full\n", fs->name);
        return fs;
    }

    struct inode* new = (struct inode*) malloc (sizeof(struct inode));
    new->name = malloc(sizeof(char) * (strlen(name)+1) );
    strcpy(new->name,name);
    for(int i=0; i<MAX_CHILDREN; i++)
        new->children[i] = NULL;
    new->parent = NULL;

    new->parent = fs;
    if(poz_libera >= 0)
        fs->children[poz_libera] = new;
    return new;
}

void printDirectory(struct inode *fs)
{
    if(fs==NULL)
        return;

    for(int i=0; i<MAX_CHILDREN; i++)
    {
         if(fs->children[i]!=NULL)
            if(fs->children[i]->name[strlen(fs->children[i]->name)-1]=='/')
                printf("Directory: %s\n", fs->children[i]->name);
            else
                printf("File: %s\n", fs->children[i]->name);
    }
}

void changeDirectory(struct inode **fs, char *dir)
{
    if((*fs) == NULL)
        return;

    if(strcmp(dir,"..")==0)
    {
        if((*fs)->parent!=NULL)
        {
            (*fs) = (*fs)->parent;
            return;
        }else
            return;
    }

    for(int i=0; i<MAX_CHILDREN; i++)
        if((*fs)->children[i]!=NULL)
            if(strcmp((*fs)->children[i]->name,dir)==0)
            {
                if( (*fs)->children[i]->name[strlen((*fs)->children[i]->name)-1]=='/' )
                {
                    (*fs) = (*fs)->children[i];
                    return;
                }
            }
    printf("Directory does not exist!\n");
}

void printFullPath(struct inode *fs)
{
    if(fs == NULL)
        return;

    printFullPath(fs->parent);
    printf(fs->name);
}

void printDirectoryRecursive(struct inode *fs)
{
    if(fs == NULL)
        return;

    printDirectory(fs);
    for(int i=0; i<MAX_CHILDREN; i++)
        printDirectoryRecursive(fs->children[i]);
}

void removeInode(struct inode *fc, char *fn)
{
    if(fc==NULL)
        return;
    
    for(int i=0; i<MAX_CHILDREN; i++)
        if(fc->children[i]!=NULL)
            if(strcmp(fc->children[i]->name,fn)==0)
            {
                int nr_subdirs = 0;
                for(int j=0; j<MAX_CHILDREN; j++)
                    if(fc->children[i]->children[j]!=NULL)
                        nr_subdirs++;
                if(nr_subdirs==0)
                {
                    free(fc->children[i]->name);
                    free(fc->children[i]);
                    fc->children[i] = NULL;
                    return;
                }else
                {
                    printf("Cannot delete non-empty directory.\n");
                    return;
                }
            }
    printf("File or directory %s does not exist in %s\n",fn, fc->name);
}

int compare_inodes(struct inode *n1, struct inode *n2)
{
    if(n2 == NULL && n1 == NULL)
        return -1;
    
    if(n2 == NULL && n1 != NULL)
        return -1;

    if(n1 == NULL && n2 != NULL)
        return 1;

    if(strcmp(n1->name, n2->name) < 0)
        return -1;

    return 1;
}

void sortDirectory(struct inode *fs)
{
    if(fs == NULL)
        return;

    int ordonat =0;
    while(ordonat != 1)
    {
        ordonat = 1;
        for(int i=0; i<MAX_CHILDREN-1; i++)
            if(compare_inodes(fs->children[i], fs->children[i+1])>0)
            {
                struct inode *aux = fs->children[i];
                fs->children[i] = fs->children[i+1];
                fs->children[i+1] = aux;
                ordonat = 0;
            }
    }
}

void findInodeAnywhere(struct inode *fs, char *name)
{
    if(fs == NULL)
        return;

    if(strcmp(fs->name,name)==0)
    {
        printFullPath(fs);
        return;
    }

    if(fs->name[strlen(fs->name)-1] != '/')
        return;

    for(int i=0; i<MAX_CHILDREN-1; i++)
        findInodeAnywhere(fs->children[i], name);
}

struct inode *changeDirectoryAbsolute(struct inode *fs, char *dir)
{
    if(fs==NULL)
        return NULL;

    if(strstr(dir, fs->name) != dir)
        return NULL;

    if(strlen(dir) ==  strlen(fs->name))
        return fs;

    for(int i=0; i<MAX_CHILDREN-1; i++)
    {
        struct inode * aux = changeDirectoryAbsolute(fs->children[i], dir + strlen(fs->name));
        if(aux!=NULL)
            return aux;
    }

    return NULL;
}

void move(struct inode *fSrc, struct inode *fDst)
{
    if(fSrc == NULL)
    {
        printf("Source file does not exist\n");
        return;
    }

    if(fDst == NULL)
    {
        printf("Destination file does not exist\n");
        return;
    }

    //verifica loc liber in destinatie
    int destinatie_loc = -1;
    for(int i=0; i<MAX_CHILDREN-1; i++)
    {
        if(fDst->children[i]==NULL)
            {
                destinatie_loc = i;
                break;
            }        
    }

    if(destinatie_loc == -1)
    {
        printf("Destination is full\n");
        return;
    }    

    if(fSrc->parent!=NULL)
    {
        for(int i=0; i<MAX_CHILDREN-1; i++)
        {
            if(fSrc->parent->children[i]==fSrc)
            {
                fSrc->parent->children[i] = NULL;
                break;
            }
        }
    }

    fSrc->parent = fDst;
    fDst->children[destinatie_loc] = fSrc;    
}

int main()
{
    char comanda;
    bool ask = true;

    struct inode *fc = addInode(NULL, "/"); 
    struct inode *root = fc;
    struct inode *aux = NULL;
    

    while(1)
    {
        if(ask)
            printf("Command? "); 
        scanf("%c", &comanda);

        ask = true;
        char argument1[255];
        char argument2[255];

        switch(comanda)
        {
            case 'm':
                printf("Source path? ");
                scanf("%s",argument1);

                printf("Destination path? ");
                scanf("%s",argument2);

                move( changeDirectoryAbsolute(root, argument1), changeDirectoryAbsolute(root, argument2) );
                break;



            case 'C':
                printf("Change path to? ");
                scanf("%s",argument1);
                aux = changeDirectoryAbsolute(root, argument1);
                if(aux!=NULL)
                    fc = aux;
                else
                    printf("Directory does not exist.\n");
                break;

            case 'F':
                printf("Give filename? ");
                scanf("%s",argument1);
                findInodeAnywhere(fc, argument1);
                break;

            case 's':
                sortDirectory(fc);
                break;

            case 'r':
                printf("Give filename? ");
                scanf("%s",argument1);
                removeInode(fc, argument1);
                break;

            case 'P':
                printDirectoryRecursive(fc);
                break;

            case 'f':
                printFullPath(fc);
                printf("\n");
                break;

            case 'c':
                printf("Give filename? ");
                scanf("%s",argument1);
                changeDirectory(&fc, argument1);
                break;

            case 'p':
                printDirectory(fc);
                break;

            case 'a':
                printf("Give filename? ");
                scanf("%s",argument1);
                addInode(fc,argument1);
                break;

            case ' ':
            case '\r':
            case '\n':
                ask = false;
                break;

            default:
                printf("Unknown command '%c'.\n", comanda);
                break;
        }
    }
    return 0;
}