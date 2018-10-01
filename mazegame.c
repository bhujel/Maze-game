#include <stdio.h>
#include <stdlib.h>
struct queue{
  char v ;
  int x , y ;
  struct queue *f , *r , *next ;
};
typedef struct stack{
  char v ;
  int x , y ;
  struct stack *next ;
}stk;
void create_board( char b[100][100] , int r , int c ){
    for ( int i = 0 ; i <= r ; i++ ){
        for ( int j = 0 ; j <= c ; j++ ){
            b[i][j] = ' ' ;
        }
    }
    b[0][0] ='s';
    b[r][c] ='d';
    b[1][1]=b[1][2]=b[1][3]=b[0][5]=b[0][6] ='@';
    b[2][2]=b[3][2]=b[3][0]=b[2][4]=b[2][5]=b[2][6]='@';
    b[3][4]=b[3][5]=b[3][6]='@';
    b[4][2]=b[4][3]=b[5][5]=b[5][6] =b[5][0] = '@';
}
void screen( char b[100][100] , int r , int c ){
    printf("$");
    for ( int i = 0 ; i <= c ; i++ )
    printf(" $");
    printf("$");
    printf("\n");
    for ( int i = 0 ; i <= r ; i++ ){
        printf("$");
        for ( int j = 0 ; j <= c ; j++ ){
            printf(" %c",b[i][j]);
        }
        printf("$\n");
    }
    printf("$");
    for ( int i = 0 ; i <= c ; i++ )
    printf(" $");
    printf("$");
    printf("\n");
}
void add( struct queue **q , int r , int c , char b[100][100]){
struct queue *temp =(struct queue*)malloc(sizeof(struct queue)) ;
temp->x = r ;
temp->y = c ;
temp->v = '0';
temp->next = NULL ;
if( (*q)->r == NULL ){
  (*q)->f = (*q)->r = temp ;
}else{
(*q)->r->next = temp ;
(*q)->r = temp ;
}
b[(*q)->r->x][(*q)->r->y] = (*q)->r->v ;
}
void dequeue( struct queue **q , char b[100][100]){
  b[(*q)->f->x][(*q)->f->y] = '*' ;
  struct queue *t = (*q)->f ;
  (*q)->f = (*q)->f->next;
  free(t);
}
void push( stk **s , int r , int c , char b[100][100]){
 stk *temp = (stk*)malloc(sizeof(stk));
 temp->v = '0' ;
 temp->x = r ;
 temp->y = c ;
 if ( *s == NULL )
 *s = temp ;
 else {
 temp->next = *s ;
 *s = temp ;
 }
 b[temp->x][temp->y] = temp->v ;
}
void pop( stk **s , char b[100][100] ){
  stk *temp = *s ;
  b[temp->x][temp->y] = '*' ;
  *s = (*s)->next ;
  free(temp);
}

