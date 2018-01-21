#include<stdio.h>
#include<stdlib.h>
char buf[128];

struct student {int id; char name[32]; int score;};
typedef struct student datatype;
struct rb_node{ datatype data; struct rb_node *left, *right; int black; };
//(black == 0)->red (black == 1)->black;

int is_red(struct rb_node *t){
  return (t != NULL && !t->black);
}
int is_red_family(struct rb_node *t){
  if(is_red(t)){
    if(is_red(t->left))return 1;//case 1
    if(is_red(t->right))return 2;//case 2
    return 0;
  }else{
    return 0;
  }
}

void print_rbtree(struct rb_node *t) {
  if(t == NULL) printf(".\n");
  else {
    printf("[%c]%d,%s,%d\n",t->black?'b' : 'r',t->data.id,t->data.name,t->data.score);
    print_rbtree(t->left); print_rbtree(t->right);
  }
}

struct rb_node* rotate_right(struct rb_node *t){
  struct rb_node *rt;
  if(t == NULL || t->left == NULL)return t;
  else{
    rt = t->left;
    t->left = rt->right;
    rt->right = t;
    return rt;
  }
}
struct rb_node* rotate_left(struct rb_node *t){
  struct rb_node *rt;
  if(t == NULL || t->right == NULL)return t;
  else{
    rt = t->right;
    t->right = rt->left;
    rt->left = t;
    return rt;
  }
}
struct rb_node *resolve_red_pair(struct rb_node *t){
  if(t == NULL){
    return t;
  }
  if(is_red_family(t->left) == 1){
    if(is_red(t->right)){
      t->black = 0;
      t->left->black = 1;
      t->right->black = 1;
    }else{
      t = rotate_right(t);
      t->black = 1;
      t->left->black = 0;
      t->right->black = 0;
    }
  }
  if(is_red_family(t->left) == 2){
    if(is_red(t->right)){
      t->black = 0;
      t->left->black = 1;
      t->right->black = 1;
    }else{
      t->left = rotate_left(t->left);
      t = rotate_right(t);
      t->black = 1;
      t->left->black = 0;
      t->right->black = 0;
    } 
  }
  if(is_red_family(t->right) == 2){
    if(is_red(t->left)){
      t->black = 0;
      t->left->black = 1;
      t->right->black = 1;
    }else{
      t = rotate_left(t);
      t->black = 1;
      t->left->black = 0;
      t->right->black = 0;
    }
  }
  if(is_red_family(t->right) == 1){
     if(is_red(t->left)){
      t->black = 0;
      t->left->black = 1;
      t->right->black = 1;
    }else{
      t->right = rotate_right(t->right);
      t = rotate_left(t);
      t->black = 1;
      t->left->black = 0;
      t->right->black = 0;
     } 
  }
  //t->left = resolve_red_pair(t->left);
  //t->right = resolve_red_pair(t->right);
  return t;
}
struct rb_node *rb_insert_rec(struct rb_node *t, struct student d){
  struct rb_node *n;
  if(t == NULL){
    n = (struct rb_node*)malloc(sizeof(struct rb_node));
    n->data = d;
    n->left = n->right = NULL;
    n->black = 0;
    return n;
  }else{
    if(t->data.id > d.id){
      t->left = rb_insert_rec(t->left, d);
    }
    if(t->data.id < d.id){
      t->right = rb_insert_rec(t->right, d);
    }
    t = resolve_red_pair(t);
    return t;
  } 
}
struct rb_node *rb_insert(struct rb_node *t, struct student d){
  t = rb_insert_rec(t, d);
  t->black = 1;
  return t;
}

int main(){
  struct student d;
  struct rb_node *t = NULL;
  while(fgets(buf, sizeof(buf), stdin) != NULL){
    sscanf(buf,"%d,%[^,],%d",&d.id,d.name,&d.score);
    t = rb_insert(t, d);
  }
  print_rbtree(t);
  return 0;
}
