#include "my_frame.h"

#include "my_panel.h"

MyFrame::MyFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title) {
  new MyPanel(this);
}