int play( char b[100][100] , char b1[100][100] , int r , int c ){
  char op , u ;
  int undo = 3 , l = 3 ;
  scanf(" %c",&op);
  int x = 0 , y = 0 , s = 0 ;
  b1[0][0] ='*' ;
  stk *redo = NULL ;
  while( b1[x][y] != 'd' && op ){
    //push(&redo , x , y , b1 );
    system("clear");
    int t1 = x , t2 = y ;
    int x1 = 0 , y1 = 0 ;
    switch(op){
    case 'w' : x1 = -1 ;
    break ;
    case 'd' : y1 = 1 ;
    break ;
    case 'z' : x1 = 1 ;
    break ;
    case 'a' : y1 = -1 ;
    break ;
    default : printf(" Press valid option \n");
    x1 = 0 , y1 = 0 ;
    break ;
    } 
    x = x + x1 , y = y + y1 ;
if ( x >= 0 && x <= r && y >= 0 && y <= c ){
  if ( (b[x][y] == '*' || b[x][y] == '0') && ( b1[x][y] == ' '|| b1[x][y] == '*' )){
    if ( b1[x][y] == ' ' ){
     b1[x][y] ='*' ;
    s += 4 ;
    }
    else if ( b1[x][y] == '*' ){
      s -= 4 ;
      b1[t1][t2] = ' ' ;
    }
  }else if( b1[x][y] == '@' ){
     printf("OOPS YOU HIT THE OBSTACLE\nPRESS 'u' TO UNDO\n YOU VE %d LIFE\n",undo);
        scanf(" %c",&u);
        if ( u == 'u' && undo > 0 ){
      x = t1 , y = t2 ;
      s -= 4 ;
      undo-- ;
        }else {
          goto end1 ; 
        }
  }
  if ( b1[x][y] == 'd'){
    printf("YOU REACHED THE DESTINAION\n");
  break ;
  }
    }else{
        printf("OOPS YOU HIT THE OBSTACLE\nPRESS 'u' TO UNDO\nYOU VE %d LIFE\n",undo);
        scanf(" %c",&u);
        if ( u == 'u' && undo > 0 ){
      x = t1 , y = t2 ;
      s -= 4 ;
      undo--;
      undo++ ;
        }else {
          goto end ; 
        }
    }
      screen( b1 , r , c );
      printf("YOUR SCORE : %d\n",s);
     scanf(" %c",&op);  
  }
  printf("THANK YOU FOR PLAYING\nYOUR SCORE : %d\n",s);
  return 1 ;
  end :{
   printf("SORRY YOU FAILED\n");
   return 0 ;
  }
  end1 :{
   printf("SORRY YOU FAILED\n");
   return 0 ;
  }
}
//implement using queue
int q_implement( struct queue *q ,char b[100][100] ,char b1[100][100] ,int r ,int c ){
while( 1 ){
  if((q->f->x)-1 >= 0 ) {
    if( b[(q->f->x)-1][(q->f->y)] == 'd')
    goto last ;
    else if( b[(q->f->x)-1][(q->f->y)] == ' ')
    add( &q , (q->f->x)-1 , q->f->y , b );
  }
  if((q->f->x)+1 <= r ){
    if( b[(q->f->x)+1][(q->f->y)] == 'd')
    goto last ;
    else if ( b[(q->f->x)+1][(q->f->y)] == ' ')
    add( &q , (q->f->x)+1 , q->f->y , b );
  }
  if((q->f->y)-1 >= 0) {
    if( b[(q->f->x)][(q->f->y)-1] == 'd')
    goto last ;
    else if (b[(q->f->x)][(q->f->y)-1] == ' ')
    add( &q , (q->f->x) , (q->f->y)-1 , b );
  }
  if ((q->f->y)+1 <= c ){
    if( b[(q->f->x)][(q->f->y)+1] == 'd')
    goto last ;
    else if ( b[(q->f->x)][(q->f->y)+1] == ' ')
    add( &q , (q->f->x) , (q->f->y)+1 , b );
  } 
  dequeue( &q , b);  
 }
 last:
 dequeue( &q , b); 
 if (play( b , b1 , r , c ))
 return 1 ;
 else 
 return 0 ;
}
void stack( stk *s , char b[100][100] , char b1[100][100] , int r , int c ){
  while( 1 ){
      int tx = s->x , ty = s->y ;
      pop(&s,b);
  if(tx+1 >= 0 ) {
    if( b[tx+1][ty] == 'd'){
      goto out ;
    }
    else if( b[tx+1][ty]== ' ')
    push( &s , tx+1 , ty , b );
  }
  if(ty+1 >= 0 ) {
    if( b[tx][ty+1] == 'd'){
      goto out ;
    }
    else if( b[tx][ty+1]== ' ')
    push( &s , tx , ty+1 , b );
  }
  if(tx-1 >= 0 ) {
    if( b[tx-1][ty] == 'd'){
      goto out ;
    }
    else if( b[tx-1][ty]== ' ')
    push( &s , tx-1 , ty , b );
  }
  if(ty-1 >= 0 ) {
    if( b[tx][ty-1] == 'd'){
      goto out;
    }
    else if( b[tx][ty-1]== ' ')
    push( &s , tx , ty-1 , b );
       }
    }
  out :
  //screen( b , r , c );
 play( b , b1 , r , c );
}
int main(){
    char b[100][100] , b1[100][100] , b2[100][100] ;
    int r = 5 , c = 7, f = 0 ;
    struct queue *q =(struct queue*)malloc(sizeof(struct queue)) ;
    create_board( b , r , c );
    for ( int i = 0 ; i <= r ; i++ ){
      for ( int j = 0 ; j <= c ; j++ )
      b2[i][j] = b1[i][j] = b[i][j];
    }
printf("WEL-COME TO MAZE GAME\nPRESS\n'W' = UP\n'A' = LEFT\n'D' = RIGHT\n'Z' = DOWN\n");
    screen( b , r , c );
    q->f = q->r = NULL ;
    add( &q , 0 , 0 , b );
 int c1 = q_implement( q , b , b1 , r , c );    
char ch ;
if(c){
printf("DO YOU WANT TO CONTINUE [y/n]?\n");
scanf(" %c",&ch);
if ( ch == 'y')
{
  stk *s = NULL ;
    create_board( b , r , c );
    for ( int i = 0 ; i <= r ; i++ ){
      for ( int j = 0 ; j <= c ; j++ )
      b1[i][j] = b2[i][j];
    }
    screen( b , r , c );
     push( &s , 0 , 0 , b );
     stack( s , b , b1 , r , c );
  }
}
    return 0 ;
}

