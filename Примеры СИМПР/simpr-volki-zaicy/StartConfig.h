//---------------------------------------------------------------------------

#ifndef StartConfigH
#define StartConfigH
//---------------------------------------------------------------------------

class StartConfig {
  private:
    StartConfig() {
      hareCount = 50;
      wolfCount = 6;
      foodCount = 0;
      foodLimit = 2000;
      hareLifeLength = 500;
      wolfLifeLength = 500;
      foodGenProbabilityX1000 = 400;
      foodRespawnProbabilityX1000 = 6;
      harePregnancyLength = 25;
      wolfPregnancyLength = 125;
      hareSpeed = 0.05;
      wolfSpeed = 0.07;
      hareSpawnFactor = 5;
      wolfSpawnFactor = 3;
    }
  public:
    static StartConfig* instance() {
      static StartConfig inst;
      return &inst;
    }

    int hareCount;
    int wolfCount;
    int foodCount;
    int foodLimit;

    int hareLifeLength;
    int wolfLifeLength;

    int foodGenProbabilityX1000;
    int foodRespawnProbabilityX1000;

    int harePregnancyLength;
    int wolfPregnancyLength;

    float hareSpeed;
    float wolfSpeed;

    int hareSpawnFactor;
    int wolfSpawnFactor;
};

//---------------------------------------------------------------------------
#endif
