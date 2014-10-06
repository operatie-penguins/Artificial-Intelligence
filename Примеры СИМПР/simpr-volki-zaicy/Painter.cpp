//---------------------------------------------------------------------------


#pragma hdrstop

#include "Model.h"
#include "Painter.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

Painter::Painter(TCanvas* apCanvas) {
  m_pCanvas = apCanvas;
  m_pCanvas->Brush->Color = clBlack;
  m_pCanvas->Brush->Style = bsSolid;
}

void Painter::onBeforeNextCreature() {
  // plotCreature(m_pModel->getCurrentCreature(), clRed);
}

void Painter::plotCreature(Creature* pCreature, TColor c) {
  int x = pCreature->x *  m_Width;
  int y = pCreature->y *  m_Height;
  m_pCanvas->Pen->Color = c;
  m_pCanvas->Pen->Width = 5;
  m_pCanvas->MoveTo(x,y);
  m_pCanvas->LineTo(x,y);
}

void Painter::onBeginNextIter() {
  resetImage();
  for(vector<Food*>::iterator it = m_pModel->food.begin();
      it != m_pModel->food.end();
      it++) {
    plotPixel((*it)->x,
              (*it)->y,
              clLime);
  }
  for(vector<Creature*>::iterator it = m_pModel->creatures.begin();
      it != m_pModel->creatures.end();
      it++) {
    if((*it)->isHare()) {
      plotCreature(*it, clWhite);
    } else {
      plotCreature(*it, clRed);
    }
  }
}

void Painter::onResize(int newWidth, int newHeight) {
  m_Width = newWidth;
  m_Height = newHeight;
  resetImage();
}

void Painter::setModel(Model* apModel) {
  m_pModel = apModel;
  m_pModel->setModelListener(this);
}

void Painter::plotPixel(float x, float y, TColor c) {
  m_pCanvas->Pixels[x * m_Width][y * m_Height] = c;
}

void Painter::resetImage() {
  m_pCanvas->Brush->Color = clBlack;
  m_pCanvas->FillRect(TRect(0, 0, m_Width, m_Height));
}

