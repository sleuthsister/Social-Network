#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 50

typedef struct node 
{
    char usn[100];
    struct node* next;
}node;

// Array to store user nodes
node* adj[size]; 
int count = 0;


node* create_node(char *name) 
{
   
    for (int i = 0; i < count; i++) 
    {
        if (adj[i] != NULL && strcmp(name, adj[i]->usn) == 0) 
        {
            printf("Sorry,Username already taken!\n");
            return NULL;
        }
    }
    
    node* new_node = (node*)malloc(sizeof( node));
    strcpy(new_node->usn, name);
    new_node->next = NULL;
    adj[count] = new_node;
    count++;
    return new_node;
}

void add_in_network(node* adj[], char name1[], char name2[]) 
{
    node* user1 = NULL;
    node* user2 = NULL;
    
    for (int i = 0; i < count; i++) 
    {
        if (strcmp(adj[i]->usn, name1) == 0) 
        {
            user1 = adj[i];
        }
        if (strcmp(adj[i]->usn, name2) == 0) 
        {
            user2 = adj[i];
        }
    }
   
    node* u1=user1;
    while (u1!=NULL)
    {
        if (strcmp(u1->usn,user2->usn)==0)
        {
            printf("Sorry, the users are already friends\n");
            return;        
        } 
        u1=u1->next;
    }
    // If both users are found, add user2 as a friend to user1 and vice versa
    if (user1!=NULL && user2!=NULL) 
    {
        node* newnode = (node*)malloc(sizeof(node));
        strcpy(newnode->usn, name2);
        newnode->next = user1->next;
        user1->next = newnode;
        
        node*newnode2=(node*)malloc(sizeof( node));
        strcpy(newnode2->usn,name1);
        newnode2->next=user2->next;
        user2->next=newnode2;
        printf("%s and %s are now friends!",user1->usn,user2->usn);
    } 
    else
    {
        printf("User not found\n");
    }
    
}


void display_network() 
{
    for (int i = 0; i < count; i++) 
    {
        if (adj[i] != NULL) 
        {
            printf("%s : ", adj[i]->usn);
            node* temp = adj[i]->next;
            
            while (temp != NULL) 
            {
                printf("%s ", temp->usn);
                temp = temp->next;
            }
            printf("\n");
        }
    }
}

void show_friends(char *n)
{
    int found=0;
    for(int i=0;i<count;i++)
    {
        if (strcmp(adj[i]->usn, n) == 0)
        {
            found=1;
            printf("%s friends are : \n",adj[i]->usn);
            node* temp = adj[i]->next;
            
            while (temp != NULL) 
            {
                printf("%s\n", temp->usn);
                temp = temp->next;
            }

        }        
    }
    if(found==0)
    {
        printf("Sorry, No user found");
    }
}

void mutual_friends(char *n1,char *n2)
{
    int mutual=0;
    int mcount=0;
    char mutual_list[10];
    node*temp1=NULL;
    node*temp2=NULL;
    for(int i=0;i<count;i++)
    {
        if (strcmp(adj[i]->usn, n1) == 0)
        {
            temp1 = adj[i]->next;
        }  
        if(strcmp(adj[i]->usn,n2)==0)
        {
            temp2=adj[i]->next;
        }
        if (temp1!=NULL && temp2!=NULL)
        {
            break;
        }
        
    }
    if (strcmp(temp1->usn,temp2->usn)==0)
    {
        printf("Please enter two different usernames\n");
        return;
    }
    
    while(temp1!=NULL && temp2!=NULL)
        {
            node *t1=temp1;
            while (t1!=NULL)
            {
                if (strcmp(t1->usn,temp2->usn)==0)
                {
                    printf("%s ",t1->usn);
                    mutual++;
                }
                t1=t1->next;
            }
            temp2=temp2->next;
        } 
        printf("\nThere are %d mutual friends ",mutual);   
    if(mutual==0)
    {
        printf("\n %s and %s have no mutual friends..",n1,n2);
    }
}

void remove_friend(char *name1, char *name2)
{
    int found=0;
    for(int i=0;i<count;i++)
    {
        if(strcmp(adj[i]->usn,name1)==0)
        {
            found=1;
            node*temp=adj[i]->next;
            node*prev=adj[i];
            while(temp!=NULL && strcmp(temp->usn,name2)!=0)
            {
                prev=temp;
                temp=temp->next;
            }
            if(temp==NULL)
            {
                printf("\n %s is not in the friend list of %s..",name2,name1);
            }
            else
            {
                prev->next=temp->next;
                free(temp);
                printf("\n%s and %s are no longer friends :(",name1,name2);   
            }
            break;
        }
    }
    if(found==0)
    {
        printf("\nSorry, unable to find user!");

    }
    
}

