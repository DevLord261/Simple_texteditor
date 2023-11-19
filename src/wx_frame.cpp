//
// Created by unkown on 11/18/23.
//

#include "wx_frame.h"

wxIMPLEMENT_APP(wx_frame);

bool wx_frame::OnInit() {
    mainFrame *frame = new mainFrame();
    frame->Show();
    return true;
}

mainFrame::mainFrame() : wxFrame(nullptr, wxID_ANY, "Hello World",wxPoint(50,50),wxSize(800,600)){


    wxIcon *icon=new wxIcon();
    icon->LoadFile("/resources/myicon.png",wxBITMAP_TYPE_PNG);
    SetIcon(*icon);


    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_OPEN, "&Open...\tCtrl+O");
    menuFile->Append(wxID_SAVE,"&Save\tCtrl+S");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);


    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);


    text= new wxTextCtrl(this,wxID_ANY,"",wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE);
    Bind(wxEVT_MENU, &mainFrame::LoadContent, this, wxID_OPEN);
    Bind(wxEVT_MENU, &mainFrame::SaveContent, this, wxID_SAVE);
    Bind(wxEVT_MENU, &mainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &mainFrame::OnExit, this, wxID_EXIT);



}

void mainFrame::LoadContent(wxCommandEvent& event)
{
    wxFileDialog
            openFileDialog(this, _("Open text file"), "", "",
                           "text files (*.txt)|*.txt|All files (*.*)|*.*", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...

    fileName =openFileDialog.GetPath();
    wxTextFile file;
    if (file.Open(fileName)){
        wxString Content;
        for (int i = 0; i < file.GetLineCount(); ++i) {
            Content+=file.GetLine(i) +"\n";
        }
        text->Clear();
        text->SetValue(Content);
        file.Close();
    }

}

void mainFrame::SaveContent(wxCommandEvent& event){
    if (fileName ==""){
        wxFileDialog saveFileDialog(this,_("Save text file"),"","",
                                    "text files (*.txt)|*.txt",wxFD_SAVE);
        if (saveFileDialog.ShowModal()==wxID_CANCEL)
            return;
        fileName=saveFileDialog.GetPath();
    }
    wxTextFile file(fileName);
    if (!file.Exists())
        file.Create();
    if (file.Open()){
        file.Clear();
        file.AddLine(text->GetValue());
        file.Write();
        file.Close();
    }
}

void mainFrame::OnExit(wxCommandEvent &event) {
    wxWindow::Close();

}

void mainFrame::OnAbout(wxCommandEvent &event) {
    wxMessageBox("This is Simple Text Editor",
                 "About", wxOK | wxICON_INFORMATION);
}

