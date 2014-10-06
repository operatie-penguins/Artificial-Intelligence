//---------------------------------------------------------------------------

#ifndef PainterH
#define PainterH
//---------------------------------------------------------------------------

#include <Graphics.hpp>
class Model;

class Painter {
  private:
    TCanvas* m_pCanvas;
    Model* m_pModel;
    float m_Width;
    float m_Height;
  public:
    Painter(TCanvas* apCanvas);
    void onBeforeNextCreature();
    void onBeginNextIter();
    void onResize(int newWidth, int newHeight);
    void setModel(Model* apModel);
    void plotCreature(Creature* pCreature, TColor c);
    void plotPixel(float x, float y, TColor c);
    void resetImage();    
};

//---------------------------------------------------------------------------
#endif