node* push_back(node*head,char* name)
{
    node* new_node=(node*)malloc(sizeof(node));
    node* last=head;
    new_node->next=NULL;
    strcpy(new_node->usn,name);
    if (head==NULL)
    {
        head=new_node;
        return head;
    }
    
    while (last->next!=NULL)
    {
        last=last->next;
    }
    last->next=new_node;
    return head;
    
}

node *deque(node* head)
{
    node* new_node=head->next;
    free(head);
    return new_node;
}

void bfs(node* adj[], char *start, char *target) 
{
   
    node* queue = NULL; 
    int visited[size] = {0}; 
    int parent[size]; 
    int start_index = -1, target_index = -1;

    
    for (int i = 0; i < count; i++) 
    {
        if (strcmp(adj[i]->usn, start) == 0) 
        {
            start_index = i;
        }
        if (strcmp(adj[i]->usn, target) == 0) 
        {
            target_index = i;
        }
    }

    if (start_index == -1 || target_index == -1) 
    {
        printf("Start or target user not found.\n");
        return;
    }

   
    queue = push_back(queue, start);
    visited[start_index] = 1; 
    parent[start_index] = -1; 

    while (queue != NULL) 
    {
        
        node* current = queue;
        queue = deque(queue); 

        // find the current node in the adjacency list
        int current_index = -1;
        for (int i = 0; i < count; i++) 
        {
            if (strcmp(adj[i]->usn, current->usn) == 0) 
            {
                current_index = i;
                break;
            }
        }

        // for printing the shortest path if we have reached the target
        if (current_index == target_index) 
        {
            
            printf("Shortest path from %s to %s: ", start, target);
            int path[size];
            int path_length = 0;
            for (int i = target_index; i != -1; i = parent[i]) 
            {
                path[path_length] = i;
                path_length++;
            }
            for (int j = path_length - 1; j >= 0; j--) 
            {
                printf("%s ", adj[path[j]]->usn);
            }
            printf("\n");
            free(current); 
            return;
        }

        // traverse the friends of the current node
        node* friend_node = adj[current_index]->next;
        while (friend_node != NULL) 
        {
            
            int friend_index = -1;
            for (int i = 0; i < count; i++) 
            {
                if (strcmp(adj[i]->usn, friend_node->usn) == 0) 
                {
                    friend_index = i;
                    break;
                }
            }

            if (friend_index != -1 && !visited[friend_index]) 
            {
                
                visited[friend_index] = 1;
                parent[friend_index] = current_index; 
                queue = push_back(queue, friend_node->usn);
            }
            friend_node = friend_node->next;
        }

        free(current); 
    }

    printf("No path found from %s to %s.\n", start, target);
}



void main()
{
    printf("Welcome to Social Network!");
    printf("\nChoose from the following options to perform an operation");
    int stop=0;
    while(stop!=1)
    {
        printf("\n1. Add user");
        printf("\n2. Add friends");
        printf("\n3. Remove friend");
        printf("\n4. Show friend list");
        printf("\n5. Show mutual friends");
        printf("\n6. Show connection between users");
        printf("\n7. Display network");
        printf("\n8. Log Out");
        int choice;
        printf("\nEnter choice : ");
        scanf("%d",&choice);
        
        if(choice==1)
        {
            char n[100];
            printf("\nEnter user name : ");
            scanf("%s",n);
            node*user=(node*)malloc(sizeof(node));
            user=create_node(n);
            if(user==NULL)
            {
                printf("Sorry, unable to create user at the moment\n");
            }
            else
            {
                printf("\nUser added successfully!");
                printf("\nWelcome to the Network, %s",user->usn);
            }
        }
        else if(choice==2)
        {
            //add friend ( connect edge btw vertex)
            char name1[100], name2[100];
            printf("\nEnter username to add friend : ");
            scanf("%s", name1);
            printf("Enter friend's username: ");
            scanf("%s", name2);
            add_in_network(adj, name1, name2);
        }
        else if(choice==3)
        {
            char name1[100],name2[100];
            printf("Enter user account: ");
            scanf("%s",name1);
            printf("\nEnter friend's account: ");
            scanf("%s",name2);
            remove_friend(name1,name2);
        }
         else if(choice==4)
        {
            char name[100];
            printf("Enter user name to display frined list : ");
            scanf("%s",name);
            show_friends(name);
        }
        else if(choice==5)
        {
            char name1[100],name2[100];
            printf("Enter user 1 : ");
            scanf("%s",name1);
            printf("\nEnter user 2 : ");
            scanf("%s",name2);
            mutual_friends(name1,name2);

        }
        else if(choice==6)
        {
            char start_user[100];
            char target_user[100];
            printf("Enter username: ");
            scanf("%s", start_user);
            printf("Enter target username: ");
            scanf("%s", target_user);
           bfs(adj,start_user,target_user);
        }
        else if(choice==7)
        {
            display_network();
        }
        else if(choice==8)
        {
            printf("\nThank You for using Social Network!");
            stop=1;
            break;
        }
        
    }
}
