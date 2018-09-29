class Vasi{
public:
   Vasi();
   ~Vasi();
};


class Rafi{
  int number;
public:
   Rafi(int);
   ~Rafi();
   bool placebook(int);
   bool takebook();
};

class Doulapi{
  Rafi panw;
  Rafi katw;
public:
  Doulapi(int,int);
  ~Doulapi();
  bool placebook(int,int);
  bool takebook(int);
};


class Library{
  Vasi vasi;
  Doulapi doulapi;
  Rafi rafi1;
  Rafi rafi2;
  Rafi rafi3;
  int counter;
public:
  Library(int,int,int,int,int,int);
  ~Library();
  bool placebook(int,int);
  bool takebook(int);
  };


