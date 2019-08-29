#include "wx/app.h"

#include "my_frame.h"

class App : public wxApp {
public:
  bool OnInit() override {
    if (!wxApp::OnInit()) {
      return false;
    }

    MyFrame* window = new MyFrame(wxT("WX Cylinder"));
    window->SetSize(800, 600);
    window->Show();

    return true;
  }
};

IMPLEMENT_APP(App)
