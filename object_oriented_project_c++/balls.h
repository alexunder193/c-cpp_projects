class Ball{
 protected:
  int durability;
  int maxdurability;
  int loseball;
  int breakball;
 public:
  virtual void hit()=0;
  virtual void rest()=0;
  virtual void meiosi()=0;
  virtual int epistrofi()=0;
  int tupos(int,int,int);
  Ball();
};


class Basketball: public Ball{
  static int sum1;
 public:
  void hit();
  void rest();
  Basketball(int);
  void meiosi();
  int epistrofi();
};


class Tennis: public Ball{
 static int sum2;
 public:
  void hit();
  void rest();
  Tennis(int);
  void meiosi();
  int epistrofi();
};


class Pingpong: public Ball{
 static int sum3;
 public:
  void hit();
  void rest();
  Pingpong(int);
  void meiosi();
  int epistrofi();
};

