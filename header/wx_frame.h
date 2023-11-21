//
// Created by unkown on 11/18/23.
//

#ifndef WX_TEXTEDITOR_WX_FRAME_H
#define WX_TEXTEDITOR_WX_FRAME_H

#include "wx/wx.h"
#include "wx/filedlg.h"
#include "wx/wfstream.h"
#include "wx/richtext/richtextctrl.h"
#include "wx/textfile.h"
#include "wx/stdpaths.h"
#include "wx/stc/stc.h"

class wx_frame :public wxApp {
public:
    bool OnInit() override;
};

class mainFrame : public wxFrame{
public:
    mainFrame();
private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void LoadContent(wxCommandEvent& event);
    void SaveContent(wxCommandEvent& event);
    void OnSize(wxSizeEvent& event);
    //wxTextCtrl *text;
    wxStyledTextCtrl *nbtext;
    wxString fileName;
    wxBoxSizer *Sizer;
    int digits;

};



#endif //WX_TEXTEDITOR_WX_FRAME_H
