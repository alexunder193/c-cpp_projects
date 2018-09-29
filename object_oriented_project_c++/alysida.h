class Alysida{
  private:
   int plithos;                          //plithos paiktwn
 typedef  struct listnode{
  int id;
  int number;
  listnode* epomenos;
}*List;

List header;                                 //deiktis pou deixnei stin arxi tis alysidas
List temp;                                   //deikths pou deixnei se komvous tis alysidas xreiazetai gia tin stoptune thn resume kai thn hit
List trexon;                                 //xreiazetai gia thn eisagwgh twn paiktwn  na deixnei ston teleutaio komvo
  public:
Alysida();
void eisagogi(int,int,int);
void stop_tune();
void hit();
void print_chain();
void resume();
void game_over();
void winner();
};

